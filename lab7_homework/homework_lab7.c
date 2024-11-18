#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

void reverse_string(char *str) {
  int len = strlen(str);
  int i, j;
  for (i = 0, j = len - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

void process_content(const char *buffer, char *result) {
  int digits_count = 0, uppercase_count = 0, lowercase_count = 0;
  char digits[MAX_BUFFER_SIZE] = {0};
  char uppercase[MAX_BUFFER_SIZE] = {0};
  char lowercase[MAX_BUFFER_SIZE] = {0};
  char others[MAX_BUFFER_SIZE] = {0};

  for (int i = 0; buffer[i] != '\0'; i++) {
    if (isdigit(buffer[i])) {
      digits[digits_count++] = buffer[i];
    } else if (isupper(buffer[i])) {
      uppercase[uppercase_count++] = buffer[i];
    } else if (islower(buffer[i])) {
      lowercase[lowercase_count++] = buffer[i];
    } else {
      others[strlen(others)] = buffer[i];
    }
  }

  sprintf(result, "%d%s%d%s%d%s%s", digits_count, digits, uppercase_count,
          uppercase, lowercase_count, lowercase, others);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
    return 1;
  }

  // open input
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char buffer[MAX_BUFFER_SIZE];
  if (fgets(buffer, sizeof(buffer), file) == NULL) {
    perror("Error reading file");
    fclose(file);
    return 1;
  }
  fclose(file);

  buffer[strcspn(buffer, "\n")] = 0;

  printf("Initial File Content: %s\n", buffer);

  // pipes
  int pipe_parent_to_child[2], pipe_child_to_parent[2];
  if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
    perror("Pipe creation failed");
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("Fork failed");
    return 1;
  }

  // Child process
  if (pid == 0) {
    close(pipe_parent_to_child[1]);
    close(pipe_child_to_parent[0]);

    char received_buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read =
        read(pipe_parent_to_child[0], received_buffer, sizeof(received_buffer));
    if (bytes_read > 0) {
      received_buffer[bytes_read] = '\0';
      printf("Child Received (Reversed): %s\n", received_buffer);

      char result_buffer[MAX_BUFFER_SIZE];
      process_content(received_buffer, result_buffer);

      write(pipe_child_to_parent[1], result_buffer, strlen(result_buffer));
    }

    close(pipe_parent_to_child[0]);
    close(pipe_child_to_parent[1]);
    exit(0);
  } else {
    // Parent process
    close(pipe_parent_to_child[0]);
    close(pipe_child_to_parent[1]);

    char processed_buffer[MAX_BUFFER_SIZE];
    strcpy(processed_buffer, buffer);

    reverse_string(processed_buffer);
    printf("Parent Sending (Reversed): %s\n\n", processed_buffer);

    write(pipe_parent_to_child[1], processed_buffer, strlen(processed_buffer));
    close(pipe_parent_to_child[1]);

    char child_response[MAX_BUFFER_SIZE];
    ssize_t bytes_read =
        read(pipe_child_to_parent[0], child_response, sizeof(child_response));
    if (bytes_read > 0) {
      child_response[bytes_read] = '\0';
      printf("Parent Received from Child(processed): %s\n", child_response);
    }
    close(pipe_child_to_parent[0]);

    wait(NULL);
  }

  return 0;
}
