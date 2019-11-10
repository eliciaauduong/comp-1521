#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main(void) {
    int fd = open("sparse_file.txt", O_WRONLY | O_CREAT, 0644);
    write(fd, "Hello, Andrew!\n", 15);
    lseek(fd, 16L * 1000 * 1000 * 1000 * 1000, SEEK_CUR);
    write(fd, "Good Bye Andrew!\n", 17);
    close(fd);
    return 0;
}