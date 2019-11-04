////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  COMP1521 - Computer Systems Fundamentals                                  //
//  Elicia AU DUONG - z5260173                                                //
//  ---                                                                       //
//  Assignment 1: emu, A MIPS Emulator (PART 1)                               //
//  print_instruction.c                                                       //
//                                                                            //
//  print_instruction is given a MIPS instruction as a 32-bit unsigned        //
//  integer value. You need to add code to print_instruction which prints     //
//  out the assembler for the instruction.                                    //
//                                                                            //
//  instructions sorted by opcode patterns                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include "instruction.h"

// print assembler for a given 32-bit unsigned MIPS instruction
void print_instruction(uint32_t instruction) {
    // get the opcodes to differentiate each instruction
    // 111111xxxxxxxxxxxxxxx11111111111
    uint32_t code = instruction & 0xFC0007FF;
    // 111111xxxxxxxxxxxxxxxxxxxxxxxxxx
    uint32_t code1 = instruction & 0xFC000000;
    // 11111111111xxxxxxxxxxxxxxx111111
    uint32_t code2 = instruction & 0xFFE0003F;
    // 111111xxxxx11111xxxxxxxxxxxxxxxx
    uint32_t code3 = instruction & 0xFC1F0000;

    // get the registers / numbers from the instruction
    uint32_t s = extractNum('s', instruction);
    uint32_t t = extractNum('t', instruction);
    uint32_t d = extractNum('d', instruction);
    uint32_t i = extractNum('i', instruction);
    uint32_t b = extractNum('b', instruction);
    uint32_t x = extractNum('x', instruction);
    
    if (code == 0x00000020) {
        printf("add $%d, $%d, $%d", d, s, t);         // add instruction
    } else if (code == 0x00000022) {
        printf("sub $%d, $%d, $%d", d, s, t);         // sub instruction
    } else if (code == 0x70000002) {
        printf("mul $%d, $%d, $%d", d, s, t);         // mul instruction
    } else if (code == 0x00000024) {
        printf("and $%d, $%d, $%d", d, s, t);         // and instruction
    } else if (code == 0x00000025) {
        printf("or $%d, $%d, $%d", d, s, t);          // or instruction
    } else if (code == 0x00000026) {
        printf("xor $%d, $%d, $%d", d, s, t);         // xor instruction
    } else if (code == 0x00000004) {
        printf("sllv $%d, $%d, $%d", d, t, s);        // sllv instruction
    } else if (code == 0x00000006) {
        printf("srlv $%d, $%d, $%d", d, t, s);        // srlv instruction
    } else if (code == 0x0000002A) {
        printf("slt $%d, $%d, $%d", d, s, t);         // slt instruction
    } else if (code == 0x00000008) {
        printf("jr $%d", s);                          // jr instruction
    } else if (code == 0x0000000C) {
        printf("syscall");                            // syscall instruction
    }
    
    if (code1 == 0x20000000) {
        printf("addi $%d, $%d, %d", t, s, b);         // addi instruction
    } else if (code1 == 0x30000000) {
        printf("andi $%d, $%d, %d", t, s, b);         // andi instruction
    } else if (code1 == 0x34000000) {
        printf("ori $%d, $%d, %d", t, s, b);          // ori instruction
    } else if (code1 == 0x38000000) {
        printf("xori $%d, $%d, %d", t, s, b);         // xori instruction
    } else if (code1 == 0x28000000) {
        printf("slti $%d, $%d, %d", t, s, b);         // slti instruction   
    } else if (code1 == 0x3C000000) {
        printf("lui $%d, %d", t, b);                  // lui instruction
    } else if (code1 == 0x80000000) {
        printf("lb $%d, %d($%d)", t, b, s);           // lb instruction
    } else if (code1 == 0x84000000) {
        printf("lh $%d, %d($%d)", t, b, s);           // lh instruction
    } else if (code1 == 0x8C000000) {
        printf("lw $%d, %d($%d)", t, b, s);           // lw instruction
    } else if (code1 == 0xA0000000) {
        printf("sb $%d, %d($%d)", t, b, s);           // sb instruction
    } else if (code1 == 0xA4000000) {
        printf("sh $%d, %d($%d)", t, b, s);           // sh instruction
    } else if (code1 == 0xAC000000) {
        printf("sw $%d, %d($%d)", t, b, s);           // sw instruction
    } else if (code1 == 0x10000000) {
        printf("beq $%d, $%d, %d", s, t, b);          // beq instruction
    } else if (code1 == 0x14000000) {
        printf("bne $%d, $%d, %d", s, t, b);          // bne instruction
    } else if (code1 == 0x08000000) {
        printf("j 0x%x", x);                          // j instruction
    } else if (code1 == 0x0C000000) {
        printf("jal 0x%x", x);                        // jal instruction
    }
    
    if (code2 == 0x00000000) {
        printf("sll $%d, $%d, %d", d, t, i);          // sll instruction
    } else if (code2 == 0x00000002) {
        printf("srl $%d, $%d, %d", d, t, i);          // srl instruction
    }  
    
    if (code3 == 0x18000000) {
        printf("blez $%d, %d", s, b);                 // blez instruction
    } else if (code3 == 0x1C000000) {
        printf("bgtz $%d, %d", s, b);                 // bgtz instruction
    } else if (code3 == 0x04000000) {
        printf("bltz $%d, %d", s, b);                 // bltz instruction
    } else if (code3 == 0x04010000) {
        printf("bgez $%d, %d", s, b);                 // bgez instruction
    } 
}