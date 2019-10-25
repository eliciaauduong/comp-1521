////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "emu.h"
#include "ram.h"
#include "registers.h"

#define PATH_LENGTH 2048

typedef enum action {
    a_error,
    a_interactive,
    a_print,
    a_execute,
    a_print_file,
    a_execute_file
} action_t;

static action_t process_arguments(int argc, char *argv[],
                                  char *spim_asm_filename,
                                  char *spim_out_filename);
static int run_or_print_program(action_t action);
static void run_interactively(uint32_t *program_counter);
static bool run_command(uint32_t *program_counter, int *program_terminated);
static void step_program(uint32_t *program_counter, int *program_terminated);
static void run_program(uint32_t *program_counter, int *program_terminated);
static int get_command(void);

#define EMU_USAGE_MESSAGE                                                      \
    "Usage: emu <file.s>\n"                                                    \
    "   or: emu -p <instructions>\n"                                           \
    "   or: emu -e <instructions>\n"                                           \
    "   or: emu -P <file.s>\n"                                                 \
    "   or: emu -E <file.s>\n"                                                 \
    "\n"                                                                       \
    "Options:\n"                                                               \
    "    -p      print instructions from command-line\n"                       \
    "    -P      print instructions from file\n"                               \
    "    -e      execute instructions from command-line\n"                     \
    "    -E      execute instructions from file\n"                             \
    "\n"                                                                       \
    "With no options, `emu' enters interactive mode.\n" EMU_REPL_HELP_MESSAGE  \
    "\n"                                                                       \
    "For more information, check out the assignment spec, or ask on Piazza.\n" \
    "    <https://cgi.cse.unsw.edu.au/~cs1521/19T3/assignments/ass1/index.html>\n"

#define EMU_REPL_HELP_MESSAGE                                                  \
    "In interactive mode, available commands are:\n"                           \
    "    s       step (execute one instruction)\n"                             \
    "    r       execute all remaining instructions\n"                         \
    "    q       quit\n"                                                       \
    "    h       this help message\n"                                          \
    "    P       print Program\n"                                              \
    "    R       print Registers\n"                                            \
    "    D       print Data segment\n"                                         \
    "    S       print Stack segment\n"                                        \
    "    T       print Text segment\n"                                         \
    "Entering nothing will re-send the previous command.\n"

static void usage(void) {
    fputs(EMU_USAGE_MESSAGE, stderr);
    exit(1);
}

int main(int argc, char *argv[]) {
    char *temporary_directory;
    char template[] = "/tmp/emu.XXXXXX";
    if ((temporary_directory = mkdtemp(template)) == NULL) {
        fprintf(stderr,
                "%s: can not open create temporary directory: ", argv[0]);
        perror("");
        return 1;
    }

    // atexit could be used here
    char spim_asm_filename[PATH_LENGTH];
    snprintf(spim_asm_filename, sizeof spim_asm_filename, "%s/emu.s",
             temporary_directory);
    char spim_out_filename[PATH_LENGTH];
    snprintf(spim_out_filename, sizeof spim_out_filename, "%s/emu.s.out",
             temporary_directory);

    action_t action =
        process_arguments(argc, argv, spim_asm_filename, spim_out_filename);

    unlink(spim_asm_filename);
    unlink(spim_out_filename);
    rmdir(temporary_directory);

    if (action == a_error) {
        return 1;
    } else {
        return run_or_print_program(action);
    }
}

