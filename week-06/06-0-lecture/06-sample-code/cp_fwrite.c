// cp <file1> <file2> implemented with libc and *zero* error handling 

#include <stdio.h>

int main(int argc, char *argv[]) {
    // open takes 3 arguments:
    //   1) address of zero-terminated string containing pathname of file to open
    //   2) bitmap indicating whether to write, read, ... file
    //   3) permissions if file will be newly created
    //      0644 == readable to everyone, writeable by owner

    // b = binary mode - not needed on Linux, OSX (POSIX) systems
    //                 - needed on Windows

    FILE *read_stream = fopen(argv[1], "rb");
    FILE *write_stream = fopen(argv[2], "wb");

    // this will be slightly faster than an a fgetc/fputc loop
    while (1) {
        char bytes[BUFSIZ];
        size_t bytes_read = fread(bytes, 1, 4096, read_stream);
        if (bytes_read <= 0) {
            break;
        }
        fwrite(bytes, 1, bytes_read, write_stream);
    }

    return 0;
}