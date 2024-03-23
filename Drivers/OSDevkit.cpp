#include "../Library/io.h"
#include "../Library/memory.h"
#include "../mboot/bootinfo.h"
#include "../Library/convert.hpp"
#include "../Library/kernel.hpp"

extern void idt_init(void);

extern "C" void osdevkitmain(unsigned long magic, unsigned long addr) {
    multiboot_info_t* info = (multiboot_info_t*)addr;
    VGAConsole::Init();

    // Init boot informations.
    BootInfo::CommandLine = info->cmdline;
    BootInfo::VBEMode = info->vbe_mode;
    BootInfo::MultibootInfo = info;

    char buffer[256];
    idt_init();
    Keyboard::Reset();
    Print("Booted from %s.\n", info->boot_loader_name);
    Print("Memory size is %s bytes.\n", tostring(info->mem_upper, buffer));
    
    Kernel* kernel = new Kernel();
    kernel->Init();

    while (1)
    {
        kernel->KernelLoop();
    }
}