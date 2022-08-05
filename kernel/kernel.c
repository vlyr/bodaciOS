#include <stdint.h>
#include <string.h>
#include <vga.h>

void kmain() {
    vga_initialize();

    vga_printf("printf string test | %s\n", "test string");
    vga_printf("printf char test | %c\n", 'h');
    vga_printf("printf integer test | %d\n", 123);
}
