#include <stdint.h>
#include <string.h>
#include <vga.h>

void kmain() {
    vga_initialize();
    strlen("123");

    vga_printf("Hello, world %c", 246);
}
