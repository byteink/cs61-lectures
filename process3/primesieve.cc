#include "helpers.hh"

void add_filter(const char* const* argv) {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r >= 0);

    pid_t pid = fork();
    assert(pid >= 0);

    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(argv[0], (char**) argv);
        assert(0);
    }

    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
}

int main(int argc, char**) {
    if (argc != 1) {
        fprintf(stderr, "Usage: seq 2 N | ./primesieve\n");
        fprintf(stderr, "Prints primes between 2 and N.\n");
        exit(1);
    }

    // We never want buffering on stdin or stdout.
    setvbuf(stdin, nullptr, _IONBF, 0);
    setvbuf(stdout, nullptr, _IONBF, 0);

    // sieve of Eratosthenes!
    // Assume initial standard input is a sequence of integers
    // starting from 2.

    // Repeatedly:
    // 1. Read a number (the next prime)
    // 2. Cross off all multiples of that number by
    //    introducing another filter
    int previous_prime = 1, next_prime;
    while (scanf("%d", &next_prime) == 1) {
        assert(previous_prime < next_prime);
        printf("%d\n", next_prime);
        previous_prime = next_prime;

        char buf[20];
        sprintf(buf, "%d", next_prime);
        const char* argv[] = { "./filtermultiples", buf, nullptr };
        add_filter(argv);
    }
}
