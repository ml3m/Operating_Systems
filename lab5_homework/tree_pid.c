
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 *
 *
 *
Parent PID: 17290
P1 (PID: 17291, PPID: 17290)
C1 (PID: 17292, PPID: 17291)
C2 (PID: 17293, PPID: 17292)
C3 (PID: 17294, PPID: 17293)
parent process closed with pid 17290%                           

17290 (P)
  | 
17291 (Cp1) not good. (it must be C1)

 
 *
 */

void create_process_tree() {
    pid_t cp1, c1, c2, c3;

    printf("Parent(Root) PID: %d\n", getpid());


    /*
    Cp1 = fork();
    if (Cp1 == 0) {
        printf("Process: Cp1 (PID: %d, PPID: %d)\n", getpid(), getppid());
    }
    */

    // init forc p and Cp1
    cp1 = fork();
    if (cp1 == 0) {
        printf("Process: CP1 (PID: %d, PPID: %d)\n", getpid(), getppid());

        c1 = fork();
        if (c1 == 0) {
            printf("Process: C1 (PID: %d, PPID: %d)\n", getpid(), getppid());

            c2 = fork();
            if (c2 == 0) {
                printf("Process: C2 (PID: %d, PPID: %d)\n", getpid(), getppid());

                c3 = fork();
                if (c3 == 0) {
                    printf("Process: C3 (PID: %d, PPID: %d)\n", getpid(), getppid());
                    exit(0);
                }
                waitpid(c3, NULL, 0);
                exit(0);
            }
            waitpid(c2, NULL, 0);
            exit(0);
        }
        waitpid(c1, NULL, 0);
        exit(0);
    }
    waitpid(cp1, NULL, 0);
    //printf("parent process closed with pid %d", getpid());
}

int main() {
    create_process_tree();
    return 0;
}
