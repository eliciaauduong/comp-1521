////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  COMP1521 - Computer Systems Fundamentals                                  //
//  Elicia AU DUONG - z5260173                                                //
//  ---                                                                       //
//  Assignment 1: emu, A MIPS Emulator (PART 2)                               //
//  execute_instruction.c                                                     //
//                                                                            //
//  get register values by calling                                            //
//      `get_register(register_type register_number)`                         //
//  change registers by calling                                               //
//      `set_register(register_type register_number, uint32_t value)`         //
//  get memory values by calling `get_byte(uint32_t address)`                 //
//  changes memory by calling `set_byte(uint32_t address, uint8_t value)`     //
//                                                                            //
//  updates program_counter to address of next instruction                    //
//  returns 1 if an exit syscall is executed, 0 otherwise                     //
//  instructions sorted by opcode patterns                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include "instruction.h"

// execute a given MIPS instruction and update the program counter
int execute_instruction(uint32_t instruction, uint32_t *program_counter) {
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
        addInstr(s, t, d, program_counter);              // add instruction
    } else if (code == 0x00000022) {
        subInstr(s, t, d, program_counter);              // sub instruction
    } else if (code == 0x70000002) {
        mulInstr(s, t, d, program_counter);              // mul instruction
    } else if (code == 0x00000024) {
        andInstr(s, t, d, program_counter);              // and instruction
    } else if (code == 0x00000025) {
        orInstr(s, t, d, program_counter);               // or instruction
    } else if (code == 0x00000026) {
        xorInstr(s, t, d, program_counter);              // xor instruction
    } else if (code == 0x00000004) {
        sllvInstr(s, t, d, program_counter);             // sllv instruction
    } else if (code == 0x00000006) {
        srlvInstr(s, t, d, program_counter);             // srlv instruction
    } else if (code == 0x0000002A) {
        sltInstr(s, t, d, program_counter);              // slt instruction
    } else if (code == 0x00000008) {
        jrInstr(s, program_counter);                     // jr instruction
    } else if (code == 0x0000000C) {
        syscallInstr(program_counter);                   // syscall instruction
        if (get_register(v0) == 10) {
            return 1;
        }
    }  
    
    if (code1 == 0x20000000) {
        addiInstr(t, s, b, program_counter);             // addi instruction
    } else if (code1 == 0x30000000) {
        andiInstr(t, s, b, program_counter);             // andi instruction
    } else if (code1 == 0x34000000) {
        oriInstr(t, s, b, program_counter);              // ori instruction
    } else if (code1 == 0x38000000) {
        xoriInstr(t, s, b, program_counter);             // xori instruction
    } else if (code1 == 0x28000000) {
        sltiInstr(t, s, b, program_counter);             // slti instruction   
    } else if (code1 == 0x3C000000) {
        luiInstr(t, b, program_counter);                 // lui instruction
    } else if (code1 == 0x80000000) {
        lbInstr(t, b, s, program_counter);               // lb instruction
    } else if (code1 == 0x84000000) {
        lhInstr(t, b, s, program_counter);               // lh instruction
    } else if (code1 == 0x8C000000) {
        lwInstr(t, b, s, program_counter);               // lw instruction
    } else if (code1 == 0xA0000000) {
        sbInstr(t, b, s, program_counter);               // sb instruction
    } else if (code1 == 0xA4000000) {
        shInstr(t, b, s, program_counter);               // sh instruction
    } else if (code1 == 0xAC000000) {
        swInstr(t, b, s, program_counter);               // sw instruction
    } else if (code1 == 0x10000000) {
        beqInstr(s, t, b, program_counter);              // beq instruction
    } else if (code1 == 0x14000000) {
        beqInstr(s, t, b, program_counter);              // bne instruction
    } else if (code1 == 0x08000000) {
        jInstr(x, program_counter);                      // j instruction
    } else if (code1 == 0x0C000000) {
        jalInstr(x, program_counter);                    // jal instruction
    }

    if (code2 == 0x00000000) {
        sllInstr(d, t, i, program_counter);              // sll instruction
    } else if (code2 == 0x00000002) {
        srlInstr(d, t, i, program_counter);              // srl instruction
    }  

    if (code3 == 0x18000000) {
        blezInstr(s, b, program_counter);                // blez instruction
    } else if (code3 == 0x1C000000) {
        bgtzInstr(s, b, program_counter);                // bgtz instruction
    } else if (code3 == 0x04000000) {
        bltzInstr(s, b, program_counter);                // bltz instruction
    } else if (code3 == 0x04010000) { 
        bgezInstr(s, b, program_counter);                // bgez instruction
    } 

    // 0 should be returned, unless an exit syscall is executed
    return 0;
}