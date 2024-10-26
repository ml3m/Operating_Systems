/* the program copies a whole tree from a given path in argv[1] into argv[2]
 *
 * made it work for:
 * dirs
 * files
 * symlinks
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#ifndef PATH_MAX
#define PATH_MAX 4096  
// some <limits.h> have the PATH_MAX already defined in there.
// mine didn't 
#endif

void copy_file(const char *src_file, const char *dest_file) {
    int src_fd = open(src_file, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (dest_fd < 0) {
        perror("Error creating destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    ssize_t bytes;
    while ((bytes = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes) != bytes) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }
    if (bytes < 0) {
        perror("Error reading from source file");
    }

    close(src_fd);
    close(dest_fd);
}

void copy_symlink(const char *src_link, const char *dest_link) {
    char link_target[PATH_MAX];
    ssize_t len = readlink(src_link, link_target, sizeof(link_target) - 1);
    if (len < 0) {
        perror("Error reading symbolic link");
        exit(EXIT_FAILURE);
    }
    link_target[len] = '\0';

    if (symlink(link_target, dest_link) < 0) {
        perror("Error creating symbolic link");
        exit(EXIT_FAILURE);
    }
}

void copy_entity(const char *src, const char *dest) {
    struct stat st;
    if (stat(src, &st) < 0) {
        perror("Error reading source path");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(st.st_mode)) {
        if (mkdir(dest, st.st_mode) < 0) {
            perror("Error creating destination directory");
            exit(EXIT_FAILURE);
        }

        DIR *dir = opendir(src);
        if (!dir) {
            perror("Error opening source directory");
            exit(EXIT_FAILURE);
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // make it work for . and ..
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char src_path[PATH_MAX];
            char dest_path[PATH_MAX];
            snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
            snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

            if (stat(src_path, &st) < 0) {
                perror("Error reading file");
                closedir(dir);
                exit(EXIT_FAILURE);
            }

            if (S_ISDIR(st.st_mode)) {
                copy_entity(src_path, dest_path);
            } else if (S_ISREG(st.st_mode)) {
                copy_file(src_path, dest_path);
            } else if (S_ISLNK(st.st_mode)) {
                copy_symlink(src_path, dest_path);
            } else {
                fprintf(stderr, "Unsupported file type: %s\n", src_path);
            }
        }

        closedir(dir);
    } else {
        fprintf(stderr, "Source path is not a directory: %s\n", src);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s path/to/copy path/to/create\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat(argv[1], &st) < 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Source path is not a directory or cannot be accessed.\n");
        exit(EXIT_FAILURE);
    }

    if (stat(argv[2], &st) == 0) {
        fprintf(stderr, "Destination path already exists.\n");
        exit(EXIT_FAILURE);
    }

    copy_entity(argv[1], argv[2]);
    return 0;
}
