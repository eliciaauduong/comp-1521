#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t b;
    uint32_t u;

    u = 0x03040506;
    b = *(uint8_t *)&u;
    printf("%d\n", b); // prints 6 on a little-endian machine
}