#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/fcntl.h>

#define TESTFILE "coherence-test.txt"

void write_1() {
    FILE* f = fopen(TESTFILE, "w");
    fprintf(f, "CS 61 is terrible!\n");
    fclose(f);
}

void write_2() {
    FILE* f = fopen(TESTFILE, "w");
    fprintf(f, "CS 61 is awesome!!\n");
    fclose(f);
}


void read_using_stdio() {
    write_1();  // writes "CS 61 is terrible!\n"

    FILE* f = fopen(TESTFILE, "r");

    char buf[BUFSIZ];
    size_t nr = fread(buf, 1, 9, f);
    fwrite(buf, 1, nr, stdout);

    write_2();  // writes "CS 61 is awesome!!\n"

    nr = fread(buf, 1, BUFSIZ, f);
    fwrite(buf, 1, nr, stdout);

    fclose(f);
}

void read_using_syscalls() {
    write_1();  // writes "CS 61 is terrible!\n"

    int fd = open(TESTFILE, O_RDONLY);

    char buf[BUFSIZ];
    ssize_t nr = read(fd, buf, 9);
    fwrite(buf, 1, nr, stdout);

    write_2();  // writes "CS 61 is awesome!!\n"

    nr = read(fd, buf, BUFSIZ);
    fwrite(buf, 1, nr, stdout);

    close(fd);
}


static void usage() {
    fprintf(stderr, "Usage: ./coherence -s (stdio)  or  ./coherence -y (syscalls)\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    int which = 0;

    int opt;
    while ((opt = getopt(argc, argv, "sy")) != -1) {
        switch (opt) {
        case 's':
            which = 's';
            break;
        case 'y':
            which = 'y';
            break;
        default:
            usage();
        }
    }

    if (which == 's') {
        read_using_stdio();
    } else if (which == 'y') {
        read_using_syscalls();
    } else {
        usage();
    }
}
