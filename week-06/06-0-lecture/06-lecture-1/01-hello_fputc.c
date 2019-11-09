// hello world implemented with fputc 

#include <stdio.h>

int main(void) {
    char bytes[16] = "Hello, Andrew!\n";

    for (int i = 0; i < 15; i++) {
        fputc(bytes[i], stdout);
    }

    // or as we know bytes is null-terminated: bytes[15] == '\0'

    for (int i = 0; bytes[i] != '\0'; i++) {
        fputc(bytes[i], stdout);
    }

    // or if you prefer pointers

    for (char *p = &bytes[0]; *p != '\0'; p++) {
        fputc(*p, stdout);
    }

    return 0;
}