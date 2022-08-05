#include <stdint.h>
#include <string.h>
#include "core/include/vga.h"

void kmain() {
    vga_initialize();

    vga_color_t color = vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
    vga_print("Hello, world!", color);
}
