// useles suse of chdir() because it only affects this process and any it runs 
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && chdir(argv[1]) != 0) {
        perror("chdir");
        return 1;
    }
    return 0;
}