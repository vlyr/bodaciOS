#pragma once

#include <stddef.h>
#include <stdint.h>

#define PMM_ACCESS_UNIT_LENGTH 32
#define PMM_BLOCK_SIZE 4096

// Initialize global state & initialize PMM at `base_address` (the top of the kernel's stack)
void pmm_init(void* base_address, size_t mem_size);

// Initialize a region of `size` pages of memory
// Returns a pointer to `base_addr`.
void* pmm_init_region(uint64_t base_addr, size_t size);

// Deinitialize a region of `size` pages of memory
void pmm_deinit_region(uint64_t base_addr, size_t size);

// Allocate a block and return the starting address of it
void* pmm_alloc_block();
