// use fseek to change arandom bit in a file 
// the return value of the calls to fopen, fseek and fgetc should be checked to see if they worked! 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    // open file for reading and writing
    FILE *f = fopen(argv[1], "r+");

    // move to end of file
    fseek(f, 0, SEEK_END);

    long n_bytes_in_file = ftell(f);

    // seed random number generator with current time
    srandom(time(NULL));

    // pick a random byte
    long target_byte = random() % n_bytes_in_file;

    // move to byte
    fseek(f, target_byte, SEEK_SET);

    // read byte
    int byte = fgetc(f);

    // pick a random bit
    int bit = random() % 7;

    // flip the bit
    int new_byte = byte ^ (1 << bit);

    // move back to write byte to same position
    fseek(f, -1, SEEK_CUR);

    // write the byte
    fputc(new_byte, f);

    fclose(f);

    printf("Changed byte %ld of %s from %02x to %02x\n",target_byte, argv[1], byte, new_byte);
    return 0;
}