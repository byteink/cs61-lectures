#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.hh"

char global_ch = 'A';
const char const_global_ch = 'B';

void f() {
    char local_ch = 'C';
    char* allocated_ch = new char('D');

    hexdump(&global_ch, 1);
    hexdump(&const_global_ch, 1);
    hexdump(&local_ch, 1);
    hexdump(allocated_ch, 1);
}

int main() {
    f();
}
