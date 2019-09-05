#include <cstdio>
#include <cstdlib>
#include <climits>

extern int8_t add(int8_t a, int8_t b);

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: add A B\n\
    Prints A + B.\n");
        exit(1);
    }

    int8_t a = (int8_t) strtol(argv[1], 0, 0);
    int8_t b = (int8_t) strtol(argv[2], 0, 0);

    printf("%d + %d = %d\n", a, b, add(a, b));
}
