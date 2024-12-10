#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void close_fd(int fd) {
    if (fd != -1) {
        close(fd);
    }
}

void clear(int input, int digits, int other) {
    close_fd(input);
    close_fd(digits);
    close_fd(other);
}

int main(int argc, char const* argv[]) {
    int input = open(argv[1], O_RDONLY);
    if (input == -1) {
        clear(input, -1, -1);
        return 1;
    }
    int digits = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    int other = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (digits == -1 || other == -1) {
        clear(input, digits, other);
        return 2;
    }
    char buffer_char;
    while (1) {
        ssize_t real_read_size = read(input, &buffer_char, sizeof(char));
        if (real_read_size == -1) {
            clear(input, digits, other);
            return 3;
        }
        if (real_read_size == 0) {
            break;
        }
        size_t to_write = 0;
        if (buffer_char >= '0' && buffer_char <= '9') {
            to_write = write(digits, &buffer_char, sizeof(char));
        } else {
            to_write = write(other, &buffer_char, sizeof(char));
        }
        if (to_write == -1) {
            clear(input, digits, other);
            return 3;
        }
    }
    clear(input, digits, other);
    return 0;
}
