#include <stdio.h>
#include <stdint.h>

int main(void) {
    // int16_t is a signed type (-32768..32767)
    // all operations below are defined for a signed type
    int16_t i; // go to an unsigned type for any bit operations

    i = -1;
    i = i >> 1; // undefined -  shift of a negative value
    printf("%d\n", i);
    printf("%x\n", i);
    
    i = -1;
    i = i << 1; // undefined -  shift of a negative value
    printf("%d\n", i);
    
    i = 32767;
    i = i << 1; // undefined -  left shift produces a negative value

    uint64_t j;
    j = 1 << 33; // undefined - 1 type is int
    j = ((uint64_t)1) << 33; // ok
    
    return 0;
}