#include <stdint.h>
typedef unsigned int size_t;

void* operator new (size_t size) {
    void* buf[size];
    return buf;
}
