/*
 *
2. Create a C application that switches between executing two processes.

The parent will start both processes at once but will allow only the first subprocess 
to run for a number of N seconds. 

After that, the process will be put
on hold (wait), and the second subprocess run for a number of N seconds. 

Then the parent process will stop the second process and resume the first one. 

Each process switch will be accompanied by a message 
(e.g.: "Process x was put on hold, Process y started"). 
This cycle will be done until the parent receives the SIGUSR1 signal.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t stop_switching = 0;

void sigusr1_handler() {
    stop_switching = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N_seconds> <num_cycles>\n", argv[0]);
        exit(1);
    }
    int N = atoi(argv[1]);
    int num_cycles = atoi(argv[2]);


    // ignore SIGUSR1
    signal(SIGUSR1, SIG_IGN);

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("First fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        signal(SIGUSR1, sigusr1_handler);

        while (!stop_switching) {
            printf("First process running\n");
            sleep(1);
        }
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Second fork failed");
        kill(pid1, SIGKILL);
        exit(1);
    }

    if (pid2 == 0) {
        // 2
        while (!stop_switching) {
            printf("Second process running\n");
            sleep(1);
        }
        exit(0);
    }

    int cycle_count = 0;
    while (cycle_count < num_cycles && !stop_switching) {
        // 1
        printf("Process 1 started, Process 2 on hold\n");
        kill(pid2, SIGSTOP);
        kill(pid1, SIGCONT);
        sleep(N);

        // 2
        printf("Process 2 started, Process 1 on hold\n");
        kill(pid1, SIGSTOP);
        kill(pid2, SIGCONT);
        sleep(N);

        cycle_count++;
    }

    kill(pid1, SIGKILL);
    kill(pid2, SIGKILL);


    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
