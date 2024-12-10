#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void close_fd(int fd) {
    if (fd != -1) {
        close(fd);
    }
}

void clear(int input, int digits, int other, char* buffer) {
    if (buffer != NULL) {
        free(buffer);
    }
    close_fd(input);
    close_fd(digits);
    close_fd(other);
}

int main(int argc, char const* argv[]) {
    int input = open(argv[1], O_RDONLY);
    if (input == -1) {
        clear(input, -1, -1, NULL);
        return 1;
    }
    int digits = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int other = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (digits == -1 || other == -1) {
        clear(input, digits, other, NULL);
        return 2;
    }
    const size_t buffer_size = 8;
    char* buffer = (char*)calloc(buffer_size * 3, sizeof(char));
    if (buffer == NULL) {
        clear(input, -1, -1, buffer);
        return 3;
    }
    while (1) {
        ssize_t real_read_size = read(input, buffer, buffer_size);
        if (real_read_size == -1) {
            clear(input, digits, other, buffer);
            return 3;
        }
        if (real_read_size == 0) {
            break;
        }
        for (ssize_t i = 0; i < real_read_size; ++i) {
            size_t to_write = 0;
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                to_write = write(digits, buffer + i, sizeof(char));
            } else {
                to_write = write(other, buffer + i, sizeof(char));
            }
            if (to_write == -1) {
                clear(input, digits, other, buffer);
                return 3;
            }
        }
    }
    clear(input, digits, other, buffer);
    return 0;
}
