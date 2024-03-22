#pragma once
#include "../IOPorts.h"
#include "./Keyboard/keyboard.hpp"

static char* VGAMemory = (char*)0xb8000;

static const int CONSOLE_WIDTH = 160;
static const int CONSOLE_HEIGHT = 50;

class VGAConsole {
    static int line;
    static int col;

    public:
        static void Init() {
            line = 0;
            col = 0;
            Clear();
        }

        static void PrintChar(char c) {
            if (c == '\n') {
                line += 1;
                col = 0;
                return;
            }

            VGAMemory[(line * 160) + (col * 2)] = c;
            col++;
            return;
        }

        static void Print(const char* text) {
            for (int i = 0; text[i] != 0; ++i) {
                if (col == 80)
                {
                    line += 1;
                    col = 0;
                }
                else
                {
                    PrintChar(text[i]);
                }
            }
        }

        static int GetCol() {
            return col;
        }

        static int GetLine() {
            return line;
        }

        static void SetCol(int ncol) {
            col = ncol;
        }

        static void SetLine(int nline) {
            line = nline;
        }

        static void Clear(int c) {
            for (int i = 0; i < CONSOLE_HEIGHT * CONSOLE_WIDTH; ++i) {
                if (col % 2 != 0) {
                    VGAMemory[(line * 160) + col] = c;
                } else {
                    VGAMemory[(line * 160) + col] = 0;
                }
                col++;
            }
            line = 0;
            col = 0;
        }

        static void Clear() {
            Clear(0x07);
        }
};