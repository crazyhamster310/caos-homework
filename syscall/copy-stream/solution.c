long syscall(long number, ...);

void _start() {
    const unsigned int buffer_size = 1024;
    char buffer[buffer_size];
    int real_size = 0;
    while ((real_size = syscall(0, 0, buffer, buffer_size)) > 0) {
        syscall(1, 1, buffer, real_size);
    }
    syscall(60, 0);
}