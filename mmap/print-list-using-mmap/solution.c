#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, const char* argv[]) {
    const char* file_name = argv[1];
    int fd = open(file_name, O_RDONLY);
    struct stat st_buffer;
    fstat(fd, &st_buffer);
    if (st_buffer.st_size == 0) {
        close(fd);
        return 0;
    }
    char* content = mmap(NULL, st_buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    struct Item* item = (struct Item*)malloc(sizeof(struct Item));
    do {
        memcpy(item, content + item->next_pointer, sizeof(struct Item));
        printf("%d ", item->value);
    } while(item->next_pointer);
    munmap(content, st_buffer.st_size);
    close(fd);
    return 0;
}