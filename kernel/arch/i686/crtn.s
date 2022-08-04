// https://wiki.osdev.org/Calling_Global_Constructors#x86_.2832-bit.29
.section .init
    /* gcc will nicely put the contents of crtend.o's .init section here. */
    popl %ebp
    ret

.section .fini
    /* gcc will nicely put the contents of crtend.o's .fini section here. */
    popl %ebp
    ret
