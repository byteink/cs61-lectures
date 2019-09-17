#include "hexdump.hh"
#include <vector>

void func() {
    char a[5] = {'A', 'A', 'A', 'A', 'A'};
    std::vector<char> v{'B', 'B', 'B', 'B', 'B'};

    hexdump(&a, sizeof(a));
    hexdump(&v, sizeof(v));
    hexdump(v.data(), sizeof(v[0]) * v.size());
}

int main() {
    func();
}
