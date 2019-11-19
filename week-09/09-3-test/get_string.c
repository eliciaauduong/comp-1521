// print a line from stream using fgetc (only)
// reads in at most one less than size characters from stream and stores them
// into the buffer pointed to by s. 
// Reading stops after an EOF or a newline.  
// If a newline is read, it  is stored  into  the buffer. 
// A terminating null byte ('\0') is stored after last character in the buffer.
// Test 09 - Tuesday 19 November
// Elicia AU DUONG - z5260173

#include <stdio.h>

#include "get_string.h"

void get_string(char *s, int size, FILE *stream) {

    int ch = fgetc(stream); // get first character
    int i = 0; // track size of buffer
    while (i < size) { // read until one less than size
        if (ch == EOF) { // if character is EOF stop reading
            break;
        } else if (ch == '\n') { // if character is \n store and stop reading
            s[i] = ch;
            i++;
            break;
        } else { // else store character
            s[i] = ch;
        }
        ch = fgetc(stream); // get new character
        i++;
    }
    
    // terminating null byte is stored after last character
    if (i < size) {
        s[i] = '\0';
    } else {
        s[i-1] = '\0';
    }
}