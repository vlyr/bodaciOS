#include <mem.h>

void* memset(void* addr, uint8_t byte, size_t size) {
    uint8_t* ptr = addr;

    for (size_t i = 0; i < size; i++) {
        ptr[i] = byte;
    }

    return addr;
}

void* memcpy(void* dest, const void* src, size_t size) {
    uint8_t* dp = dest;
    const uint8_t* sp = src;

    while (size--) {
        *dp++ = *sp++;
    }

    return dest;
}
