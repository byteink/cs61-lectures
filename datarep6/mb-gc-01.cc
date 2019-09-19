#include "membench.hh"
#include <vector>
#include <string>
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

void gc() {
    // Called when memory is exhausted; should reclaim
    // unreferenced memory
    // ??????? Do something ??????
    abort();
}

void* gc_alloc(size_t sz) {
    void* p = malloc(sz);
    if (!p) {
        gc();
        p = malloc(sz);
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
