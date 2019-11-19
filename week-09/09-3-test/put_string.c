// print s to stdout with a new line appended using fputc (only)
// Test 09 - Tuesday 19 November
// Elicia AU DUONG - z5260173

#include <stdio.h>

void put_string(char *str);

void put_string(char *s) {

    int i = 0;
    while (s[i] != '\0') { // until end of string
        fputc(s[i], stdout); // print to stdout
        ++i;
    }
    fputc('\n', stdout);
}
