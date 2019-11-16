// simple example of catching a signal don't compile with dcc 

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void ha_ha(int signum) {
    printf("Ha Ha!\n");
}

int main(void) {
    // catch SIGINT which is sent if user types cntrl-d

    struct sigaction action = {.sa_handler = ha_ha};
    sigaction(SIGINT, &action, NULL);

    while (1) {
        printf("Can't interrupt me, I'm ignoring ctrl-C\n");
        sleep(1);
    }
}