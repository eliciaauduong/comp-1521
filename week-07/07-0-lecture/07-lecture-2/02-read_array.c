// read bytes of array + pointer to file array_pointer.save non-portable between platforms breaks if sizeof int changes or endian-ness changes 

// Handling this safely is called serialization: https://en.wikipedia.org/wiki/Serialization 

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int array[10];

int main(int argc, char *argv[]) {

    int fd = open("array.save", O_RDONLY, 0644);
    if (fd < 0) {
        perror("array.save");
        return 1;
    }

    if (read(fd, array, sizeof array) != sizeof array) {
        perror("array.save");
        return 1;
    }
    close(fd);

    // print array
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}