#include "helpers.hh"

void usage() {
    fprintf(stderr, "Usage: ./filtermultiples N\n");
    fprintf(stderr, "Reads integers from standard input; prints them except multiples of N.\n");
    exit(1);
}

int main(int argc, char** argv) {
    long p;
    if (argc != 2
        || (p = strtol(argv[1], nullptr, 0)) < 1) {
        usage();
    }

    long value;
    while (scanf("%ld", &value) == 1) {
        if (value % p != 0) {
            printf("%ld\n", value);
        }
    }
}
