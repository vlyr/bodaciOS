#include <io.h>
#include <keyboard.h>

uint8_t get_scancode() {
    while (!(inb(0x64) & 1))
        asm volatile("pause");

    return inb(0x60);
}
