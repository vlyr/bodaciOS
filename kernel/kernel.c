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
            pmm_init(0x0100000, ((struct multiboot_tag_basic_meminfo*) t)->mem_upper);

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

