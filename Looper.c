#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handler(int sig) {
    printf("\nReceived Signal: %s\n", strsignal(sig));
    
    if (sig == SIGTSTP) {
        signal(SIGTSTP, SIG_DFL);
        signal(SIGCONT, handler);
    } else if (sig == SIGCONT) {
        signal(SIGCONT, SIG_DFL);
        signal(SIGTSTP, handler);
    }
    
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(int argc, char **argv) {
    printf("Starting the program\n");
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGCONT, handler);

    while (1) {
        sleep(1);
    }

    return 0;
}
