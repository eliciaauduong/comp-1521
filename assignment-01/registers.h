////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <stdint.h>

#ifndef CS1521_ASS1__REGISTERS_H
#define CS1521_ASS1__REGISTERS_H

#define N_REGISTERS 32
typedef enum register_type {
    zero,
    at,
    v0, v1,
    a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4, s5, s6, s7,
    t8, t9,
    k0, k1,
    gp,
    sp, fp, ra
} register_type;

//
// This array maps `register_type' values to a string name ---
//
//     assert(register_name_map[ra] == "$ra");
//
extern const char *const register_name_map[];

//
// You can call these functions from `execute_instruction.c':
//
uint32_t get_register(register_type register_number);
void set_register(register_type register_number, uint32_t value);


//
// These functions are used in `emu.c' --- do not call these functions.
//
void print_registers(void);

#endif // !defined(CS1521_ASS1__REGISTERS_H)