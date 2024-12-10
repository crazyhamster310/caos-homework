#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char const* argv[]) {
    int fd = open(argv[1], O_RDONLY);
    struct Item buffer;
    off_t offset = 0;
    do {
        int amount = read(fd, &buffer, sizeof(struct Item));
        if (amount == 0) {
            break;
        }
        printf("%d ", buffer.value);
        offset = buffer.next_pointer;
        lseek(fd, offset, SEEK_SET);
    } while(offset);
    close(fd);
    return 0;
}
