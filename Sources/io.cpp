#include "../Library/io.h"
#include "../Drivers/Keyboard/keyboard.hpp"
#include "../Library/convert.hpp"

int Print(const char* format, ...) {
    const char* string;

    va_list args;
    va_start(args, format);

    for(string = format; *string != 0; string++) {
        while(*string != '%') {
            if (*string == 0) {
                break;
            }
            else if (*string == '\n') {
                VGAConsole::PrintChar('\n');
                string++;
            } else {
                VGAConsole::PrintChar(*string);
                string++;
            }
        }
        if (*string == 0) {
            break;
        }

        string++;

        switch (*string)
        {
        case 's':
            VGAConsole::Print(va_arg(args, char*));
            break;
        case 'c':
            VGAConsole::PrintChar(va_arg(args, int));
            break;
        
        default:
            break;
        }
    }
    va_end(args);
    
    return 0;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

// Implementation of tostring()
char* tostring(int num, char* str)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    if (num < 0) {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / 10;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

namespace {
    unsigned char transScan(unsigned char target)
    {
        unsigned char result;

        switch (target) 
        {
            case 0x02: result = '1'; break;
            case 0x03: result = '2'; break;
            case 0x04: result = '3'; break;
            case 0x05: result = '4'; break;
            case 0x06: result = '5'; break;
            case 0x07: result = '6'; break;
            case 0x08: result = '7'; break;
            case 0x09: result = '8'; break;
            case 0x0A: result = '9'; break;
            case 0x0B: result = '0'; break;
            case 0x1E: result = 'a'; break;
            case 0x30: result = 'b'; break;
            case 0x2E: result = 'c'; break;
            case 0x20: result = 'd'; break;
            case 0x12: result = 'e'; break;
            case 0x21: result = 'f'; break;
            case 0x22: result = 'g'; break;
            case 0x23: result = 'h'; break;
            case 0x17: result = 'i'; break;
            case 0x24: result = 'j'; break;
            case 0x25: result = 'k'; break;
            case 0x26: result = 'l'; break;
            case 0x32: result = 'm'; break;
            case 0x31: result = 'n'; break;
            case 0x18: result = 'o'; break;
            case 0x19: result = 'p'; break;
            case 0x10: result = 'q'; break;
            case 0x13: result = 'r'; break;
            case 0x1F: result = 's'; break;
            case 0x14: result = 't'; break;
            case 0x16: result = 'u'; break;
            case 0x2F: result = 'v'; break;
            case 0x11: result = 'w'; break;
            case 0x2D: result = 'x'; break;
            case 0x15: result = 'y'; break;
            case 0x2C: result = 'z'; break;
            case 0x1c: result = 0x13;  break; // Enter
            case 0x39: result = ' '; break;  // Space
            case 0x0E: result = 0x08; break; // backspace ascii code = 8
            default: result = 0xFF; break; 
        }
        return result;
    }
}

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
}__attribute__((packed));

extern "C" void keyboard_handler();
extern "C" void load_idt(unsigned long *idt_ptr);
struct IDT_entry IDT[256];

#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

static char buffer[256];
static int index = 0;

unsigned char Keyboard::GetKey() {
    outb(0x20, 0x20);
    if (inb(0x64) & 0x01) {
        unsigned char key = transScan(inb(0x60));
        if (key == 0xff) {
            return 0;
        }
        else if (key == 0x13) {
            VGAConsole::Print("\n");
            return '\n';
        }
        else if (key == 0x08) {
            if (index > 0) {
                VGAConsole::SetCol(VGAConsole::GetCol() - 1);
                VGAConsole::PrintChar(' ');
                VGAConsole::SetCol(VGAConsole::GetCol() - 1);
                buffer[index - 1] = 0;
                index--;
                return '\b';
            }
            else {
                return '\b';
            }
        }
        buffer[index++] = key;
        VGAConsole::PrintChar(key);
        return key;
    }
    return 0;
}

unsigned char Keyboard::Get() {
    outb(0x20, 0x20);
    if (inb(0x64) & 0x01) {
        unsigned char key = transScan(inb(0x60));
        if (key == 0xff) {
            return 0;
        }
        else if (key == 0x13) {
            return '\n';
        }
        else if (key == 0x08) {
            if (index > 0) {
                buffer[index - 1] = 0;
                index--;
                return '\b';
            }
            else 
            {
                return '\b';
            }
        }
        buffer[index++] = key;
        return key;
    }
    return 0;
}

char* Keyboard::GetKeyBuffer() {
    return buffer;
}

void Keyboard::ClearKeyBuffer() {
    for (int i = 0; i < 256; ++i) {
        buffer[i] = 0;
    }
    index = 0;
}

void Keyboard::Reset() {
    outb(0x64, 0x20);
}

int VGAConsole::col = 0;
int VGAConsole::line = 0;

void idt_init(void) {
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];
	keyboard_address = (unsigned long)keyboard_handler;
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