static action_t process_arguments(int argc, char *argv[],
                                  char *spim_asm_filename,
                                  char *spim_out_filename) {
    action_t action = a_interactive;

    if (argc < 2) {
        usage();
        return a_error;
    }

    int c;
    while ((c = getopt(argc, argv, "pePE")) != -1) {
        switch (c) {
        case 'p':
            action = a_print;
            break;

        case 'e':
            action = a_execute;
            break;

        case 'P':
            action = a_print_file;
            break;

        case 'E':
            action = a_execute_file;
            break;

        default:
            usage();
            return a_error;
        }
    }

    FILE *asm_stream = fopen(spim_asm_filename, "w");
    if (!asm_stream) {
        fprintf(stderr, "%s: can not open '%s': ", argv[0], spim_out_filename);
        perror("");
        return a_error;
    }

    if (action == a_print || action == a_execute) {
        fputs("main:\n", asm_stream);
        for (int arg = optind; arg < argc; arg++) {
            char *endptr;
            strtol(argv[arg], &endptr, 0);
            // if we are given a hex or decomal integer turn into a word directive
            if (argv[arg][0] && !*endptr) {
                fputs(".word ", asm_stream);
            }
            fputs(argv[arg], asm_stream);
            fputc('\n', asm_stream);
        }
    } else {
        if (optind != argc - 1) {
            usage();
            return a_error;
        }

        FILE *in = fopen(argv[optind], "r");
        if (!in) {
            fprintf(stderr, "%s: can not open '%s': ", argv[0], argv[optind]);
            perror("");
            return a_error;
        }

        int byte;
        while ((byte = fgetc(in)) != EOF) {
            fputc(byte, asm_stream);
        }
        fclose(in);
    }
    fclose(asm_stream);

    char assemble_command[256 + PATH_LENGTH];
    snprintf(assemble_command, sizeof assemble_command,
             "PATH=/home/cs1521/bin:$PATH spim -assemble -f %s >/dev/null",
             spim_asm_filename);
    int exit_status = system(assemble_command);

    if (exit_status != 0) {
        fprintf(stderr, "%s: could not assemble program\n", argv[0]);
        return a_error;
    }

    FILE *out_stream = fopen(spim_out_filename, "r");
    if (!out_stream) {
        fprintf(stderr, "%s: can not open '%s': ", argv[0], spim_out_filename);
        perror("");
        return a_error;
    }
    read_program(out_stream);
    fclose(out_stream);

    return action;
}

static int run_or_print_program(action_t action) {
    // set the stack pointer the same as SPIM does for consistency.
    set_register(sp, 0x7FFFF8E4);

    // set the same return address as SPIM does for consistency
    // this is outside out text area so program will terminate on return
    // in SPIM this is the kernel text segment
    set_register(ra, 0x00400018);

    // set the global pointer the same as SPIM does for consistency
    set_register(gp, 0x10008000);

    // set the frame pointer the same as SPIM does for consistency
    // set_register(fp, 0x0);

    // set the PC to the same as SPIM so we can run code
    uint32_t program_counter = 0x400024;

    // set t1..t7 to non-zero values to facilitate testing
    for (int i = 9; i < 16; i++) {
        set_register(i, i - 8);
    }

    int program_terminated = 0;
    if (action == a_print || action == a_print_file) {
        print_program();
    } else if (action == a_execute || action == a_execute_file) {
        run_program(&program_counter, &program_terminated);
        if (action == a_execute) {
            print_registers();
        }
    } else {
        run_interactively(&program_counter);
    }

    return 0;
}

// interactive mode:
static void run_interactively(uint32_t *program_counter) {
    int program_terminated = 0;
    while (true) {
        if (!program_terminated) {
            printf("PC = ");
            print_instruction_at_address(*program_counter);
        }

        if (!run_command(program_counter, &program_terminated)) {
            break;
        }
    }
}

static void step_program(uint32_t *program_counter, int *program_terminated) {
    if (*program_terminated) {
        printf("Can not step - program terminated.\n");
    } else {
        *program_terminated = execute_next_instruction(program_counter);
    }
}

static void run_program(uint32_t *program_counter, int *program_terminated) {
    if (*program_terminated) {
        printf("Can not run - program terminated.\n");
    }
    while (!*program_terminated) {
        step_program(program_counter, program_terminated);
    }
}

static bool run_command(uint32_t *program_counter, int *program_terminated) {
    int command = get_command();

    switch (command) {
    case 's':
        step_program(program_counter, program_terminated);
        break;
    case 'r':
        run_program(program_counter, program_terminated);
        break;
    case 'P':
        print_program();
        break;
    case 'R':
        print_registers();
        break;
    case 'D':
        print_data_segment();
        break;
    case 'S':
        print_stack_segment();
        break;
    case 'T':
        print_text_segment();
        break;
    case 'h':
    case '?':
        puts(EMU_REPL_HELP_MESSAGE);
        break;
    case 'q':
    case -1:
        break;
    default:
        printf("Unknown command '%c'\n", command);
        printf("Type '?' for a list of commands\n");
        break;
    }

    return command != 'q' && command != -1;
}

static int get_command(void) {
    static int last_command = 'h';

    printf("emu > ");

    char input[BUFSIZ];
    if (fgets(input, BUFSIZ, stdin) == NULL) {
        return -1;
    }

    // get first non-white-space character on line
    char c;
    if (sscanf(input, " %c", &c) == 1) {
        last_command = c;
        return c;
    } else {
        return last_command;
    }
}