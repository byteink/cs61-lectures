#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "hexdump.hh"

int main(int argc, char** argv) {
    assert(argc >= 3);
    int n1 = strtol(argv[1], nullptr, 0);
    int n2 = strtol(argv[2], nullptr, 0);

    for (int i = n1; i <= n2; ++i) {
        use_int(i);
        //printf("%d\n", i);
    }
    printf("Done %d-%d\n", n1, n2);
}
