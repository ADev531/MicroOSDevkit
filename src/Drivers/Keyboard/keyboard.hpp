#pragma once

#include "../../IOPorts.h"

struct kbddrv {
    public:
    void reset();
    unsigned char get();
};

typedef struct kbddrv KeyboardDriver;

class Keyboard {
    public:
        /// @brief Driver for Keyboard class.
        static KeyboardDriver driver;

        /// @brief Resets keyboard.
        static void Reset();

        /// @brief Provides Console Key Inputting.
        /// @return Key char.
        static unsigned char GetKey();

        /// @brief Provides normal key inputting.
        /// @return Key char.
        static unsigned char Get();
        static char* GetKeyBuffer();
        static void ClearKeyBuffer();
};