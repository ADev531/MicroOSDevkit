#pragma once

#include "../Drivers/kerneldebugger.hpp"

/// @brief Basic kernel class for MicroOSDevkit.
class Kernel 
{
    public:

    Kernel() {
        SendDebuggerMessage("Kernel Created.\n");
    }

    /// @brief Init kernel.
    void Init();

    /// @brief Looping part of kernel.
    void KernelLoop();
};