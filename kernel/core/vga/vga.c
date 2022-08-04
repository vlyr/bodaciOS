#include "../include/vga.h"

uint16_t* VGA_BUFFER;

void vga_initialize() {
    VGA_BUFFER = (uint16_t*) 0xb8000;

    // Print '!'
    VGA_BUFFER[21] = 0x0F21;
}
