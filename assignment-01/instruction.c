////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  COMP1521 - Computer Systems Fundamentals                                  //
//  Elicia AU DUONG - z5260173                                                //
//  ---                                                                       //
//  Assignment 1: emu, A MIPS Emulator (PART 1 & 2)                           //
//  instruction.c                                                             //
//                                                                            //
//  implementation of functions declared in instruction.h                     //
//  instructions sorted by opcode patterns                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include "instruction.h"

// Extract registers / numbers from a given instruction
uint32_t extractNum(char num, uint32_t instruction) {
    uint32_t result = 0;
    if (num == 's') {
        uint32_t s = 0x03E00000;
        result = (s & instruction) >> 21;
    } else if (num == 't') {
        uint32_t t = 0x001F0000;
        result = (t & instruction) >> 16;
    } else if (num == 'd') {
        uint32_t d = 0x0000F800;
        result = (d & instruction) >> 11;
    } else if (num == 'i') {
        uint32_t i = 0x000007C0;
        result = (i & instruction) >> 6;
    } else if (num == 'b') {
        uint32_t b = instruction & 0x0000FFFF;
        result = is_negative(b);
    } else if (num == 'x') {
        result = instruction & 0x3FFFFFF;
    }

    return result;
}

// Check if a number is negative and convert to negative
int32_t is_negative(uint32_t num) {
    uint32_t negative = num & 0x00008000;
    if (negative == 0x00008000) {
        int32_t neg = num ^ 0x0000ffff;
        neg = neg + 1;
        neg = 0 - neg;
        return neg;
    }
    return num;
}

// Check if a number is negative and convert to negative
// Specifically for load instructions
int32_t l_negative(char l, uint32_t num) {
    if (l == 'b') {
        uint32_t negative = num & 0x00000080;
        if (negative == 0x00000080) {
            int32_t neg = num ^ 0x000000ff;
            neg = neg + 1;
            neg = 0 - neg;
            return neg;
        } 
    } else if (l == 'h') {
        uint32_t negative = num & 0x00008000;
        if (negative == 0x00008000) {
            int32_t neg = num ^ 0x0000ffff;
            neg = neg + 1;
            neg = 0 - neg;
            return neg;
        } 
    }
    return num;
}

////////////////////////////////////////////////////////////////////////////////
//              Code Pattern 1: 111111xxxxxxxxxxxxxxx11111111111              //
////////////////////////////////////////////////////////////////////////////////

// Execute add instruction
// add $d, $s, $t
// d = s + t
void addInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t sum = x + y;
    set_register(d, sum);

    (*program_counter) += 4;
}

// Execute sub instruction
// sub $d, $s, $t
// d = s - t
void subInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t diff = x - y;
    set_register(d, diff);

    (*program_counter) += 4;
}

// Execute mul instruction
// mul $d, $s, $t
// d = s * t
void mulInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t mul = x * y;
    set_register(d, mul);

    (*program_counter) += 4;
}

// Execute and instruction
// and $d, $s, $t
// d = s & t
void andInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = x & y;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute or instruction
// or $d, %s, $t
// d = s | t
void orInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = x | y;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute xor instruction
// xor $d, %s, $t
// d = s ^ t
void xorInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = x ^ y;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute sllv instruction
// sllv $d, $t, $s
// d = s << t
void sllvInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = x << y;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute srlv instruction
// srlv $d, $t, $s
// d = s >> t
void srlvInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = x >> y;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute slt instruction
// slt $d, $s, $t
// d = (s < t)
void sltInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t val = (x < y);
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute jr instruction
// jr $s
// PC = s
void jrInstr(uint32_t s, uint32_t *program_counter) {
    (*program_counter) = s;
}

// Execute syscall instruction
// syscall
// determined by $v0
void syscallInstr(uint32_t *program_counter) {
    uint32_t reg = get_register(v0);
    uint32_t arg = get_register(a0);
    if (reg == 1) {                                     // print integer
        printf("%d", arg);
    } else if (reg == 4) {                              // print string
        arg = get_register(a0);
        int i = 0;
        int c = get_byte(arg + i);
        while(c != '\0') {
            printf("%c", c);
            i++;
            c = get_byte(arg + i);
        }
    } else if (reg == 5) {                              // read integer
        uint32_t num = 0;
        scanf("%d", &num);
        set_register(v0, num);
        printf("%d", get_register(v0));
    } else if (reg == 8) {                              // read string
        char *str = NULL;
        uint32_t size = get_register(a1);
        int i = 0;
        int zeroFill = 0;
        scanf("%s", str);
        while (i < size) {
            if (str[i-1] == '\n' || zeroFill == 1) {
                set_byte(arg+i,0);
                zeroFill = 1;
            } else {
                set_byte(arg+i,str[i]);
            }
            i++;
        }
    } else if (reg == 10) {                             // exit
        exit(0);
    } else if (reg == 11) {                             // print character
        printf("%c", arg);
    } else if (reg == 12) {                             // read character
        char c = 0;
        scanf("%c", &c);
        set_register(v0, (uint32_t)c);
    }
    
    (*program_counter) += 4;
}

////////////////////////////////////////////////////////////////////////////////
//              Code Pattern 2: 111111xxxxxxxxxxxxxxxxxxxxxxxxxx              //
////////////////////////////////////////////////////////////////////////////////

// Execute addi instruction
// addi $t, $s, I
// t = s + I
void addiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t result = x + I;
    set_register(t, result);

    (*program_counter) += 4;
}

