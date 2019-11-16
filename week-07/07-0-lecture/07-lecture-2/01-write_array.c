// write bytes of array to file array.save 

/*
$ dcc write_array.c -o write_array
$ dcc read_array.c -o read_array
$ ./write_array
$ ls -l array.save
-rw-r--r-- 1 z5555555 z5555555 40 Oct 30 21:46 array.save
$ ./read_array
10 11 12 13 14 15 16 17 18 19
$
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int array[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int main(int argc, char *argv[]) {

    int fd = open("array.save", O_WRONLY|O_CREAT, 0644);
    if (fd < 0) {
        perror("array.save");
        return 1;
    }

    if (write(fd, array, sizeof array) != sizeof array) {
        perror("array.save");
        return 1;
    }
    close(fd);

    return 0;
}