CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = process_switcher
SOURCES = problem_two.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g
debug: $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all debug clean
