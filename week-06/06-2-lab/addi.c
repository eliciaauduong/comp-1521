////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  addi.c                                                                    //   
//  -----                                                                     //
//  Generate the opcode for an addi instruction                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    uint32_t code = 0x20000000; // opcode for addi
    uint16_t imm = i; // store i in a 16 bit int to preserve the sign
    
    code = code | (s << 21); // store s
    code = code | (t << 16); // store t
    code = code | imm; // store i
    
    return code;

}