#include "Library/io.h"
#include "Library/memory.h"
#include "Drivers/VGAScreen.hpp"

int main() {
    Print("Hello, My First OS!\n");
Prompt:
    Print(">");
    while (1) {
        char Result = Keyboard::GetKey();

        if (Result == '\n') {
            char* buffer = Keyboard::GetKeyBuffer();
            if (StringMatches(buffer, "help") == 0) {
                Print("------- My First OS! -------       \n \
Currently x86-32 only supported.   \n \
You can modifiy this os with c++!  \n \
If you want, do push request to    \n \
Github! \n");
            }
            else if (StringMatches(buffer, "tst") == 0) {
                Print("Test Message!\n");
            }
            else {
                Print("Unknown Command : %s\n", buffer);
            }
            Keyboard::ClearKeyBuffer(); // Run Command Before Clearing Buffer!
            break;
        }
    }

    goto Prompt;
    
    return 0;
}