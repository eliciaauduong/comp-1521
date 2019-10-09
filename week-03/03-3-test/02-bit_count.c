// count bits in a uint64_t
// Test 03 - Tuesday 8 October
// Elicia AU DUONG - z5260173

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define BITS 64

// return how many 1 bits value contains
int bit_count(uint64_t value) {

    int count = 0; // set a counter for the number of 1 bits
    uint64_t mask = 1; // set a mask to check each bit of the value
    
    for (int i = 0; i < BITS; i++) { // for every bit in the value
        if (mask & value) { // if the bit is equal to 1
            count++; // increase the count of 1 bits
        }
        mask <<= 1; // move to the next bit
    }

    return count;
}