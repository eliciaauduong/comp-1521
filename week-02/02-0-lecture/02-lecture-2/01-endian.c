#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//
// use a union to alias uint16_t, uint32_t,uint64_t types
// to an array of bytes so we can see order (endian-ness)
// bytes of integer type stored in memory
//
// what this program prints vary between platforms:
// https://en.wikipedia.org/wiki/Endianness
// CSE machines are little-endian
//

union overlay {
    uint16_t s;
    uint32_t i;
    uint64_t l;
    uint8_t  bytes[8];
};

void print_bytes(char *message, void *v, int n);

int main(void) {
    union overlay u = {.l = 0};

    u.s = 0x1234;
    print_bytes("uint16_t s = 0x1234            ", u.bytes, 2); // @cse prints 34 12
    u.i = 0x12345678;
    print_bytes("uint32_t i = 0x12345678        ", u.bytes, 4); // @cse prints 78 56 34 12
    u.l = 0x123456789abcdef0;
    print_bytes("uint64_t l = 0x123456789abcdef0", u.bytes, 8); // @cse prints f0 de bc 9a 78 56 34 12

    if (u.bytes[0] == 0xf0) {
        printf("little-endian machine\n");
    } else if (u.bytes[0] == 0x01) {
        printf("big-endian machine\n");
    } else {
        printf("unusual machine\n");
    }
}


void print_bytes(char *message, void *v, int n) {
    uint8_t *p = v;
    printf("%s, bytes[0..%d] = ", message, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%02x ", p[i]);
    }
    printf("\n");
}