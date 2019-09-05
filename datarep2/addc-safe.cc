#include <cstdio>
#include <cstdlib>
#include <cinttypes>

extern int8_t add(int8_t a, int8_t b);

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: add A B\n\
    Prints A + B.\n");
        exit(1);
    }

    int ai = strtol(argv[1], 0, 0);
    int bi = strtol(argv[2], 0, 0);
    if (ai > INT8_MAX || ai < INT8_MIN ||
        bi > INT8_MAX || bi < INT8_MIN) {
        fprintf(stderr, "Error: A and B must fit in an int8_t\n");
        exit(1);
    }

    int8_t a = (int8_t) ai;
    int8_t b = (int8_t) bi;
    printf("%d + %d = %d\n", a, b, add(a, b));
}
