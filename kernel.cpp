#include "Library/io.h"
#include "Drivers/VGAScreen.hpp"
#include "Library/memory.h"
#include "Drivers/Keyboard/keyboard.hpp"

int main() {
    Print("Hello, world!\n");
    VGAConsole::PrintChar(GetKey());
    while (1);
    return 0;
}