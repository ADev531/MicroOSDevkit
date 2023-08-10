#pragma once

static inline void outb(unsigned short port, unsigned char value)
{
    asm volatile ("outb %%al,%%dx": :"dN"(port), "a"(value));
} 

static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0"
                : "=a"(ret)
                : "Nd"(port)
                : "memory");
    return ret;
}