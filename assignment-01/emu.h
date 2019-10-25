////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <stdint.h>

#ifndef CS1521_ASS1__EMU_H
#define CS1521_ASS1__EMU_H

//
// You need to write these functions.  See the specification for details.
//
int execute_instruction(uint32_t instruction, uint32_t *program_counter);
void print_instruction(uint32_t instruction);

#endif // !defined(CS1521_ASS1__EMU_H)