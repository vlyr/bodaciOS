#include <vga.h>
#include "../include/common.h"

__attribute__((noreturn)) void panic(const char* message) {
    vga_printf("KERNEL PANIC | %s", message);

    __asm__("hlt");

    // Hack to get the compiler to shut up
    for (;;)
        ;
}

__attribute__((noreturn)) void __stack_chk_fail(void) {
#if __STDC_HOSTED__
    abort();
#else
    panic("Stack smashing detected");
#endif
    for (;;)
        ;
}
