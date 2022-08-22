#pragma once

#include <stddef.h>
#include <stdint.h>

#define PMM_BLOCK_SIZE 4096
#define BLOCKS_PER_U32 32

// Initialize global state for PMM
void pmm_init(uint64_t base_addr, size_t mem_size);

// Allocate `n` contiguous page frames and return the starting address
void* pmm_alloc_frame(size_t n);
