#include <stddef.h>
#include <vga.h>
#include <string.h>

size_t vga_row;
size_t vga_col;

void vga_initialize() {
    vga_row = 0;
    vga_col = 0;

    for(size_t y = 0; y < VGA_HEIGHT; y++) {
        for(size_t x = 0; x < VGA_WIDTH; x++) {
            // Clear the buffer (TODO)
        }
    }
}

void vga_print_char(vga_entry_t c) {
    if(vga_col + 1 > VGA_WIDTH) {
        vga_col = 0;
        vga_row += 1;
    }

    size_t index = (VGA_WIDTH * vga_row) + vga_col;

    VGA_BUFFER[index] = c;

    vga_col += 1;
}

void vga_print(const char* string, vga_color_t color) {
    for(size_t i = 0; i < strlen(string); i++) {
        uint8_t c = string[i];

        vga_entry_t entry = vga_entry(c, color);

        vga_print_char(entry);
    }
}
