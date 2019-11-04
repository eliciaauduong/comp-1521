// If you use C library functions add includes here.
#include <stdlib.h>

#include "emu.h"
#include "ram.h"
#include "registers.h"

/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t result)`
 * changes memory by `set_byte(uint32_t result, uint8_t value)`
 *
 * updates program_counter to result of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */

uint32_t transfer_to_negative(uint32_t whole);
void add(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void sub(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void mul(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void and(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void or(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void xor(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void sllv(uint32_t d,uint32_t t,uint32_t s,uint32_t whole,uint32_t*program_counter);
void srlv(uint32_t d,uint32_t t,uint32_t s,uint32_t whole,uint32_t*program_counter);
void slt(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter);
void addi(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void andi(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void ori(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void xori(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void sll(uint32_t d,uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter);
void srl(uint32_t d,uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter);
void slti(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void lui(uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter);
void lb(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void lh(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void lw(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void sb(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void sh(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void sw(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter);
void beq(uint32_t s,uint32_t t,uint16_t i,uint32_t whole,uint32_t*program_counter);
void bne(uint32_t s,uint32_t t,uint16_t i,uint32_t whole,uint32_t*program_counter);
void blez(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter);
void bgtz(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter);
void bltz(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter);
void bgez(uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter);
void j(uint32_t X,uint32_t whole,uint32_t*program_counter);
void jal(uint32_t X,uint32_t whole,uint32_t*program_counter);
void jr(uint32_t s,uint32_t whole,uint32_t*program_counter);
void syscall(uint32_t p1,uint32_t p2,uint32_t p3,uint32_t p4,uint32_t p5,uint32_t whole,uint32_t*program_counter);

int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

    // example code to implement add $4, $14, $12
    // uint32_t x = get_register(14);
    // uint32_t y = get_register(12);
    // uint32_t sum = x + y;
    // set_register(4, sum);


    // Update program_counter to result of next instructions
    // Most instructions will simply do the following:
    // (*program_counter) += 4;
    // Jump & Branch instructions will do something different

    uint32_t sec1 = instruction & 0xFC000000;
    uint32_t sec2 = instruction & 0x03E00000;
    uint32_t sec3 = instruction & 0x001F0000;
    uint32_t sec4 = instruction & 0x0000F800;
    uint32_t sec5 = instruction & 0x000007C0;

    uint32_t sec56 = instruction & 0x0000ffff;
    uint32_t sec23456 = instruction & 0x03ffffff;

    sec1 = sec1 >> 26;
    sec2 = sec2 >> 21;
    sec3 = sec3 >> 16;
    sec4 = sec4 >> 11;
    sec5 = sec5 >> 6;

    if ((instruction & 0xFC0007FF) == 0x00000020){            // add instruction
        add(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000022){     // sub instruction
        sub(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x70000002){     // mul instruction
        mul(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000024){     // and instruction
        and(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000025){     //  or instruction
        or(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000026){     // xor instruction
        xor(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000004){     //sllv instruction
        sllv(sec4, sec3, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x00000006){     //srlv instruction
        srlv(sec4, sec3, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC0007FF) == 0x0000002A){     // slt instruction
        slt(sec4, sec2, sec3,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x20000000){     //addi instruction
        if ((sec56 & 0x00008000) == 0x00008000){              // need to transfer to negative number
            uint32_t xor = instruction ^ 0x0000ffff;
            xor = xor + 1;
            xor = 0 - xor;
            sec56 = xor;
        }
        addi(sec3, sec2, sec56, instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x30000000){     //andi instruction
        andi(sec3, sec2, sec56, instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x34000000){     // ori instruction
        ori(sec3, sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x38000000){     //xori instruction
        xori(sec3, sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFFE0003F) == 0x00000000){     // sll instruction
        sll(sec4, sec3, sec5,instruction,program_counter);
    } else if ((instruction & 0xFFE0003F) == 0x00000002){     // srl instruction
        srl(sec4, sec3, sec5,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x28000000){     //slti instruction
        slti(sec3, sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFFE00000) == 0x3C000000){     // lui instruction
        if ((sec56 & 0x00008000) == 0x00008000){              // need to transfer to negative number
            uint32_t xor = instruction ^ 0x0000ffff;
            xor = xor + 1;
            xor = 0 - xor;
            sec56 = xor;
        }
        lui(sec3, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x80000000){     //  lb instruction
        lb(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x84000000){     //  lh instruction
        lh(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x8C000000){     //  lw instruction
        lw(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0xA0000000){     //  sb instruction
        sb(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0xA4000000){     //  sh instruction
        sh(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0xAC000000){     //  sw instruction
        sw(sec3, sec56, sec2,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x10000000){     // beq instrction
        sec56 = sec56 | 0xffff0000;
//        printf("beq $%d, %u\n", sec2, sec56);
        beq(sec2, sec3, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x14000000){     // bne instruction
        sec56 = sec56 | 0xffff0000;
//        printf("bne $%d, %u\n", sec2, sec56);
        bne(sec2, sec3, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC1F0000) == 0x18000000){     //blez instruction
        sec56 = sec56 | 0xffff0000;
//        printf("blez $%d, %u\n", sec2, sec56);
        blez(sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC1F0000) == 0x1C000000){     //bgtz instruction
        sec56 = sec56 | 0xffff0000;
//        printf("bgtz $%d, %u\n", sec2, sec56);
        bgtz(sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC1F0000) == 0x04000000){     //bltz instruction
        sec56 = sec56 | 0xffff0000;
//        printf("bltz $%d, %u\n", sec2, sec56);
        bltz(sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC1F0000) == 0x04010000){     //bgez instruction
        sec56 = sec56 | 0xffff0000;
//        printf("bgez $%d, %u\n", sec2, sec56);
        bgez(sec2, sec56,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x08000000){     //   j instruction
        j(sec23456,instruction,program_counter);
    } else if ((instruction & 0xFC000000) == 0x0C000000){     // jal instruction
        jal(sec23456,instruction,program_counter);
    } else if ((instruction & 0xFC1FFFFF) == 0x00000008){     //  jr instruction
        jr(sec2,instruction,program_counter);
    } else if ((instruction & 0xFFFFFFFF) == 0x0000000C){     //syscall instruction
        syscall(sec1,sec2,sec3,sec4,sec5,instruction,program_counter);
    }


    // 0 should be returned, unless an exit syscall is executed
    return 0;
}

// PUT EXTRA FUNCTIONS HERE

void add(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x + y;
    set_register(d, result);

    (*program_counter) += 4;
}

void sub(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x - y;
    set_register(d, result);

    (*program_counter) += 4;
}

void mul(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x * y;
    set_register(d, result);

    (*program_counter) += 4;
}

void and(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x & y;
    set_register(d, result);

    (*program_counter) += 4;
}

void or(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x | y;
    set_register(d, result);

    (*program_counter) += 4;
}

void xor(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = x ^ y;
    set_register(d, result);

    (*program_counter) += 4;
}

void sllv(uint32_t d,uint32_t t,uint32_t s,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(t);
    uint32_t y = get_register(s);
    uint32_t result = x << y;
    set_register(d, result);

    (*program_counter) += 4;
}

void srlv(uint32_t d,uint32_t t,uint32_t s,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(t);
    uint32_t y = get_register(s);
    uint32_t result = x >> y;
    set_register(d, result);

    (*program_counter) += 4;
}

void slt(uint32_t d,uint32_t s,uint32_t t,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = get_register(t);
    uint32_t result = (x < y);
    set_register(d, result);

    (*program_counter) += 4;
}

void addi(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = i;
    uint32_t result = x + y;
    set_register(t, result);

    (*program_counter) += 4;
}

void andi(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = i;
    uint32_t result = x & y;
    set_register(t, result);

    (*program_counter) += 4;
}

void ori(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = i;
    uint32_t result = x | y;
    set_register(t, result);

    (*program_counter) += 4;
}

void xori(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = i;
    uint32_t result = x ^ y;
    set_register(t, result);

    (*program_counter) += 4;
}

void sll(uint32_t d,uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(t);
    uint32_t y = i;
    uint32_t result = x << y;
    set_register(d, result);

    (*program_counter) += 4;
}

void srl(uint32_t d,uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(t);
    uint32_t y = i;
    uint32_t result = x >> y;
    set_register(d, result);

    (*program_counter) += 4;
}

void slti(uint32_t t,uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(s);
    uint32_t y = i;
    uint32_t result = (x < y);
    set_register(t, result);

    (*program_counter) += 4;
}

void lui(uint32_t t,uint32_t i,uint32_t whole,uint32_t*program_counter){
    uint32_t x = i;
    uint32_t result = x << 16;
    set_register(t,result);

    (*program_counter) += 4;
}

void lb(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = get_byte(x+y);
//    printf("lb result == %x\n", result);
    set_register(t,result);

    (*program_counter) += 4;
}

void lh(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = get_byte(x+y);
    result = result + (get_byte(x+y+1) << 8);
//    printf("lh result == %x\n", result);

    set_register(t,result);

    (*program_counter) += 4;
}

void lw(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = get_byte(x+y);
    result = result + (get_byte(x+y+1) << 8);
    result = result + (get_byte(x+y+2) << 16);
    result = result + (get_byte(x+y+3) << 24); 
//    printf("lw result == %x\n", result);
    set_register(t,result);

    (*program_counter) += 4;
}

void sb(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = x + y;
    set_byte(result,(get_register(t) & 0xff));

    (*program_counter) += 4;
}

void sh(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = x + y;
    set_byte(result,(get_register(t) & 0xff));
    result = x + y + 1;
    set_byte(result,(get_register(t) & 0xff00));

    (*program_counter) += 4;
}

void sw(uint32_t t,uint32_t o,uint32_t b,uint32_t whole,uint32_t*program_counter){
    uint32_t x = get_register(b);
    uint32_t y = o;
    uint32_t result = x + y;
    set_byte(result,(get_register(t) & 0xff));
    result = x + y + 1;
    set_byte(result,(get_register(t) & 0xff00));
    result = x + y + 2;
    set_byte(result,(get_register(t) & 0xff0000));
    result = x + y + 3;
    set_byte(result,(get_register(t) & 0xff000000));

    (*program_counter) += 4;
}

void beq(uint32_t s,uint32_t t,uint16_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) == get_register(t)){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void bne(uint32_t s,uint32_t t,uint16_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) != get_register(t)){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void blez(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) < 0){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void bgtz(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) > 0){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void bltz(uint32_t s,uint16_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) <= 0){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void bgez(uint32_t s,uint32_t i,uint32_t whole,uint32_t*program_counter){
    if (get_register(s) >= 0){
        (*program_counter) += (i << 2);
    }else{
        (*program_counter) += 4;
    }
}

void j(uint32_t X,uint32_t whole,uint32_t*program_counter){
    (*program_counter) = (*program_counter & 0xf0000000) | (X << 2);
}

void jal(uint32_t X,uint32_t whole,uint32_t*program_counter){
    set_register(31, *program_counter + 4);
    (*program_counter) = (*program_counter & 0xf0000000) | (X << 2);
}

void jr(uint32_t s,uint32_t whole,uint32_t*program_counter){
    (*program_counter) = s;
}

void syscall(uint32_t p1,uint32_t p2,uint32_t p3,uint32_t p4,uint32_t p5,uint32_t whole,uint32_t*program_counter){

    uint32_t request = get_register(2);         //get $v0
    uint32_t work    = get_register(4);         //get $a0

    if (request == 1){
        printf("%d", work);
    }else if (request == 4){
        uint32_t address = get_register(4);
        for(int count = 0;get_byte(address + count) != '\0';count++){
            char curr = get_byte(address + count);
            printf("%c", curr);
        }
    }else if (request == 5){
        int scan = 0;
        scanf("%d",&scan);
        set_register(2,(uint32_t)scan);
    }else if (request == 8){
        char *string = NULL;
        uint32_t address = get_register(4);
        uint32_t length = get_register(5);
        scanf("%s\n",string);
        for(int i = 0;i < length;i++){
            set_byte(address+i,string[i]);
        }
    }else if (request == 10){
        exit(0);
    }else if (request == 11){
        printf("%c", work);
    }else if (request == 12){
        char scan = 0;
        scanf("%c",&scan);
        set_register(2,(uint32_t)scan);
    }

    (*program_counter) += 4;
}