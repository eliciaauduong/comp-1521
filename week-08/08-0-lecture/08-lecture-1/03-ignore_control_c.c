// simple example of catching a signal don't compile with dcc 

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(void) {
    // catch SIGINT which is sent if user types cntrl-d

    struct sigaction action = {.sa_handler = SIG_IGN};
    sigaction(SIGINT, &action, NULL);

    while (1) {
        printf("Can't interrupt me, I'm ignoring ctrl-C\n");
        sleep(1);
    }
}