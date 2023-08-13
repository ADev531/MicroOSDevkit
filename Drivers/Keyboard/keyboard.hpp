#pragma once

#include "../../IOPorts.h"

class Keyboard {
    public:
        static unsigned char GetKey();
        static char* GetKeyBuffer();
        static void ClearKeyBuffer();
};