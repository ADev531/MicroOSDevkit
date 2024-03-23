#pragma once

/// @brief Class for testing exception handlers.
class ExceptionTester {
    public:

    /// @brief Tests Divide by Zero exception handler.
    static void DivideByZeroTest()
    {
        int zero = 0;

        int tmp = 1 / zero;
    }
};