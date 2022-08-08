#include <stdint.h>
#include <string.h>
#include <vga.h>
#include <multiboot.h>
#include <limits.h>

void print_multiboot_information(uint64_t* multiboot_information) {
    vga_printf("mbi size | %d\n", *multiboot_information);

    size_t offset = 8;
    struct multiboot_tag* t = (struct multiboot_tag*) (multiboot_information + offset);

    while (t->type != MULTIBOOT_TAG_TYPE_END) {
        vga_printf("multiboot tag | size: %d, type: %d\n", t->size, t->type);

        offset += t->size + (t->size % 8);
        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }
}

void kmain(uint64_t* multiboot_information) {
    vga_initialize();

    print_multiboot_information(multiboot_information);

    vga_printf("printf string test | %s\n", "test string");
    vga_printf("printf char test | %c\n", 'h');
    vga_printf("printf integer test | %d\n", 123);
}

