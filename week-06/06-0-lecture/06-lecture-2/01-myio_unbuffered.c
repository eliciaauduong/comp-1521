// simple re-implementation of stdio functions fopen, fgetc, fputc, fclose no buffering *zero* error handling for clarity 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MY_EOF -1

// struct to hold data for a stream
typedef struct my_file {
    int fd;
} my_file_t;

my_file_t *my_fopen(char *file, char *mode) {
    int fd = -1;
    if (mode[0] == 'r') {
        fd = open(file, O_RDONLY);
    } else if (mode[0] == 'w') {
        fd = open(file, O_WRONLY | O_CREAT, 0666);
    } else if (mode[0] == 'a') {
        fd = open(file, O_WRONLY | O_APPEND);
    }

    if (fd == -1) {
        return NULL;
    }

    my_file_t *f = malloc(sizeof *f);
    f->fd = fd;
    return f;
}

int my_fgetc(my_file_t *f) {
    uint8_t byte;
    int bytes_read = read(f->fd, &byte, 1);
    if (bytes_read == 1) {
        return byte;
    } else {
        return MY_EOF;
    }
}

int my_fputc(int c, my_file_t *f) {
    uint8_t byte = c;
    if (write(f->fd, &byte, 1) == 1) {
        return byte;
    } else {
        return MY_EOF;
    }
}

int my_fclose(my_file_t *f) {
    int result = close(f->fd);
    free(f);
    return result;
}

int main(int argc, char *argv[]) {
    my_file_t *input_stream = my_fopen(argv[1], "r");
    if (input_stream == NULL) {
        perror(argv[1]);
        return 1;
    }

    my_file_t *output_stream = my_fopen(argv[2], "w");
    if (output_stream == NULL) {
        perror(argv[2]);
        return 1;
    }

    int c;
    while ((c = my_fgetc(input_stream)) != MY_EOF) {
        my_fputc(c, output_stream);
    }

    return 0;
}