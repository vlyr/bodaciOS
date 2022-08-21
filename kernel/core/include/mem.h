#include <stddef.h>

#define PMM_BLOCK_SIZE 4096

// Allocate `n` contiguous page frames and return the starting address
void* pmm_alloc_frame(size_t n);
