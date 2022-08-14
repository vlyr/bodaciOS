#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <vga.h>
#include <limits.h>
#include <stdbool.h>

size_t vga_row;
size_t vga_col;

enum fmt_state {
    FMT_STATE_ESCAPE,
    FMT_STATE_REGULAR,
};

void vga_initialize() {
    vga_row = 0;
    vga_col = 0;

    // Clear out the buffer
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t idx = y * VGA_WIDTH + x;

            vga_color_t black = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK);
            VGA_BUFFER[idx] = vga_entry(' ', black);
        }
    }
}

void vga_print_char(unsigned char c, vga_color_t color) {
    if (vga_col + 1 > VGA_WIDTH) {
        vga_col = 0;
        vga_row += 1;
    }

    // Check for special characters
    if (c == '\n') {
        vga_row++;
        vga_col = 0;
        return;
    }

    vga_entry_t entry = vga_entry(c, color);
    size_t index = (VGA_WIDTH * vga_row) + vga_col;

    VGA_BUFFER[index] = entry;

    vga_col += 1;
}

void vga_print(vga_color_t color, const char* string) {
    for (size_t i = 0; i < strlen(string); i++) {
        uint8_t c = string[i];

        vga_print_char(c, color);
    }
}

// TODO: %x and %p
void vga_vprintf(vga_color_t color, const char* string, va_list args) {
    char current;
    size_t idx = 0;

    enum fmt_state state = FMT_STATE_REGULAR;

    while ((current = string[idx])) {
        switch (state) {
        case FMT_STATE_REGULAR: {
            if (current == '%') {
                state = FMT_STATE_ESCAPE;
            } else {
                vga_print_char(current, color);
            }
            break;
        }

        case FMT_STATE_ESCAPE: {
            switch (current) {
            case 'c': {
                char c = va_arg(args, int);
                vga_print_char(c, color);
                break;
            }

            case 's': {
                char* s = va_arg(args, char*);

                while (*s) {
                    vga_print_char(*s++, color);
                }

                break;
            }

            case 'd': {
                long long i = va_arg(args, long long);

                char* buffer = "";
                char* new = fmt_int(i, buffer, 10);

                while (*new) {
                    vga_print_char(*new ++, color);
                }

                break;
            }
            }

            state = FMT_STATE_REGULAR;
        }
        }

        idx++;
    }
}

void vga_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vga_color_t color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    vga_vprintf(color, fmt, args);
}
