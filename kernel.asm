[bits 32]

section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002+0x00)

global start
global load_idt
global keyboard_handler
extern osdevkitmain
start:
    cli
    mov esp, kernel_stack
    push 0 ; Flag register reset
    popf
    push ebx ; multiboot info pointer
    push eax ; magic
    call osdevkitmain
    hlt
load_idt:
    mov edx, [esp+4]
    lidt [edx]
    sti
    ret
keyboard_handler:
    iretd

section .bss
resb 16834
kernel_stack:

