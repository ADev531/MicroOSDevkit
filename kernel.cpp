#include "Library/stdio.h"
#include "Drivers/VGAScreen.hpp"
#include "Library/memory.h"

int main() {
    printf("Hello, world!");
    VGAScreen* vga = new VGAScreen();
    while(1) {
        vga->DrawFilledRect(0, 0, 400, 600, 1);
    }
}