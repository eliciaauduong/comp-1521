# Lecture 1 Notes
Wednesday September 18, 2019

## Course introduction
**ASSUMED KNOWLEDGE**
- Design an algorithmic solution
- Describe your solution in C code, using ...
    - Variables, assignment, tests (==, !, <=, &&, etc)
    - if, while, for, break, scanf(), printf()
    - Functions, return, prototypes, *.h, *.c
    - Arrays, structs, pointers, malloc(), free()

**NOT ASSUMED**
- Linked structures, file operations, ADTs, sorting, recursion, bit operations

---

## Integers

- Decimal representation: digits 0 to 9 (base 10)
- Binary representation: digits 0 and 1 (base 2)
- Hexadecimal representation digits 0 - 9 and A - F (base 16)
- Binary to hexadecimal: collect bits into groups of four starting from right to left
    - 'Pad out' left-hand side with 0's if necessary

*Examples*

1011111000101001<sub>2</sub> to Hex:

| 1011 | 1110 | 0010 | 1001 |
| :----: | :----: | :----: | :----: |
| B | E | 2 | 9 |

10111101011100<sub>2</sub> to Hex:

| *00*10 | 1111 | 0101 | 1100 |
| :----: | :----: | :----: | :----: |
| 2 | F | 5 | C |

- Hexadecimal to binary: convert each hex digit into equivalent 4-bit binary representation

*Example*

Convert AD5<sub>16</sub> to Binary:

| A | D | 5 |
| :---: | :---: | :---: |
| 1010 | 1101 | 0101 |

---

### Memory Organisation
- Memory is effectively a gigantic array of bytes
- Memory addresses are effectively an index to this array of bytes, usually printed in hexadecimal

### Variables in Memory
``` C
int k;
int m;

// prints address of k is 0xbffffb80
printf("address of k is %p\n", &k);

// prints address of m is 0xbffffb84
printf("address of m is %p\n", &m);