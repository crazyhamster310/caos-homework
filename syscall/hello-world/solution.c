long syscall(long number, ...);

void _start() {
    const char buffer[] = "Hello, World!\n";
    syscall(1, 1, buffer, sizeof(buffer) - 1);
    syscall(60, 0);
}
