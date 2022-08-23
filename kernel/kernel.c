#include <stdint.h>
#include <string.h>
#include <multiboot.h>
#include <limits.h>
#include <common.h>
#include <vga.h>
#include <keyboard.h>
#include <mem.h>

void print_multiboot_information(uint64_t* multiboot_information) {
    // klog(LOG_MESSAGE_DEBUG, "mbi size | %d\n", *multiboot_information);

    size_t offset = 8;
    struct multiboot_tag* t = (struct multiboot_tag*) (multiboot_information + offset);

    while (t->type != MULTIBOOT_TAG_TYPE_END) {
        switch (t->type) {
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: {
            break;
        }

        case MULTIBOOT_TAG_TYPE_MMAP: {
            multiboot_memory_map_t* mmap;

            for (mmap = ((struct multiboot_tag_mmap*) t)->entries;
                 (multiboot_uint8_t*) mmap < (multiboot_uint8_t*) t + t->size;
                 mmap = (multiboot_memory_map_t*) ((unsigned long) mmap +
                                                   ((struct multiboot_tag_mmap*) t)->entry_size))
                if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
                    klog(LOG_MESSAGE_DEBUG,
                         "memory region from multiboot struct: addr = %x, len = %d\n", mmap->addr,
                         mmap->len);
                    // pmm_init_region(mmap->addr, mmap->len / 1024);
                }

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

    // Gotta find a more sane way of iterating over the multiboot tags
    /*struct multiboot_tag* t = (struct multiboot_tag*) (multiboot_information + 8);

    while (1) {
        if (t->type == MULTIBOOT_TAG_TYPE_BASIC_MEMINFO) {
            pmm_init(1024 + ((struct multiboot_tag_basic_meminfo*) t)->mem_upper);
            klog(LOG_MESSAGE_DEBUG, "PMM initialized\n");

            break;
        }

        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }*/

    print_multiboot_information(multiboot_information);

    /*void* frame = pmm_alloc_block();
    klog(LOG_MESSAGE_DEBUG, "address returned from `pmm_alloc_frame`: %x\n", frame);

    void* f2 = pmm_alloc_block();
    klog(LOG_MESSAGE_DEBUG, "address returned from `pmm_alloc_frame`: %x\n", f2);*/

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

