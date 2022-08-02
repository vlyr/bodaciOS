ENTRY(start)

SECTIONS {
    . = 1M;

    .boot BLOCK(4K) : ALIGN(4K)
    {
        /* ensure that the multiboot header is at the beginning */
    }

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot_header)
        *(.text)
    }
}
