#pragma once

#include <stdarg.h>

#include "../Drivers/VGAConsole.hpp"

int Print(const char* format, ...);
void io_wait();