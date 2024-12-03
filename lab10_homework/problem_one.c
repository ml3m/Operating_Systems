/*
 * C Program 1: Parent-Child Process with SIGUSR1 Signal
 *
 * The parent process forks a child and sends the SIGUSR1 signal to it every
 * second. The child computes a[n+1] = a[n] + 1/r, starting with a[0] = a0, and
 * prints the current value of a[n] each time it receives SIGUSR1. The child
 * exits after printing twice. The parent starts by printing "*****" and
 * alternates between "+++++" and "-----" every second, sending SIGUSR1 to the
 * child. After the child exits, the parent prints the exit status. a0 and r are
 * provided as command-line arguments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

double current_value;
int print_count = 0;
double r;

// Signal handler for SIGUSR1
void handle_SIGUSR1(int signal) {
    //printf("Signal SIGUSR1 received by child.\n");
    current_value += 1 / r; // Update the sequence
    printf("Current value: %.6f\n", current_value);
    print_count++;

    // 2 prints we end exe
    if (print_count == 2) {
        printf("Child exiting after 2 prints.\n");
        exit(0); // Exit after 2 prints
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a0> <r>\n", argv[0]);
        exit(1);
    }

    double a0 = atof(argv[1]);
    r = atof(argv[2]);

    if (r == 0) {
        fprintf(stderr, "Error: r cannot be zero\n");
        exit(1);
    }
    printf("*****\n");

    /******* Child Process *********/
    signal(SIGUSR1, SIG_IGN);
    int id = fork();

    if (id < 0) {
        perror("Error creating process");
        exit(1);
    }

    if (id == 0) { // Child process
        current_value = a0;
        printf("Child process started. Initial value: %.6f\n", current_value);

        if (signal(SIGUSR1, handle_SIGUSR1) == SIG_ERR) {
            fprintf(stderr, "Error setting up SIGUSR1 handler\n");
            exit(2);
        }

        while (1) {
            //printf("Child waiting for signals...\n"); // Debugging message
            pause(); // Wait for signals
        }
    }
    for (int i = 0;;i++) {
        if (i % 2 == 0) {
            printf("+++++\n");
        } else {
            printf("-----\n");
        }

        //printf("Parent sending SIGUSR1 to child.\n");
        kill(id, SIGUSR1); // Send signal to child
        sleep(1);


        // Check if the child process has exited
        int status;
        if (waitpid(id, &status, WNOHANG) > 0) {
            printf("Child exited with code: %d\n", WEXITSTATUS(status));
            break;
        }
    }
    return 0;
}
