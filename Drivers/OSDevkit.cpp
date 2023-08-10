#include "VGAConsole.hpp"
#include "../mboot/1/info.h"

extern int main();

extern "C" void osdevkitmain(unsigned long magic, unsigned long addr) {
    multiboot_info_t* info = (multiboot_info_t*)addr;
    VGAConsole::Clear(0x07);
    VGAConsole::Print("Booted by ");
    VGAConsole::Print(info->boot_loader_name);
    VGAConsole::Print("\n");
    main();
}