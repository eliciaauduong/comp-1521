// copy stdin to stdout implemented with fgets 

#include <stdio.h>

int main(void) {
    // return  bytes from the stream (stdin) line at a time
    // BUFSIZ is defined in stdio.h - its an efficient value to use
    // but any value would work

    // NOTE: fgets returns a null-terminated string
    //       in other words a 0 byte marks the end of the bytes read

    // so fgets can not be used to read data containing bytes which are 0
    // also fputs takes a null-terminated string so it can not be used to write bytes which are 0
    // in other word you can't use fget/fputs for binary data e.g. jpgs

    char line[BUFSIZ];
    while (fgets(line, BUFSIZ, stdin) != NULL) {
        fputs(line, stdout);
    }

    return 0;
}