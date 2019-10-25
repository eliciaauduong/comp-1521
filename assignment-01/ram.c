////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "emu.h"
#include "ram.h"

typedef struct memory_segment {
    uint32_t first_address;
    uint32_t last_address;
    uint8_t *bytes;
    struct memory_segment *next;
} memory_segment_t;

// segments chained with next pointers
static memory_segment_t *text_segment;
static memory_segment_t *data_segment;
static memory_segment_t *stack_segment;

static int in_segment(uint32_t address, memory_segment_t *segment);
static memory_segment_t *read_segment(FILE *f, uint32_t start_word,
                                      uint32_t finish_word, int is_text);
static memory_segment_t *create_segment(uint32_t start_word,
                                        uint32_t finish_word);
static void print_segment(memory_segment_t *segment);
static uint32_t word_n_repeats(memory_segment_t *segment, uint32_t address);
static uint32_t get_word(memory_segment_t *segment, uint32_t address);

static memory_segment_t *address2segment(uint32_t address) {
    for (memory_segment_t *s = text_segment; s != NULL; s = s->next) {
        if (address >= s->first_address && address <= s->last_address) {
            return s;
        }
    }
    fprintf(stderr, "invalid address used: %08X\n", address);
    return NULL;
}

uint8_t get_byte(uint32_t address) {
    memory_segment_t *s = address2segment(address);
    return s ? s->bytes[address - s->first_address] : 0;
}

void set_byte(uint32_t address, uint8_t value) {
    memory_segment_t *s = address2segment(address);
    if (s) {
        s->bytes[address - s->first_address] = value;
    }
}

void read_program(FILE *f) {
    uint32_t start_word, finish_word;

    assert(fscanf(f, ".text # %X .. %X\n", &start_word, &finish_word) == 2);
    text_segment = read_segment(f, start_word, finish_word, 1);

    assert(fscanf(f, ".data # %X .. %X\n", &start_word, &finish_word) == 2);
    data_segment = read_segment(f, start_word, finish_word, 0);

    stack_segment = create_segment(0x7FFF0000, 0x7FFFFFFF);

    text_segment->next = data_segment;
    data_segment->next = stack_segment;
}

void print_instruction_at_address(uint32_t address) {
    uint32_t word = get_word(text_segment, address);
    printf("[%08X] %08X ", address, word);
    print_instruction(word);
    printf("\n");
}

void print_program(void) {
    for (uint32_t address = text_segment->first_address;
         address < text_segment->last_address; address += 4)
        print_instruction_at_address(address);
}

static int in_segment(uint32_t address, memory_segment_t *segment) {
    return address >= segment->first_address &&
           address <= segment->last_address;
}

// returns -1 if outside text_segment before or after execution
// returns 1 for syscall exit
// returns 0 otherwise
int execute_next_instruction(uint32_t *program_counter) {
    if (!in_segment(*program_counter, text_segment)) {
        return -1;
    }

    uint32_t instruction = get_word(text_segment, *program_counter);

    if (execute_instruction(instruction, program_counter)) {
        return 1;
    }

    if (!in_segment(*program_counter, text_segment)) {
        return -1;
    }

    return 0;
}

static memory_segment_t *read_segment(
    FILE *f, uint32_t start_word, uint32_t finish_word, int is_text
) {
    memory_segment_t *segment = create_segment(start_word, finish_word);

    fscanf(f, ".word");
    if (finish_word - start_word == 0) {
        fgetc(f); // read newline
        fgetc(f); // read newline
    }
    // `spim -assemble` can output HALF WORD aligned finish_word
    // so we need to round up
    uint32_t n_words = 1 + (((finish_word - start_word) - 1) / 4);
    for (uint32_t w = 0; w < n_words; w++) {
        uint32_t word;
        assert(fscanf(f, "%X", &word) == 1);
        if (is_text && (word & 0xFA00003F) == 0x21) {
            word &= ~(uint32_t)1;
        }
        for (unsigned int b = 0; b < 4; b++) {
            segment->bytes[w * 4 + b] = (word >> (b * 8)) & 0xFF;
        }
        fgetc(f); // read ',' or newline
    }
    return segment;
}

static memory_segment_t *create_segment(
    uint32_t start_word, uint32_t finish_word
) {
    memory_segment_t *segment = malloc(sizeof *segment);
    assert(segment);
    segment->first_address = start_word;
    if (finish_word < start_word + 4) {
        // don't create empty segments
        finish_word = start_word + 4;
    }
    segment->last_address = finish_word - 1;
    segment->bytes = calloc(finish_word - start_word, 4);
    assert(segment->bytes);
    segment->next = NULL;
    return segment;
}

void print_text_segment(void) {
    print_segment(text_segment);
}

void print_data_segment(void) {
    print_segment(data_segment);
}

void print_stack_segment(void) {
    print_segment(stack_segment);
}

static void print_segment(memory_segment_t *segment) {
    for (uint32_t address = segment->first_address;
         address < segment->last_address; address += 4) {
        uint32_t word = get_word(segment, address);
        uint32_t repeat_count = word_n_repeats(segment, address);

        if (repeat_count > 3) {
            uint32_t last_address = address + repeat_count * 4;
            printf("[%08X..%08X] %08X\n", address, last_address, word);
            address = last_address;
        } else {
            printf("[%08X] %08X\n", address, word);
        }
    }
}

static uint32_t word_n_repeats(memory_segment_t *segment, uint32_t address) {
    uint32_t first_word = get_word(segment, address);
    unsigned int n_repeats = 0;
    for (uint32_t a = address + 4; a <= segment->last_address; a += 4) {
        if (get_word(segment, a) != first_word) {
            break;
        }
        n_repeats++;
    }
    return n_repeats;
}

static uint32_t get_word(memory_segment_t *segment, uint32_t address) {
    uint32_t word = 0;
    for (unsigned int b = 0; b < 4; b++) {
        uint32_t byte = segment->bytes[address - segment->first_address + b];
        word |= byte << (b * 8);
    }
    return word;
}