// read bytes of array + pointer to file array_pointer.save breaks even on same machine because address of array different for every execution see https://en.wikipedia.org/wiki/Address_space_layout_randomization 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int array[10];
int *p;

int main(int argc, char *argv[]) {

    int fd = open("array_pointer.save", O_RDONLY, 0644);
    if (fd < 0) {
        perror("array_pointer.save");
        return 1;
    }

    if (read(fd, array, sizeof array) != sizeof array) {
        perror("array_pointer.save");
        return 1;
    }

    if (read(fd, &p, sizeof p) != sizeof p) {
        perror("array_pointer.save");
        return 1;
    }

    close(fd);

    // print array
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("p         = %p\n", p);
    printf("&array[5] = %p\n", &array[5]);
    printf("array[5]  = %d\n", array[5]);
    printf("*p        = %d\n", *p);

    return 0;
}