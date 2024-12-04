# OS Lab 10 - Homework

- [Exercise 1](exercise_one)
- [Exercise 2](exercise_two)

## Exercise 1: Subprocess Signal Handling

In this exercise, a parent process creates a child process. The parent sends a
`SIGUSR1` signal to the child every second. The child computes and prints a
sequence based on the formula `a[n+1] = a[n] + 1/r`, where `a[0] = a0`, and
stops after two prints. The parent alternates between printing `+++++` and
`-----` every second, and finally, it waits for the child to exit and prints
its exit code.

### Instructions

1. The program takes two command-line arguments: `a0` and `r`.
2. The parent sends a signal to the child every second.
3. The child prints the current value of the sequence upon receiving the signal
   and exits after two prints.
4. The parent alternates its output between `+++++` and `-----` every second
   until the child exits.

## Exercise 2: Process Switching

In this exercise, the parent process creates two subprocesses and alternates
between executing them. Each process runs for `N` seconds, and after that, it
is paused, and the other process starts. The switching continues until the
parent receives a `SIGUSR1` signal, at which point it stops the cycle.

### Instructions

1. The program takes two command-line arguments: `N_seconds` and `num_cycles`.
2. The parent alternates between two subprocesses, allowing each to run for `N`
   seconds.
3. The switching process is accompanied by messages such as "Process x was put
   on hold, Process y started".
4. The process switch cycle continues for the specified number of cycles or
   until the parent receives the `SIGUSR1` signal.
