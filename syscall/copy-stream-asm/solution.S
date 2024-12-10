    .intel_syntax noprefix
    .global _start

    .data
buffer:
    .fill 1024, 1, 0

    .text
_start:
    mov rbx, 0

    mov rax, 0
    mov rdi, 0
    lea rsi, [buffer]
    mov rdx, 1024
    syscall

    mov rbx, rax

    mov rax, 1
    mov rdi, 1
    lea rsi, [buffer]
    mov rdx, rbx
    syscall

    mov rax, 60
    mov rdi, 0
    syscall