#include <stdint.h>
#include <string.h>
#include <integer.h>

uint16_t* vga_buffer;

void print_char(u8 c) {
    vga_buffer[8] = 0x0F21;
}

void kmain() {
    vga_buffer = (uint16_t*) 0xb8000;
    vga_buffer[1] = 0x0F21;

    print_char('!');

    int len = strlen("ballsack");
}
