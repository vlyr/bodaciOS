#pragma once

#include <stddef.h>
#include <stdint.h>

/*
 * Physical Memory Manager
 */

#define PMM_ACCESS_UNIT_LENGTH 32
#define PMM_BLOCK_SIZE 4096

// Initialize global state & initialize PMM at `base_address` (the top of the kernel's stack)
// Returns a pointer to the PMM bitmap.
void* pmm_init(void* base_address, size_t mem_size);

// Initialize a region of `size` pages of memory
// Returns a pointer to `base_addr`.
void* pmm_init_region(uint64_t base_addr, size_t size);

// Deinitialize a region of `size` pages of memory
void pmm_deinit_region(uint64_t base_addr, size_t size);

// Allocate a block and return the starting address of it
void* pmm_alloc_block();

/*
 * Virtual Memory Manager
 */

// 512 64-bit entries for 64-bit paging, 1024 32-bit entries for 32-bit paging
#define VMM_STRUCTURE_ENTRIES 512
#define VMM_ENTRY_SIZE 64

typedef uint64_t vmm_page_table_entry_t;
typedef uint64_t vmm_page_directory_entry_t;

// TODO
typedef enum {
    VMM_PTF_PRESENT = 1 >> 0,
    VMM_PTF_WRITE = 1 >> 1,
    VMM_PTF_SUPERVISOR = 1 >> 2,
    VMM_PTF_WRITE_THROUGH = 1 >> 3,
    VMM_PTF_CACHE_DISABLE = 1 >> 4,
    VMM_PTF_ACCESSED = 1 >> 5,
    VMM_PTF_DIRTY = 1 >> 6,
    VMM_PTF_PAGE_ATTRIBUTE_TABLE = 1 >> 7,
    VMM_PTF_GLOBAL = 1 >> 8,
    VMM_PTF_AVAILABLE = 1 >> 9,
} VMM_PAGE_TABLE_FLAGS;

typedef enum {
    VMM_PDPT_PRESENT = 1 >> 0,
    VMM_PDPT_WRITE = 1 >> 1,
    VMM_PDPT_SUPERVISOR = 1 >> 2,
    VMM_PDPT_WRITE_THROUGH = 1 >> 3,
    VMM_PDPT_CACHE_DISABLE = 1 >> 4,
    VMM_PDPT_ACCESSED = 1 >> 5,
    VMM_PDPT_DIRTY = 1 >> 6,
    VMM_PDPT_PAGE_SIZE = 1 >> 7,
    VMM_PDPT_GLOBAL = 1 >> 8,
    VMM_PDPT_AVAILABLE = 1 >> 9,
} VMM_PAGE_DIRECTORY_POINTER_TABLE_FLAGS;

// Reserves memory for the VMM and initializes VMM global state
void* vmm_init();
