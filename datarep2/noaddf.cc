#include <cinttypes>

int8_t add(int8_t a, int8_t b) {
    int8_t sum = 0, carry = 0;

    for (int i = 0; i < 8; ++i) {
        int8_t a_i = (a >> i) & 0x1;
        int8_t b_i = (b >> i) & 0x1;

        int8_t sum_i = a_i ^ b_i ^ carry;
        sum = sum | (sum_i << i);

        carry = (a_i & b_i) | (carry & (a_i ^ b_i));
    }

    return sum;   // a + b
}