// Execute andi instruction
// andi $t, $s, I
// t = s & I
void andiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t val = x & I;
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute ori instruction
// ori $t, $s, I
// t = s | I
void oriInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t val = x | I;
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute xori instruction
// xori $t, $s, I
// t = s ^ I
void xoriInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t val = x ^ I;
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute slti instruction
// slti $t, $s, I
// t = (s < I)
void sltiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t val = (x < I);
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute lui instruction
// lui $t, I
// t = I << 16
void luiInstr(uint32_t t, uint32_t I, uint32_t *program_counter) {
    uint32_t val = I << 16;
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute lb instruction
// lb $t, O($b)
// t = *(int8*)(b + O)
void lbInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t val = get_byte(x + O);
    val = l_negative('b', val);
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute lh instruction
// lh $t, O($b)
// t = *(int16*)(b + O) 
void lhInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t byte1 = get_byte(x + O);
    uint32_t byte2 = (get_byte(x + O + 1) << 8);
    uint32_t val = byte1 + byte2;
    val = l_negative('h', val);
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute lw instruction
// lw $t, O($b)
// t = *(int32*)(b + O) 
void lwInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t byte1, byte2, byte3, byte4 = 0;
    uint32_t result1 = x + O;
    uint32_t result2 = get_byte(x) + O;
    if (get_byte(result1) >= 0xff) {
        byte1 = (result2);
    } else {
        byte1 = (get_byte(result1));
    }
    if (get_byte(result1 + 1) >= 0xff) {
        byte2 = (result2 + 1) << 8;
    } else {
        byte2 = (get_byte(result1 + 1) << 8);
    }
    if (get_byte(result1 + 2) >= 0xff) {
        byte3 = (result2 + 2) << 16;
    } else {
        byte3 = (get_byte(result1 + 2) << 16);
    }
    if (get_byte(result1 + 3) >= 0xff) {
        byte4 = (result2 + 3) << 24;
    } else {
        byte4 = (get_byte(result1 + 3) << 24);
    }
    uint32_t val = byte1 + byte2 + byte3 + byte4;
    set_register(t, val);

    (*program_counter) += 4;
}

// Execute sb instruction
// sb $t, O($b)
// *(uint8*)(b + O) = (t & 0xff) 
void sbInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t val = x + O;
    set_byte(val, (get_register(t) & 0xff));
    
    (*program_counter) += 4;
}

// Execute sh instruction
// sh $t, O($b)
// / *(uint16*)(b + O) = (t & 0xffff) 
void shInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t val = x + O;
    set_byte(val, (get_register(t) & 0x00ff));
    val = x + O + 1;
    set_byte(val, (get_register(t) & 0xff00));
    
    (*program_counter) += 4;
}

// Execute sw instruction
// sw $t, O($b)
// / *(uint32*)(b + O) = t 
void swInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter) {
    uint32_t x = get_register(b);
    uint32_t y = get_register(t);
    uint32_t val = x + O;
    set_byte(val, (y & 0x000000ff));
    val = x + O + 1;
    set_byte(val, (y & 0x0000ff00));
    val = x + O + 2;
    set_byte(val, (y & 0x00ff0000));
    val = x + O + 3;
    set_byte(val, (y & 0xff000000));
    
    (*program_counter) += 4;
}

// Execute beq instruction
// beq $s, $t, I
// if (s == t) PC += I<<2; else PC += 4; 
void beqInstr(uint32_t s, uint32_t t, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    if (x == y) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}

// Execute bne instruction
// bne $s, $t, I
// if (s != t) PC += I<<2; else PC += 4; 
void bneInstr(uint32_t s, uint32_t t, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    if (x != y) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}

// Execute j instruction
// j X
// PC = (PC & 0xF0000000) | (X << 2) 
void jInstr(uint32_t X, uint32_t *program_counter) {
    (*program_counter) = ((*program_counter) & 0xF0000000) | (X << 2);
}

// Execute jal instruction
// jal X
// $ra = PC + 4; PC = (PC & 0xF0000000) | (X << 2) 
void jalInstr(uint32_t X, uint32_t *program_counter) {
    set_register(ra, (*program_counter) + 4);
    (*program_counter) = ((*program_counter) & 0xF0000000) | (X << 2);
}

////////////////////////////////////////////////////////////////////////////////
//              Code Pattern 3: 11111111111xxxxxxxxxxxxxxx111111              //
////////////////////////////////////////////////////////////////////////////////

// Execute sll instruction
// $d, $t, I
// d = t << I
void sllInstr(uint32_t d, uint32_t t, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(t);
    uint32_t val = x << I;
    set_register(d, val);

    (*program_counter) += 4;
}

// Execute srl instruction
// $d, $t, I
// d = t >> I
void srlInstr(uint32_t d, uint32_t t, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(t);
    uint32_t val = x >> I;
    set_register(d, val);

    (*program_counter) += 4;
}

////////////////////////////////////////////////////////////////////////////////
//              Code Pattern 4: 111111xxxxx11111xxxxxxxxxxxxxxxx              //
////////////////////////////////////////////////////////////////////////////////

// Execute blez instruction
// blez $s, I
// if (s <= 0) PC += I<<2; else PC += 4; 
void blezInstr(uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    if (x <= 0) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}

// Execute bgtz instruction
// bgtz $s, I
// if (s > 0) PC += I<<2; else PC += 4; 
void bgtzInstr(uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    if (x > 0) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}

// Execute bltz instruction
// bltz $s, I
// if (s < 0) PC += I<<2; else PC += 4;  
void bltzInstr(uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    if (x < 0) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}

// Execute bgez instruction
// bgez $s, I
// if (s >= 0) PC += I<<2; else PC += 4; 
void bgezInstr(uint32_t s, uint32_t I, uint32_t *program_counter) {
    uint32_t x = get_register(s);
    if (x >= 0) {
        (*program_counter) += (I << 2);
    } else {
        (*program_counter) += 4;
    }
}
