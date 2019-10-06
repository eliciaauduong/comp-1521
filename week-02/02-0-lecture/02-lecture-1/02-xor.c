#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

//
// copy stdin to stdout xor each byte with value supplied on STDIN
//
//
// Try
// $ dcc xor.c -o xor
// $ <xor.c xor 42
// $ <xor.c xor 42|xor 42
//

// xor twice to get the original value

int main(int argc, char *argv[]) {
    assert(argc == 2);
    uint8_t key = strtol(argv[1], NULL, 0);
    int c;
    while ((c = getchar()) != EOF) {
        uint8_t encrypted_c = c ^ key;
        putchar(encrypted_c);
    }
    return 0;
}