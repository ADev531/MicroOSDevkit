#include "../../IOPorts.h"

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
            case 0x39: result = ' '; break; // 스페이스
            case 0x0E: result = 0x08; break; // 백스페이스 아스키코드 = 8
            default: result = 0xFF; break; 
                // 구현안된 것은 무시한다. 구분자는 0xFF
        }
        return result;
    }
}

unsigned char GetKey() {
    if (inb(0x64) & 0x01) {
        char key = transScan(inb(0x60));
        return key;
    }
    return 0xFF;
}