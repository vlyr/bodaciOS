#include <stdint.h>
#include <string.h>
#include <multiboot.h>
#include <limits.h>
#include <common.h>
#include <vga.h>
#include <keyboard.h>
#include <mem.h>

void parse_multiboot(uint64_t* multiboot_information) {
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
                    pmm_init_region(mmap->addr, mmap->len / 1024);
                }

            break;
        }
        }

        offset += t->size + (t->size % 8);
        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }
}

void kmain(uint64_t* multiboot_information, uint64_t pmm_base_addr, uint64_t kernel_start) {
    vga_initialize();

    void* kernel_end;

    klog(LOG_MESSAGE_ERROR, "error message test\n");
    klog(LOG_MESSAGE_WARN, "warning message test\n");

    struct multiboot_tag* t = (struct multiboot_tag*) (multiboot_information + 8);

    while (1) {
        if (t->type == MULTIBOOT_TAG_TYPE_BASIC_MEMINFO) {
            kernel_end = pmm_init((void*) pmm_base_addr,
                                  ((struct multiboot_tag_basic_meminfo*) t)->mem_upper + 1024);
            break;
        }

        t = (struct multiboot_tag*) ((multiboot_uint8_t*) t + ((t->size + 7) & ~7));
    }

    parse_multiboot(multiboot_information);

    // Mark the kernel as reserved memory.
    pmm_deinit_region(kernel_start, (size_t) (kernel_end - kernel_start));

    klog(LOG_MESSAGE_DEBUG, "kernel_start = %d, kernel_end = %d\n", kernel_start, kernel_end);

    char* cmd_buffer = pmm_alloc_block();

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
