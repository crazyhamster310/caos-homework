long syscall(long number, ...);

void _start() {
    char buffer;
    while (syscall(0, 0, &buffer, 1) > 0) {
        syscall(1, 1, &buffer, 1);
    }
    syscall(60, 0);
}