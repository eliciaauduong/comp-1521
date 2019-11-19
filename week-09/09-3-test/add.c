// return the MIPS opcode for add $d, $s, $t
// Test 09 - Tuesday 19 November
// Elicia AU DUONG - z5260173

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

uint32_t add(uint32_t d, uint32_t s, uint32_t t) {

    // 000000ssssstttttddddd00000100000
    
    uint32_t code = 0x00000020; // opcode for add
    uint32_t mask = 31; // get digits for d, s, t
    
    code = code | ((mask & d) << 11);
    code = code | ((mask & t) << 16); 
    code = code | ((mask & s) << 21);
    
    return code;

}