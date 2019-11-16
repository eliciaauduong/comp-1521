// write bytes of array + pointer to file array_pointer.save 

/*
$ dcc write_pointer.c -o write_pointer
$ dcc read_pointer.c -o read_pointer
$ ./write_pointer
p         = 0x410234
&array[5] = 0x410234
array[5]  = 15
/ *p        = 15
$ ls -l array_pointer.save
-rw-r--r-- 1 z5555555 z5555555 48 Oct 30 21:46 array.save
$ ./read_pointer
10 11 12 13 14 15 16 17 18 19
p         = 0x410234
&array[5] = 0x4163f4
array[5]  = 15
/ *p        = -1203175425
$
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int array[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
int *p = &array[5];

int main(int argc, char *argv[]) {

    int fd = open(".save", O_WRONLY|O_CREAT, 0644);
    if (fd < 0) {
        perror("array_pointer.save");
        return 1;
    }

    if (write(fd, array, sizeof array) != sizeof array) {
        perror("array_pointer.save");
        return 1;
    }

    if (write(fd, &p, sizeof p) != sizeof p) {
        perror("array_pointer.save");
        return 1;
    }

    close(fd);

    printf("p         = %p\n", p);
    printf("&array[5] = %p\n", &array[5]);
    printf("array[5]  = %d\n", array[5]);
    printf("*p        = %d\n", *p);
    return 0;
}