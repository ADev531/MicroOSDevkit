#pragma once
#include "../IOPorts.h"
#include "../Library/stdint.h"
#include "./Keyboard/keyboard.hpp"

static char* VGAMemory = (char*)0xb8000;

static int CONSOLE_WIDTH = 80;
static int CONSOLE_HEIGHT = 25;

class VGAConsole {
    static int line;
    static int col;

    public:
        static void Init() {
            line = 0;
            col = 0;
            Clear();
        }

        static void MoveCursor(int x, int y)
        {
            uint16_t pos = y * CONSOLE_WIDTH + x;
        
            outb(0x3D4, 0x0F);
            outb(0x3D5, (uint8_t) (pos & 0xFF));
            outb(0x3D4, 0x0E);
            outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
        }

        static void PrintChar(char c) {
            if (c == '\n') {
                line += 1;
                col = 0;
                MoveCursor(col, line);
                return;
            }

            VGAMemory[(line * CONSOLE_WIDTH * 2) + (col * 2)] = c;
            col++;
            MoveCursor(col, line);
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
            MoveCursor(col, line);
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
            col = 0;
            line = 0;
            for (int i = 0; i < CONSOLE_HEIGHT * CONSOLE_WIDTH * 2; ++i) {
                if (col % 2 != 0) {
                    VGAMemory[(line * (CONSOLE_WIDTH * 2)) + col] = c;
                } else {
                    VGAMemory[(line * (CONSOLE_WIDTH * 2)) + col] = 0;
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