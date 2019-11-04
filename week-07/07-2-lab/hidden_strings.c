////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  hidden_strings.c                                                          //
//  -----                                                                     //
//  Write a C program, hidden_strings, which takes one argument, a filename;  //
//  it should read that file, and print all sequences of length 4 or longer   //
//  of consecutive byte values corresponding to printable ASCII characters.   //
//                                                                            //
//  In other words, your program should read through the bytes of the file,   //
//  and if it finds 4 bytes in a row containing printable characters, it      //
//  it should print those bytes, and any following bytes containing ASCII     //
//  printable characters.                                                     //
//                                                                            //
//  Print each sequence on a separate line.                                   //
//                                                                            //
//  Assume ASCII printable characters are those for which the ctype.h         //
//  function isprint(3) returns a non-zero value.                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    
    char *fname = argv[1];
    FILE *f = fopen(fname, "r"); // open a file to read
    
    int buffer[3] = {0}; // create a buffer to store ASCII printable characters
    int c = fgetc(f); // get the first character of the file
    
    int count = 0; // set count of consecutive ASCII printable characters to 1
    
    int three = 0; // check to see if the first three characters in a 4 or more 
                   // bytes word have been printed
    int newEnd = 0; // check to see if a newline needs to be printed at the end
    
    while (c != EOF) { // read characters until end of file
        if (isprint(c) != 0) { // if the character is ASCII printable
            if (count < 3) { // if less than 3 characters, add to buffer
                buffer[count] = c;
            } else { // if 3 or more consecutive characters 
                if (three == 0) { // if the first three characters not printed
                    for (int i = 0; i < 3; i++) { // print buffer characters
                        printf("%c", buffer[i]);
                    }
                    three = 1; // three characters have been printed
                }
                printf("%c", c); // print each letter after
            }
            count++; // add count for every consecutive letter
        } else { // if not ASCII printable character
            if (count > 3) { // if end of ASCII word
                printf("\n"); // print a newline
                newEnd++; // newline printed
            }
            count = 0; // reset consecutive count for words
            three = 0; // three characters haven't been printed
        }
        c = fgetc(f); // get the next character
    }
    
    if (count > 3 && newEnd == 0) { // if end of word and newline not printed
        printf("\n");
    }
    
    return 0;
}