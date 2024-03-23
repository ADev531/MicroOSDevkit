#include "../IOPorts.h"
#include "../Drivers/VGAConsole.hpp"
#include "../Drivers/kerneldebugger.hpp"
#include "../Drivers/pic.h"
#include "../Library/io.h"
#include "../Library/stdint.h"

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
}__attribute__((packed));

extern "C" void DefaultFaultHandler() {
    VGAConsole::Clear();
    VGAConsole::Print("CPU Exception is occurred. The system is halted.");
	SendDebuggerMessage("CPU Exception!\n");
    while(1);
}

extern "C" void keyboard_handler();
extern "C" void load_idt(unsigned long *idt_ptr);
struct IDT_entry IDT[256];

#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

void idt_init(void)
{
	SendDebuggerMessage("Trying to init idt\n");
    PIC::Remap(0x20, 0x28);

	unsigned long keyboard_address;
    unsigned long defaultfaulthandler_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];
	keyboard_address = (unsigned long)keyboard_handler;
    defaultfaulthandler_address = (unsigned long)DefaultFaultHandler;
    
    IDT_entry faulthandlerentry;

    faulthandlerentry.offset_lowerbits = defaultfaulthandler_address & 0xffff;
	faulthandlerentry.selector = KERNEL_CODE_SEGMENT_OFFSET;
	faulthandlerentry.zero = 0;
	faulthandlerentry.type_attr = INTERRUPT_GATE;
	faulthandlerentry.offset_higherbits = (defaultfaulthandler_address & 0xffff0000) >> 16;

    // Sets default fault handler.
    for (int i = 0; i < 19; i++) {
        IDT[i] = faulthandlerentry;
    }

	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;
	outb(0x20 , 0x11);
	outb(0xA0 , 0x11);
	outb(0x21 , 0x20);
	outb(0xA1 , 0x28);
	outb(0x21 , 0x00);
	outb(0xA1 , 0x00);
	outb(0x21 , 0x01);
	outb(0xA1 , 0x01);
	outb(0x21 , 0xff);
	outb(0xA1 , 0xff);
	idt_address = (unsigned long)IDT;
	idt_ptr[0] = (sizeof(struct IDT_entry)*256)+((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;
	load_idt(idt_ptr);
}

void PIC::Remap(int offset1, int offset2)
{
	SendDebuggerMessage("Remapping PIC\n");
    uint8_t a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}