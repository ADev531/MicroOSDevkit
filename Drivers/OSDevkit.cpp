#include "../Library/io.h"
#include "../mboot/info.h"
#include "../Library/convert.hpp"

extern int main();
extern void idt_init(void);

extern "C" void osdevkitmain(unsigned long magic, unsigned long addr) {
    multiboot_info_t* info = (multiboot_info_t*)addr;
    char buffer[256];
    VGAConsole::Clear(0x07);
    idt_init();
    VGAConsole::ResetKeyboard();
    Print("Booted from %s.\n", info->boot_loader_name);
    Print("Memory size is %s bytes.\n", tostring(info->mem_upper, buffer));
    main();
}