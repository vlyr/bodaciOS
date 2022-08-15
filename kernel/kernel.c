#include <stdint.h>
#include <string.h>
#include <multiboot.h>
#include <limits.h>
#include <common.h>
#include <vga.h>

void print_multiboot_information(uint64_t* multiboot_information) {
    klog(LOG_MESSAGE_DEBUG, "mbi size | %d\n", *multiboot_information);

    size_t offset = 8;
    struct multiboot_tag* t = (struct multiboot_tag*) (multiboot_information + offset);

    while (t->type != MULTIBOOT_TAG_TYPE_END) {
        klog(LOG_MESSAGE_DEBUG, "multiboot tag | size: %d, type: %d\n", t->size, t->type);

        switch (t->type) {
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
            klog(LOG_MESSAGE_DEBUG, "mem_lower: %dKB\n",
                 ((struct multiboot_tag_basic_meminfo*) t)->mem_lower);
            klog(LOG_MESSAGE_DEBUG, "mem_upper: %dKB\n",
                 ((struct multiboot_tag_basic_meminfo*) t)->mem_upper);
        }
        }

        offset += t->size + (t->size % 8);
        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }
}

void kmain(uint64_t* multiboot_information) {
    vga_initialize();

    klog(LOG_MESSAGE_ERROR, "Error message test\n");
    klog(LOG_MESSAGE_WARN, "Warning message test\n");
    klog(LOG_MESSAGE_DEBUG, "Hex test: %x\n", 0x2F);

    print_multiboot_information(multiboot_information);
}

