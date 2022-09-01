#include <mem.h>
#include <stdint.h>

static uint64_t page_directory_pointer_table[4] = {0, 0, 0, 0};
static uint64_t page_directory[512] __attribute__((aligned(4096)));

void* vmm_init() {
    page_directory_pointer_table[0] = (uint64_t) &page_directory;
    page_directory[0] = VMM_PDPT_PRESENT | VMM_PDPT_WRITE | VMM_PDPT_PAGE_SIZE;

    return page_directory;
}
