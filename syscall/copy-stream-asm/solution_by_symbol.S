    .intel_syntax noprefix
    .global _start

    .data
buffer:
    .byte 0

    .text
_start:
    mov rbx, 0
for:
    mov rax, 0
    mov rdi, 0
    lea rsi, [buffer]
    mov rdx, 1
    syscall

    mov rbx, rax
    push rax

    mov rax, 1
    mov rdi, 1
    lea rsi, [buffer]
    mov rdx, rbx
    syscall

    mov rax, 0
    pop rbx
    cmp rbx, rax
    jnz for

    mov rax, 60
    mov rdi, 0
    syscall