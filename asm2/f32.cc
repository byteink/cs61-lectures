//! -O3
#include <stdio.h>
#include <stdlib.h>

struct small { char a1, a2; };
int __attribute__((noinline)) f(small s) {
    return s.a1 + 2 * s.a2;
}

int main(int argc, char** argv) {
    small s;
    s.a1 = s.a2 = 0;
    s.a1 = strtol(argc < 2 ? "0" : argv[1], nullptr, 0);
    s.a2 = strtol(argc < 3 ? "0" : argv[2], nullptr, 0);
    printf("%d.%d = %d\n", s.a1, s.a2, f(s));
}
