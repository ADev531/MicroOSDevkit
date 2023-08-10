#include "../Library/io.h"
#include "../mboot/info.h"

extern int main();

extern "C" void osdevkitmain(unsigned long magic, unsigned long addr) {
    multiboot_info_t* info = (multiboot_info_t*)addr;
    VGAConsole::Clear(0x07);
    Print("Booted from %s.\n", info->boot_loader_name);
    main();
}