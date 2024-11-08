# Process Tree Program

## Description

This C program demonstrates the creation of a process tree using `fork()`
system calls. The process tree consists of a parent process (Root) and child
processes, creating a hierarchy as follows:

Parent (Root) | CP1 | C1 | C2 | C3

The parent process creates a child process `CP1`, which then creates another
child `C1`, and so forth until `C3` is created. Each process prints its PID
(Process ID) and PPID (Parent Process ID) to the console.

## Files

- **`tree_pid.c`**: The main C program that creates the process tree.
- **`Makefile`**: A makefile to build, clean, and run the program.

## Build Instructions

To build the program, use the provided `Makefile`:

```bash 
make 
```
- This will generate an executable named process_tree.

Running the Program After building the program, you can run it using:

```bash 
./process_tree
```
- The program will print the PID and PPID of each
process in the hierarchy.

## Cleaning Up To remove the generated files (object files and the executable),
run:


```bash 
make clean
make all
make run
```
### Example Output 
```bash
Parent(Root) PID: 17290 
Process: CP1 (PID: 17291, PPID: 17290) 
Process: C1 (PID: 17292, PPID: 17291) 
Process: C2 (PID: 17293, PPID: 17292) 
Process: C3 (PID: 17294, PPID: 17293) 
```
