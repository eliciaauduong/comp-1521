// Gives the raw underlying bits of a float
#include <stdio.h>
#include <stdint.h>

union overlay {
    float f;
    uint32_t u;
};

int main(void) {
    float number = 3.1459;
    union overlay over;
    over.f = number;
    uint32_t bits = over.u;
    printf("%08x\n", bits);

}