[bits 32]

section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002+0x00)

global start
extern osdevkitmain
start:
    mov esp, kernel_stack

    push 0 ; Flag register reset
    popf

    push ebx ; multiboot info pointer
    push eax ; magic

    call osdevkitmain
.loop:
    jmp .loop

section .bss
resb 8192
kernel_stack:

