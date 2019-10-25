////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <stdio.h>
#include <stdint.h>

#ifndef CS1521_ASS1__RAM_H
#define CS1521_ASS1__RAM_H

//
// You can call these functions from `execute_instruction.c':
//
uint8_t get_byte(uint32_t address);
void set_byte(uint32_t address, uint8_t value);


//
// These functions are used in `emu.c' --- do not call these functions.
//
void read_program(FILE *f);
int  execute_next_instruction(uint32_t *program_counter);
void print_instruction_at_address(uint32_t address);
void print_program(void);
void print_text_segment(void);
void print_data_segment(void);
void print_stack_segment(void);

#endif // !defined(CS1521_ASS1__RAM_H)