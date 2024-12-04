# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Output executable
TARGET = parent_child_signal

# Source file
SRC = problem_one.c

# Object file
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Rule to link object file to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Rule to compile the source file into an object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
