#include <stdint.h>
#include <string.h>
#include "core/include/vga.h"

void print_char(uint8_t c) {
}

void kmain() {
    print_char('!');

    vga_initialize();
}
