# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Target Executable
TARGET = lab7

# Source Files
SRC = homework_lab7.c

# Object Files
OBJ = $(SRC:.c=.o)

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET) input_file

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all run clean
