// cp <file1> <file2> implemented with fgetc 

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    FILE *input_stream = fopen(argv[1], "rb");
    if (input_stream == NULL) {
        perror(argv[1]);  // prints why the open failed
        return 1;
    }

    FILE *output_stream = fopen(argv[2], "wb");
    if (output_stream == NULL) {
        perror(argv[2]);
        return 1;
    }

    int c; // not char!
    while ((c = fgetc(input_stream)) != EOF) {
        fputc(c, output_stream);
    }

    // close occurs automatically on exit
    // so these lines not nee
    fclose(input_stream);
    fclose(output_stream);

    return 0;
}