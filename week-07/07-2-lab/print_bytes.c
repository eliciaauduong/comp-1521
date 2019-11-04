////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  print_bytes.c                                                             //
//  -----                                                                     //
//  Write a C program, print_bytes, which takes one argument, a filename,     //
//  and which should should read the specifed file and print one line for     //
//  each byte of the file. The line should show the byte in decimal and       //
//  hexadecimal. If that byte is a an ASCII printable character, its ASCII    //
//  value should also be printed.                                             //
//                                                                            //
//  Assume ASCII printable characters are those for which the ctype.h         //
//  function isprint(3) returns a non-zero value.                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    char *fname = argv[1]; // get the filename
    FILE *f = fopen(fname, "r"); // open the file to read
    int c = fgetc(f); // get the first character
    long int num = 0; // count the number of bytes
    while (c != EOF) { // read until end of file
        if (isprint(c) != 0) { // if the byte is ASCII printable
            printf("byte %4ld: %3d 0x%02x '%c'\n", num, c, c, c);
        } else { // if the byte is not ASCII printable
            printf("byte %4ld: %3d 0x%02x\n", num, c, c);
        }
        num++; // increase the byte counter
        c = fgetc(f); // get the next character
    }
    fclose(f); // close the file
    return 0;
}