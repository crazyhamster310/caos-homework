#include <stdio.h>
#include <limits.h>
#include <linux/limits.h>
#include <sys/stat.h>

int main() {
    char buffer[PATH_MAX];
    int size = 0;
    while (scanf("%s", buffer) > 0) {
        struct stat st_buffer;
        stat(buffer, &st_buffer);
        if (S_ISREG(st_buffer.st_mode)) {
            size += st_buffer.st_size;
        }
    }
    printf("%d", size);
    return 0;
}