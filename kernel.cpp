#include "Library/io.h"
#include "Library/memory.h"

int main() {
    Print("Hello, world!\n");
    while (1) {
        unsigned char key = GetKey();
        if (key != 0xFF) {
            Print("%c", key);
        }
    }
    return 0;
}