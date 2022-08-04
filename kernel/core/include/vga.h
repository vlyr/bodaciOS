#include <stdint.h>

extern uint16_t* VGA_BUFFER;

void vga_initialize();
void vga_print(const char* string);
void vga_print_char(uint8_t c);
