#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hexdump.hh"

int array[10] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};

int access1(int i) {
    if (i < 0 || i >= 10) {
        abort();
    }
    int x = array[i];

    // Modern compilers will remove this assert as redundant
    // when optimizations are on.
    assert(i >= 0 && i < 10);

    return x;
}

int access2(int i) {
    // Let's remove the explicit bounds check. Now what happens?

    int x = array[i];
    assert(i >= 0 && i < 10);
    return x;

    // An optimizing compiler MIGHT still remove the assert.
    // While the explicit bounds check is gone, a C compiler
    // might assume the program is well-formed (given it has
    // no contradicting fact), and since well-formed programs
    // won't access out-of-bounds array elements, the
    // optimizer reasons that `i >= 0 && i < 10` and the
    // assert is always true. Your compiler's optimizer
    // might not remove this assert, but another's might.

    // So if the assert here might be removed, how can you
    // catch a bad value of `i`? There are two good answers:
    // 1. The assert should *precede* the array dereference.
    //    Asserts must execute *before* the code they are
    //    meant to protect.
    // 2. Modern compilers ship with optional *sanitizers*,
    //    enabled in our Makefiles when you say `make SAN=1`,
    //    that can detect problems like undefined behavior.
    //    For the undefined behaviors that sanitizers cannot
    //    catch at compile time, they will insert checks into
    //    your executable, and these checks will slow down
    //    your program's execution.  Most of the time, this
    //    is a small price to pay to have your work checked
    //    and avoid hours debugging the craziness that can
    //    result from undefined behavior.
}

int signed_inc(int x) {
    // Modern compilers will remove this assert because of
    // undefined behavior reasoning: signed integer overflow
    // is undefined behavior, so the compiler may assume
    // that `x + 1` never overflows when `x` is signed.
    assert(x + 1 > x);
    return x + 1;
}

int safe_signed_inc(int x) {
    // Unsigned integer overflow is *defined* behavior, so
    // this assertion will always execute.
    assert((int) ((unsigned) x + 1) > x);
    return x + 1;
}

void realloc_error(void) {
    int* p = (int*) malloc(sizeof(int));
    int* q = (int*) realloc(p, sizeof(int));
    *p = 1;
    *q = 2;
    if (p == q) {
        printf("%d %d\n", *p, *q);
    }
    // Optimized clang will print `1 2`, which is crazy!
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./ubexplore TEST N\n");
        exit(1);
    }

    int x = strtol(argv[2], NULL, 0);

    // Run optimized & unoptimized versions, and try with
    // & without SANITIZE=1.
    if (strcmp(argv[1], "access1") == 0) {
        printf("access1(%d) = %d\n", x, access1(x));
    } else if (strcmp(argv[1], "access2") == 0) {
        printf("access2(%d) = %d\n", x, access2(x));
    } else if (strcmp(argv[1], "inc") == 0) {
        printf("%d + 1 = %d\n", x, x + 1);
    } else if (strcmp(argv[1], "inc2") == 0) {
        printf("signed_inc(%d) = %d\n", x, signed_inc(x));
    } else if (strcmp(argv[1], "inc3") == 0) {
        printf("safe_signed_inc(%d) = %d\n", x, safe_signed_inc(x));
    } else if (strcmp(argv[1], "realloc") == 0) {
        realloc_error();
    } else {
        fprintf(stderr, "Unknown test (expected access1, access2, inc, inc2, inc3, or realloc)\n");
    }
}
