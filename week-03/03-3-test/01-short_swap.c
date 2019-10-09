// Swap bytes of a short
// Test 03 - Tuesday 8 October
// Elicia AU DUONG - z5260173


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define MASK 255
#define BYTE 8

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {

    uint16_t mask = MASK; // mask to get the right-most 8 bits (1 byte)
    uint16_t new = 0; // value to store new number

    uint16_t v1 = value & mask; // get the second byte of the value
    mask <<= BYTE; // move to get the other byte
    new = new | v1 << BYTE; // store the second byte in the first place
    uint16_t v2 = value & mask; // get the first byte of the value
    new = new | v2 >> BYTE; // store the first byte in the second place
    
    return new;
}