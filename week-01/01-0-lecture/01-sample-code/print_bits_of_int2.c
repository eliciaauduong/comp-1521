// Print binary representation of ints
#include <stdio.h>

void print_bits(int value);
int get_nth_bit(int value, int n);

int main(void) {
    int a = 0;
    printf("Enter an int: ");
    scanf("%d", &a);
    print_bits(a);
    printf("\n");
    return 0;
}

// print the binary representation of a value
void print_bits(int value) {
    // sizeof returns size in bytes and 1 byte == 8 bits
    int how_many_bits = 8 * (sizeof value);
    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
}

// extract the nth bit from a value
int get_nth_bit(int value, int n) {
    return (value >> n) & 1;
}