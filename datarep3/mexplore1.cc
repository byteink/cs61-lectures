#include "hexdump.hh"

void func(int i) {
    if (i > 0) {
        func(i - 1);
    }

    // hexdump(&i, sizeof(i));
}

int main() {
    func(5);
}
