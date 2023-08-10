#pragma once

static char* VGAMemory = (char*)0xb8000;
static int line = 0;
static int col = 0;

static const int CONSOLE_WIDTH = 160;
static const int CONSOLE_HEIGHT = 50;

class VGAConsole {
    public:
        static void Print(const char* text) {
            for (int i = 0; text[i] != 0; ++i) {
                if (col == 80) {
                    line += 1;
                    col = 0;
                } else if (text[i] == '\n') {
                    line += 1;
                    col = 0;
                } else {
                    VGAMemory[(line * 160) + (col * 2)] = text[i];
                    col++;
                }
            }
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
};