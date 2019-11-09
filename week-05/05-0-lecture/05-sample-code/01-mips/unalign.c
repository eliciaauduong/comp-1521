#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t bytes[32];
    uint32_t *i = (int *)bytes[1];
    *i = 0x03040506;   // store will not be aligned on a 4-byte boundary
    printf("%d\n", bytes[1]);
}