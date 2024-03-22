#pragma once

#include "../../IOPorts.h"

class Keyboard {
    public:
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