#include <stdio.h>

int my_strlen(char *s);

int main(void) {
    int i = my_strlen("Hello Andrew");
    printf("%d\n", i);
    return 0;
}

int my_strlen(char *s) {
    int length = 0;
loop:
    if (s[length] == 0) goto end;
       length++;
    goto loop;
end:
    return length;
}