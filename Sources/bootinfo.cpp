#include "../mboot/bootinfo.h"

char* BootInfo::CommandLine = (char*)"";
uint16_t BootInfo::VBEMode = 0;
multiboot_info_t* BootInfo::MultibootInfo = nullptr;