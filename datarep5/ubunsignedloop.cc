#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "hexdump.hh"

int main(int argc, char** argv) {
    assert(argc >= 3);
    unsigned n1 = strtol(argv[1], nullptr, 0);
    unsigned n2 = strtol(argv[2], nullptr, 0);

    unsigned long sum = 0;
    for (unsigned i = n1; i <= n2; ++i) {
        use_int(i);
        sum += i;
        //printf("%u\n", i);
    }
    printf("Done %u-%u, sum %lu\n", n1, n2, sum);
}
