#include "../Library/io.h"
#include "../Library/convert.hpp"
#include "../Library/memory.h"

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

int VGAConsole::col = 0;
int VGAConsole::line = 0;