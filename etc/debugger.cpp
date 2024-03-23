#include "../src/IOPorts.h"

#ifdef SERIALDEBUG

extern "C" void SendDebuggerMessage(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
    {
        outb(0x3F8, str[i]);
    }
}

#else

extern "C" void SendDebuggerMessage(char* str) {
    // do nothing because we don't need debugger now
}

#endif