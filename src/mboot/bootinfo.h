#pragma once
#include "info.h"

class BootInfo {
public:
    static char* CommandLine;
    static uint16_t VBEMode;
    static multiboot_info_t* MultibootInfo;
};