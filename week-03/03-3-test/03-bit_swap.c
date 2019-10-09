// swap pairs of bits of a 64-bit value, using bitwise operators
// Test 03 - Tuesday 8 October
// Elicia AU DUONG - z5260173

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define BITS 32

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {

    uint64_t mask1 = 1; // set a mask to check each odd bit of the value
    uint64_t mask2 = 2; // set a mask to check each even bit of the value
    uint64_t num = 0; // set a value to store the number
    
    for (int i = 0; i < BITS; i++) { // check every pair of the value
        // swap each pair of values
        num = num | ((value & mask1) << 1); // move the odd digit to even pair
        mask1 <<= 2; // move to the next odd digit
        num = num | ((value & mask2) >> 1); // move the even digit to odd pair
        mask2 <<= 2; // move to the next even digit
    }   
    
    return num;
}