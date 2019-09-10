#include "hexdump.hh"

void func() {
    char* ptrs[10];

    for (int i = 0; i != 10; ++i) {
        ptrs[i] = new char[i + 1];
    }

    for (int i = 0; i != 10; ++i) {
        delete[] ptrs[i];
    }
}

int main() {
    func();
}
