#include "../Drivers/Keyboard/keyboard.hpp"
#include "../Drivers/kerneldebugger.hpp"
#include "../Drivers/VGAConsole.hpp"
#include "../Library/memory.h"

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

KeyboardDriver Keyboard::driver = (KeyboardDriver){};

static char buffer[256];
static int index = 0;

unsigned char Keyboard::GetKey() {
    unsigned char key = Keyboard::driver.get();
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
            VGAConsole::SetCol(VGAConsole::GetCol() - 2);
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

unsigned char Keyboard::Get() {
    unsigned char key = Keyboard::driver.get();
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

char* Keyboard::GetKeyBuffer() {
    return buffer;
}

void Keyboard::ClearKeyBuffer() {
    CleanArray(buffer);
    index = 0;
}

void Keyboard::Reset() {
    SendDebuggerMessage("Keyboard Reset\n");
    Keyboard::driver.reset();
}

unsigned char KeyboardDriver::get() {
    outb(0x20, 0x20);
    if (inb(0x64) & 0x01)
    {
        return transScan(inb(0x60));   
    }
    return 0xff;
}

void KeyboardDriver::reset() {
    outb(0x64, 0x20);
}