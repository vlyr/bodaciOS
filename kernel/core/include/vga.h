#pragma once
#include <stdint.h>
#include <stddef.h>

typedef uint8_t vga_color_t;
typedef uint16_t vga_entry_t;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_BUFFER = (uint16_t*) 0xb8000;

// https://wiki.osdev.org/Meaty_Skeleton
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline vga_color_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline vga_entry_t vga_entry(unsigned char c, vga_color_t color) {
    return (uint16_t) c | (uint16_t) color << 8;
}

void vga_initialize();
void vga_print_char(vga_entry_t c);
void vga_print(const char* string);
void vga_printf(const char* format, ...);
