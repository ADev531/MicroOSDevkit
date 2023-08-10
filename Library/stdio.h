#pragma once

#include "../Drivers/VGAConsole.hpp"

int printf(const char* format, ...) {
    VGAConsole::Print(format);
    return 0;
}