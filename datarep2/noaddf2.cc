#include <cinttypes>

int8_t add(int8_t a, int8_t b) {
    int8_t a_0 = a & 0x1;
    int8_t b_0 = b & 0x1;
    int8_t s_0 = a_0 ^ b_0;  // bit 0 is a half adder
    int8_t carry = a_0 & b_0;

    int8_t a_1 = (a >> 1) & 0x1;
    int8_t b_1 = (b >> 1) & 0x1;
    int8_t s_1 = a_1 ^ b_1 ^ carry;
    carry = (a_1 & b_1) | (carry & (a_1 ^ b_1));

    int8_t a_2 = (a >> 2) & 0x1;
    int8_t b_2 = (b >> 2) & 0x1;
    int8_t s_2 = a_2 ^ b_2 ^ carry;
    carry = (a_2 & b_2) | (carry & (a_2 ^ b_2));

    int8_t a_3 = (a >> 3) & 0x1;
    int8_t b_3 = (b >> 3) & 0x1;
    int8_t s_3 = a_3 ^ b_3 ^ carry;
    carry = (a_3 & b_3) | (carry & (a_3 ^ b_3));

    int8_t a_4 = (a >> 4) & 0x1;
    int8_t b_4 = (b >> 4) & 0x1;
    int8_t s_4 = a_4 ^ b_4 ^ carry;
    carry = (a_4 & b_4) | (carry & (a_4 ^ b_4));

    int8_t a_5 = (a >> 5) & 0x1;
    int8_t b_5 = (b >> 5) & 0x1;
    int8_t s_5 = a_5 ^ b_5 ^ carry;
    carry = (a_5 & b_5) | (carry & (a_5 ^ b_5));

    int8_t a_6 = (a >> 6) & 0x1;
    int8_t b_6 = (b >> 6) & 0x1;
    int8_t s_6 = a_6 ^ b_6 ^ carry;
    carry = (a_6 & b_6) | (carry & (a_6 ^ b_6));

    int8_t a_7 = (a >> 7) & 0x1;
    int8_t b_7 = (b >> 7) & 0x1;
    int8_t s_7 = a_7 ^ b_7 ^ carry;
    carry = (a_7 & b_7) | (carry & (a_7 ^ b_7));

    int8_t sum = (s_7 << 7) | (s_6 << 6) | (s_5 << 5) |
        (s_4 << 4) | (s_3 << 3) | (s_2 << 2) | (s_1 << 1) | s_0;
    return sum;   // a + b
}
