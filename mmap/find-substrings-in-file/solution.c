#define _GNU_SOURCE

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    const char* file_name = argv[1];
    const char* pattern = argv[2];
    size_t pattern_len = strlen(pattern);
    int fd = open(file_name, O_RDONLY);
    struct stat st_buffer;
    fstat(fd, &st_buffer);
    char* content = mmap(NULL, st_buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    char* entry = content;
    size_t len = st_buffer.st_size;
    while (NULL != (entry = memmem(entry, len, pattern, pattern_len))) {
        size_t diff = entry - content;
        len = st_buffer.st_size - diff - 1;
        printf("%lu ", diff);
        ++entry;
    }
    munmap(content, st_buffer.st_size);
    close(fd);
    return 0;
}