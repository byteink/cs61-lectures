#include "unistd.h"
#include "stdio.h"
#include "assert.h"

void choose_red(const char *text) {
    // Use syscalls, which are atomic
    for (int i = 0; i != 1000000; ++i) {
        int r = write(1, text, 5);
        (void)r;
    }
    _exit(0);
}

int main(int argc, char* argv[]) {
    bool use_stdio = true;
    if (argc > 1 && argv[1][1] == 'a') {
        use_stdio = false;
    }

    pid_t p1 = fork();
    assert(p1 >= 0);

    const char* text;
    if (p1 == 0) {
        text = "BABY\n";
    } else {
        text = "mama\n";
    }

    if (!use_stdio) {
        choose_red(text);
    }

    for (int i = 0; i != 1000000; ++i) {
        fputs(text, stdout);
    }
}
