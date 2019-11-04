#include <stdio.h>
#include <stdint.h>

uint32_t is_negative(uint32_t num);
uint32_t l_negative(char l, uint32_t num);

////////////////////////////////////////////////////////////////////////////////
//
//  Code Pattern 1: 
//  
////////////////////////////////////////////////////////////////////////////////

// Execute add instruction
// add $d, $s, $t
// d = s + t
void addInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute sub instruction
// sub $d, $s, $t
// d = s - t
void subInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute mul instruction
// mul $d, $s, $t
// d = s * t
void mulInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute and instruction
// and $d, $s, $t
// d = s & t
void andInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute or instruction
// or $d, %s, $t
// d = s | t
void orInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute xor instruction
// xor $d, %s, $t
// d = s ^ t
void xorInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute sllv instruction
// sllv $d, $t, $s
// d = s << t
void sllvInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute srlv instruction
// srlv $d, $t, $s
// d = s >> t
void srlvInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute slt instruction
// slt $d, %s, $t
// d = (s < t)
void sltInstr(uint32_t s, uint32_t t, uint32_t d, uint32_t *program_counter);

// Execute jr instruction
// jr %s
// PC = s
void jrInstr(uint32_t s, uint32_t *program_counter);

// Execute syscall instruction
// syscall
// determined by $v0
void syscallInstr(uint32_t *program_counter);

////////////////////////////////////////////////////////////////////////////////
//
//  Code Pattern 2: 
//  
////////////////////////////////////////////////////////////////////////////////

// Execute addi instruction
// addi $t, $s, I
// t = s + I
void addiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute andi instruction
// andi $t, $s, I
// t = s & I
void andiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute ori instruction
// ori $t, $s, I
// t = s | I
void oriInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute xori instruction
// xori $t, $s, I
// t = s ^ I
void xoriInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute slti instruction
// slti $t, $s, I
// t = (s < I)
void sltiInstr(uint32_t t, uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute lui instruction
// lui $t, I
// t = I << 16
void luiInstr(uint32_t t, uint32_t I, uint32_t *program_counter);

// Execute lb instruction
// lb $t, O($b)
// t = *(int8*)(b + O)
void lbInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute lh instruction
// lh $t, O($b)
// t = *(int16*)(b + O) 
void lhInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute lw instruction
// lw $t, O($b)
// t = *(int32*)(b + O) 
void lwInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute sb instruction
// sb $t, O($b)
// / *(uint8*)(b + O) = (t & 0xff) 
void sbInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute sh instruction
// sh $t, O($b)
// / *(uint16*)(b + O) = (t & 0xffff) 
void shInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute sw instruction
// sw $t, O($b)
// / *(uint32*)(b + O) = t 
void swInstr(uint32_t t, uint32_t O, uint32_t b, uint32_t *program_counter);

// Execute beq instruction
// beq $s, $t, I
// if (s == t) PC += I<<2; else PC += 4; 
void beqInstr(uint32_t s, uint32_t t, uint32_t I, uint32_t *program_counter);

// Execute bne instruction
// bne $s, $t, I
// if (s != t) PC += I<<2; else PC += 4; 
void bneInstr(uint32_t s, uint32_t t, uint32_t I, uint32_t *program_counter);

// Execute j instruction
// j X
// PC = (PC & 0xF0000000) | (X << 2) 
void jInstr(uint32_t X, uint32_t *program_counter);

// Execute jal instruction
// jal X
// $ra = PC + 4; PC = (PC & 0xF0000000) | (X << 2) 
void jalInstr(uint32_t X, uint32_t *program_counter);

////////////////////////////////////////////////////////////////////////////////
//
//  Code Pattern 3: 
//  
////////////////////////////////////////////////////////////////////////////////

// Execute sll instruction
// $d, $t, I
// d = t << I
void sllInstr(uint32_t d, uint32_t t, uint32_t I, uint32_t *program_counter);

// Execute srl instruction
// $d, $t, I
// d = t >> I
void srlInstr(uint32_t d, uint32_t t, uint32_t I, uint32_t *program_counter);

////////////////////////////////////////////////////////////////////////////////
//
//  Code Pattern 4: 
//  
////////////////////////////////////////////////////////////////////////////////

// Execute blez instruction
// blez $s, I
// if (s <= 0) PC += I<<2; else PC += 4; 
void blezInstr(uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute bgtz instruction
// bgtz $s, I
// if (s > 0) PC += I<<2; else PC += 4; 
void bgtzInstr(uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute bltz instruction
// bltz $s, I
// if (s < 0) PC += I<<2; else PC += 4;  
void bltzInstr(uint32_t s, uint32_t I, uint32_t *program_counter);

// Execute bgez instruction
// bgez $s, I
// if (s >= 0) PC += I<<2; else PC += 4; 
void bgezInstr(uint32_t s, uint32_t I, uint32_t *program_counter);
