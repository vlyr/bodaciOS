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

        switch (t->type) {
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
            vga_printf("mem_lower: %dKB\n", ((struct multiboot_tag_basic_meminfo*) t)->mem_lower);
            vga_printf("mem_upper: %dKB\n", ((struct multiboot_tag_basic_meminfo*) t)->mem_upper);
        }
        }

        offset += t->size + (t->size % 8);
        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }
}

void kmain(uint64_t* multiboot_information) {
    vga_initialize();

    print_multiboot_information(multiboot_information);
}

