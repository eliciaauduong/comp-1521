// If you use C library functions add includes here.

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
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */
int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

    // example code to implement add $4, $14, $12
    uint32_t x = get_register(14);
    uint32_t y = get_register(12);
    uint32_t sum = x + y;
    set_register(4, sum);


    // Update program_counter to address of next instructions
    // Most instructions will simply do the following:
    (*program_counter) += 4;
    // Jump & Branch instructions will do something different


    // 0 should be returned, unless an exit syscall is executed
    return 0;
}

// PUT EXTRA FUNCTIONS HERE