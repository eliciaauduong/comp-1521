# Lecture 1 Notes
Wednesday October 2, 2019

## Why Study Assembler?
Useful to know assembly language because...
- Sometimes you are *required* to use it (e.g. device handlers)
- Improves your understanding of how compiled programs execute
    - Very helpful when debugging
    - Understand performance issues better
- Performance tweaking (squeezing out last pico-s)
    - Re-write that performance critical code in assembler

## CPU Architecture
A typical modern CPU has
- A set of data registers
- A set of control registers (incl. PC)
- An arithmetic-logic unit (ALU)
- Access to memory (RAM)
- A set of simple instructions
    - Transfer data between memory and registers
    - Push values through the ALU to compute results
    - Make tests and transfer control of execution
- Different types of processors have different configurations of the above

## MIPS Architecture

MIPS is a well-known and simple architecture
- Historically used everywhere from supercomputers to PlayStations,...
- Still popular in some embedded fields e.g. modems, TVs
- But being out-competed by ARM (in phones,...)

We consider the MIPS32 version fo the MIPS family
- `qtspim` ... provides a GUI front-end, useful for debugging
- `spim` ... command-line based version, useful for testing
- `xspim` ... GUI front-end, useful for debugging, only in CSE labs

Executables and source: http://spimsimulator.sourceforge.net/

Source code for browsing under /home/cs1521/spim

## Fetch-Execute Cycle
All CPUs have program execution logic like:
``` c
uint32_t pc = STARTING_ADDRESS;
while (1) {
    uint32_t instruction - memory[pc];
    pc++;
    if (instruction == HALT) {
        break;
    } else {
        execute (instruction);
    }
}
```

pc = Program Counter, a CPU register which tracks execution

Note that some instructions may modify pc (e.g. JUMP)

Executing an `instruction` involves
- Determine what the *operator* is
- Determine which *registers*, if any, are involved
- Determine which *memory location*, if any, is involved
- Carry out the operation with the relevant operands
- Store result, if any, in appropriate register

Example instruction encodings (not from a real machine):
| ADD | R1 | R2 | R3 |
| :-: | :-: | :-: | :-: |
| 8 bits | 8 bits | 8 bits | 8 bits |

| LOAD | R4 | 0x10004 |
| :-: | :-: | :-: |
| 8 bits | 8 bits | 16 bits |

## Assembly Language
Instructions are simple bit patterns within a 32-bit bit-string

Could specify machine code as a sequence of hex digits, e.g.

```
Address     Content
0x100000    0x3c041001
0x100004    0x34020004
0x100008    0x0000000c
0x10000C    0x03e00008
```

Assembly language is a symbolic way of specifying machine code
- Write instructions using mnemonics rather than hex codes
- Refer to registers using either numbers or names
- Can associate names to memory addresses

## MIPS Instructions
MIPS have several classes of instructions:
- *load and store* ... transfer data between registers and memory
- *computational* ... perform arithmetic / logical operations
- *jump and branch* ... transfer control of program execution
- *coprocessor* ... standard interface to various co-processors
- *special* ... miscellaneous tasks (e.g. syscall)

And several *addressing modes* for each instruction
- Between memory and register (direct, indirect)
- Constant to register (immediate)
- Register + register + destination register

## MIPS Architecture
MIPS CPU has
- 32 general purpose registers (32-bit)
- 16/32 floating-point registers (for float/ double)
- PC ... 32-bit register (always aligned on 4-byte boundary)
- HI, LO ... for storing results of multiplication and division

Registers can be referred to as $0..$31 or by symbolic names

Some registers have special uses e.g.
- Register $0 always has value 0, cannot be written
- Registers $1, $26, $27 reserved for use by system

### Integer Registers

|Number|Names|Usage|
|:--|:--|:--|
|0|`$zero`|Constant 0|
|1|`$at`|Reserved for assembler|
|2,3|`$v0` , `$v1`|Expression evaluation and results of a function|
|4..7|`$a0` .. `$a3`|Arguments 1-4|
|8..16|`$t0` .. `$t7`|Temporary (not preserved across function calls)|
|16..23|`$s0` .. `$s7`|Saved temporary (preserved across function calls)|
|24, 25|`$t8` , `$t9`|Temporary (preserved across function calls)|
|26, 27|`$k0` , `$k1`|Reserved for OS kernel|
|28|`$gp`|Pointer to global area|
|29|`$sp`|Stack pointer|
|30|`$fp`|Frame pointer|
|31|`$ra`|Return address (used by function call instruction)|


- Except for registers 0 and 31, these uses are only conventions
- Conventions allow compiled code from different sources to be combined (linked)
- Most of these conventions are irrelevant when you are writing small MIPS assembly code programs
- But use registers 8..23 for holding values
- Definitely do not use 0,1, and 31


## Describing MIPS Assembler Operations
- An address refers to a memory cell
- `Mem[addr]` = contents of cell at address *addr*
- `&name` = location of memory cell for *name*
- Registers are denoted: 
    - R<sub>d</sub> destination register (where result goes) 
    - R<sub>s</sub> source register #1 (where data comes from) 
    - R<sub>t</sub> source register #2 (where data comes from) 
- Reg[R] = contents of register R
- Data transfer is denoted by <-

``` MIPS
add $6, $7, $8 # Reg[6] <- Reg[7] + Reg[8]
lw $7, buffer # Reg[7] <- Mem[buffer]
```

## Setting Register

`li` R<sub>d</sub>imm load immediate Reg[R<sub>d</sub>] <- imm 

`la` R<sub>d</sub>addr load address Reg[R<sub>d</sub>] <- addr 

`move` R<sub>d</sub>R<sub>s</sub> move data reg-to-reg Reg[R<sub>d</sub>] <- Reg[R<sub>s</sub>]


## MIPS vs SPIM
MIPS is a machine architecture, including instruction set 

SPIM is an emulator for the MIPS instruction set 

- Reads text ﬁles containing instruction + directives 
- Converts to machine code and loads into "memory"
- Provides debugging capabilities 
    - Single-step, breakpoints, view registers/memory, ... 
- Provides mechanism to interact with operating system (syscall) 

Also provides extra instructions, mapped to MIPS core set 
- Provide convenient/mnemonic ways to do common operations 
- e.g. move $s0,$v0 rather than addu $s0,$0,$v0

## Using SPIM
Three ways to execute MIPS code with SPIM 
- `spim` ... command line tool
    - Load programs using -file option
    - Interact using stdin/stdout via login terminal 
- `qtspim` ... GUI environment 
    - Load programs via a load button 
    - Interact via a pop-up stdin/stdout terminal
- `xspim` ... GUI environment
    - Similar to qtspim, but not as pretty 
    - Requires X-windows server
