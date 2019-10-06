// Demonstrate C bitwise operations

#include <stdio.h>

void print_bits_hex(char *description, short n);
void print_bits(short value);
int get_nth_bit(short value, int n);

int main(void) {
    short a = 0;
    printf("Enter a: ");
    scanf("%hd", &a);
    short b = 0;
    printf("Enter b: ");
    scanf("%hd", &b);
    printf("Enter c: ");
    int c = 0;
    scanf("%d", &c);
    print_bits_hex("     a = ", a);
    print_bits_hex("     b = ", b);
    print_bits_hex("    ~a = ", ~a); // bitwise negation, swap 0's and 1's
    print_bits_hex(" a & b = ", a & b); // bitwise and
    print_bits_hex(" a | b = ", a | b); // bitwise or
    print_bits_hex(" a ^ b = ", a ^ b); // exclusive or, if 1 in either, not both
    print_bits_hex("a >> c = ", a >> c); // right shift a by c 
    print_bits_hex("a << c = ", a << c); // left shift a by c
    // left shift zero fills, right shift undefined fills if signed else zero
    return 0;
}

// print description then binary, hex and decimal representation of value
void print_bits_hex(char *description, short value) {
    printf("%s", description);
    print_bits(value);
    printf(" = 0x%04x = %d\n", value & 0xFFFF, value);
}

// print the binary representation of a value
void print_bits(short value) {
    // sizeof returns size in bytes and 1 byte == 8 bits
    int how_many_bits = 8 * (sizeof value);
    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
}

// extract the nth bit from a value
int get_nth_bit(short value, int n) {
    return (value >> n) & 1;
}