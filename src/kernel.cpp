// Include required librarys
#include "Library/io.h"
#include "Library/memory.h"
#include "Library/ExceptionTester.hpp"
#include "Library/kernel.hpp"
#include "Drivers/Keyboard/keyboard.hpp"
#include "Drivers/VGAConsole.hpp"
#include "Drivers/VGAScreen.hpp"

void Kernel::Init() {
    Print("Hello, My First OS!\n");
}

void Kernel::KernelLoop() {
    Print(">");
    while (1) {
        char Result = Keyboard::GetKey();

        if (Result == '\n') {
            //ExceptionTester::DivideByZeroTest();
            char* buffer = Keyboard::GetKeyBuffer();
            char* cmd = buffer;
            if (StringMatches(cmd, "help") == 0) {
                Print("------- My First OS! -------\n \
Currently i386 arch is only supported.\n \
You can modifiy this os with c++!\n \
If you want to modify this Kit, do push request to\n \
Github! \n");
            }
            else if (StringMatches(cmd, "tst") == 0) {
                Print("Test Message!\n");
            }
            else if (StringMatches(cmd, "gui") == 0) {
                Print("Lets start the gui.");
                VGAScreen* screen = new VGAScreen();
                screen->DrawFilledRect(0, 0, 400, 600, 1);
                while(1);
            }
            else if (StringMatches(cmd, "exception") == 0) {
                ExceptionTester::DivideByZeroTest();
            }
            else {
                Print("Unknown Command : %s\n", cmd);
            }
            Keyboard::ClearKeyBuffer(); // Clean key buffer.
            break;
        }
    }
}
