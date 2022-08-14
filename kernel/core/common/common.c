#include <vga.h>
#include <stdarg.h>
#include <common.h>

void klog(enum log_message_type type, const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    vga_color_t default_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    switch (type) {
    case LOG_MESSAGE_DEBUG: {
        vga_color_t color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
        vga_print(color, "[DEBUG]");
        break;
    }
    case LOG_MESSAGE_WARN: {
        vga_color_t color = vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
        vga_print(color, "[WARN]");
        break;
    }
    case LOG_MESSAGE_ERROR: {
        vga_color_t color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
        vga_print(color, "[ERROR]");
        break;
    }
    }

    vga_print(VGA_DEFAULT_COLOR, ": ");

    vga_vprintf(VGA_DEFAULT_COLOR, msg, args);
}

__attribute__((noreturn)) void panic(const char* message) {
    klog(LOG_MESSAGE_ERROR, "KERNEL PANIC | %s", message);

    __asm__("hlt");

    // Hack to get the compiler to shut up
    for (;;)
        ;
}

