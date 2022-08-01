#include <stdint.h>

void kmain() {
    uint8_t* vga_buffer = (uint8_t*) 0xb8000;
    vga_buffer[0] = (uint8_t) 0x0F21;
}
