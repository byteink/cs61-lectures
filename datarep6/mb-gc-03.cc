#include "membench.hh"
#include <vector>
#include <string>
#include <algorithm>
void* gc_alloc(size_t);

struct memnode {
    const char* file;
    unsigned line;
};

struct memnode_arena {
    memnode* allocate() {
        return (memnode*) gc_alloc(sizeof(memnode));
    }
    void deallocate(memnode*) {
    }
};


// Conservative garbage collector

struct allocation {
    uintptr_t addr;
    size_t sz;
    bool mark;
};

static std::vector<allocation> blocks;

allocation* gc_find(uintptr_t addr) {
    if (addr) {
        for (auto& a : blocks) {
            if (addr >= a.addr && addr < a.addr + a.sz) {
                return &a;
            }
        }
    }
    return nullptr;
}

void gc_mark(uintptr_t addr, size_t sz) {
    for (size_t i = 0; i <= sz - sizeof(uintptr_t); i += sizeof(uintptr_t)) {
        uintptr_t pptr;
        memcpy(&pptr, (void*) (addr + i), sizeof(pptr));
        allocation* a = gc_find(pptr);
        if (a && !a->mark) {
            a->mark = true;
            gc_mark(a->addr, a->sz);
        }
    }
}

void gc() {
    char* stack_top = (char*) &stack_top;
    extern char** environ; // known to be at the bottom of the stack
    char* stack_bottom = (char*) environ;

    // Unmark heap
    for (auto& a : blocks) {
        a.mark = false;
    }

    // Mark objects reachable from stack
    gc_mark((uintptr_t) stack_top, stack_bottom - stack_top);

    // Free unmarked objects
    size_t freed_size = 0;
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        if (!it->mark) {
            freed_size += it->sz;
            free((void*) it->addr);
            *it = blocks.back();
            blocks.pop_back();
        } else {
            ++it;
        }
    }

    printf("gc freed %zu bytes\n", freed_size);
}

void* gc_alloc(size_t sz) {
    blocks.reserve(100000);
    if (blocks.size() == 100000) {
        gc();
    }

    void* p = malloc(sz);
    if (!p) {
        gc();
        p = malloc(sz);
    }
    if (p) {
        blocks.push_back({(uintptr_t) p, sz, false});
    }
    return p;
}


unsigned long memnode_benchmark(unsigned noperations, unsigned step) {
    assert(step % 2 == 1);  // `step` must be odd
    long counter = 0;
    memnode_arena arena;

    // Allocate 4096 memnodes.
    const unsigned nnodes = 4096;
    memnode* m[nnodes];
    for (unsigned i = 0; i != nnodes; ++i) {
        m[i] = arena.allocate();
        m[i]->file = "datarep/mb-filename.cc";
        m[i]->line = counter;
        ++counter;
    }

    // Replace one `noperations` times.
    for (unsigned i = 0; i != noperations; ++i) {
        unsigned pos = (i * step) % nnodes;
        arena.deallocate(m[pos]);

        m[pos] = arena.allocate();
        m[pos]->file = "datarep/mb-filename.cc";
        m[pos]->line = counter;
        ++counter;
    }

    // Compute a statistic and free them.
    unsigned long result = 0;
    for (unsigned i = 0; i != nnodes; ++i) {
        result += m[i]->line;
        arena.deallocate(m[i]);
    }

    return result;
}
