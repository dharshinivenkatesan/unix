#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void print_file_permissions(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File permissions of %s: ", filename);
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main() {
    const char *filename = "example.txt";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // rw-r--r--

    // Create a file (if it doesn't exist)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Print original file permissions
    print_file_permissions(filename);

    // Demonstrate umask
    mode_t old_umask = umask(0); // Set umask to 0 to get the current umask value
    printf("Current umask value: %o\n", old_umask);

    // Set a new umask value (e.g., 022)
    mode_t new_umask = 022;
    umask(new_umask);
    printf("New umask value set: %o\n", new_umask);

    // Change file permissions using chmod
    if (chmod(filename, mode) == -1) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }

    printf("Changed permissions of %s to rw-r--r--\n", filename);

    // Print modified file permissions
    print_file_permissions(filename);

    return 0;
}
