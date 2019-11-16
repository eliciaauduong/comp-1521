// simple example of use to popen to capture output don't compile with dcc 
// - it currently has a bug with popen 

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // popen passes string to a shell for evaluation
    // brittle and highly-vulnerable to security exploits
    // popen is suitable for quick debugging and throw-away programs only

    FILE *p = popen("/bin/date --utc", "r");
    if (p == NULL) {
        perror("");
        return 1;
    }

    char line[256];
    if (fgets(line, sizeof line, p) == NULL) {
        fprintf(stderr, "no output from date\n");
        return 1;
    }

    printf("output captured from /bin/date was: '%s'\n", line);

    pclose(p);
    return 0;
}