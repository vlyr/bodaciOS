
#include <stdint.h>
#include <stddef.h>
#include "multiboot.h"

extern void setup_long_mode();
extern void enter_kernel(void* entry, uint32_t multiboot_info);

// https://wiki.osdev.org/Creating_a_64-bit_kernel_using_a_separate_loader
char* kernel_elf_space[sizeof(elf_file_data_t)];
/* Pointer to elf file structure (remember there is no memory management yet) */
elf_file_data_t* kernel_elf = (elf_file_data_t*) kernel_elf_space;                                          

/* This function parses the ELF file and returns the entry point */
void* load_elf_module(multiboot_uint32_t mod_start, multiboot_uint32_t mod_end) {
    /* Parses ELF file and returns an error code */
    unsigned long err = parse_elf_executable((void*)mod_start, sizeof(elf_file_data_t), kernel_elf);

    /* No errors occurred while parsing the file */
    if(err == 0) {                                                                                      
	for(int i = 0; i < kernel_elf->numSegments; i++) {
	    /* Load all the program segments into memory */
	    elf_file_segment_t seg = kernel_elf->segments[i];

	    /*  if you want to do relocation you should do so here, */
	    const void* src = (const void*) (mod_start + seg.foffset);

	    /*  though that would require some changes to parse_elf_executable */
	    memcpy((void*) seg.address, src, seg.flength);
	}
	/* Finally we can return the entry address */
	return (void*) kernel_elf->entryAddr;
    }
    return NULL;
}

/* This function gets called by the bootloader */
void lmain(const void* multiboot_struct) {
    /* Make pointer to multiboot_info_t struct */
    const multiboot_info_t* mb_info = multiboot_struct;

    /* Get flags from mb_info */
    multiboot_uint32_t mb_flags = mb_info->flags;
 
    void* kentry = NULL;

    /* Check if modules are available */
    if (mb_flags & MULTIBOOT_INFO_MODS) {
	/* Get the amount of modules available */
	multiboot_uint32_t mods_count = mb_info->mods_count;

	/* And the starting address of the modules */
	multiboot_uint32_t mods_addr = mb_info->mods_addr;
 
        for (uint32_t mod = 0; mod < mods_count; mod++) {
            multiboot_module_t* module = (multiboot_module_t*)(mods_addr + (mod * sizeof(multiboot_module_t)));
        }
    }
}
