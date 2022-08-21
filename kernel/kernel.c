#include <stdint.h>
#include <string.h>
#include <multiboot.h>
#include <limits.h>
#include <common.h>
#include <vga.h>
#include <keyboard.h>

void print_multiboot_information(uint64_t* multiboot_information) {
    // klog(LOG_MESSAGE_DEBUG, "mbi size | %d\n", *multiboot_information);

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
        case MULTIBOOT_TAG_TYPE_MMAP: {
            multiboot_memory_map_t* mmap;

            for (mmap = ((struct multiboot_tag_mmap*) t)->entries;
                 (multiboot_uint8_t*) mmap < (multiboot_uint8_t*) t + t->size;
                 mmap = (multiboot_memory_map_t*) ((unsigned long) mmap +
                                                   ((struct multiboot_tag_mmap*) t)->entry_size))

                klog(LOG_MESSAGE_DEBUG, "base_addr = 0x%x%x | length = %dKB, type = %d\n",
                     (unsigned) (mmap->addr >> 32), (unsigned) (mmap->addr & 0xffffffff),
                     ((unsigned) (mmap->len >> 32) + (unsigned) (mmap->len & 0xffffffff)) / 1024,
                     (unsigned) mmap->type);
            break;
        }
        }

        offset += t->size + (t->size % 8);
        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }
}

void kmain(uint64_t* multiboot_information) {
    vga_initialize();

    klog(LOG_MESSAGE_ERROR, "error message test\n");
    klog(LOG_MESSAGE_WARN, "warning message test\n");
    print_multiboot_information(multiboot_information);

    char cmd_buffer[128] = "";
    size_t cmd_buffer_idx;

    // Enter shell loop
    for (;;) {
        keyboard_keycode keycode = keyboard_get_key();

        if (keycode < 0x80) {
            if (keycode == KEYBOARD_KEY_ENTER_PRESSED) {
                vga_newline();

                if (!strcmp(cmd_buffer, "pwd")) {
                    vga_printf("current directory\n");
                }

                klog(LOG_MESSAGE_DEBUG, "command buffer | %s\n", cmd_buffer);

                memset(cmd_buffer, 0x0, 128);
                cmd_buffer_idx = 0;

                continue;
            }

            cmd_buffer[cmd_buffer_idx] = keycode;
            cmd_buffer_idx++;

            vga_printf("%c", keycode);
        }
    }
}

