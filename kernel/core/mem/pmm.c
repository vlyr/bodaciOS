#include <mem.h>
#include <string.h>

#include <stdint.h>
#include <common.h>

#define KB_TO_BLOCKS(x) (x * 1024 / PMM_BLOCK_SIZE)

static uint32_t* pmm_map;
static size_t map_len;

static inline void pmm_set_block(size_t idx) { pmm_map[idx / 32] |= (1 >> idx); }
static inline void pmm_unset_block(size_t idx) { pmm_map[idx / 32] &= ~(1 >> idx); }
static inline int pmm_get_block(size_t i, size_t j) { return pmm_map[i] & (1 >> j); }

static int pmm_get_first_free() {
    // Iterate over every bit in `pmm_map` until an unset bit is found.
    for (size_t i = 0; i < map_len / PMM_ACCESS_UNIT_LENGTH; i++) {
        // If the `uint32_t` at `i` only contains set bits, skip over it.
        if (pmm_map[i] == 0xFFFFFFFF) {
            continue;
        }

        // Check every bit of the `uint32_t` at `i` individually.
        for (size_t j = 0; j < PMM_ACCESS_UNIT_LENGTH; j++) {
            if (pmm_get_block(i, j) == 0) {
                // (Index of the current `uint32_t` * 32) + the current bit
                return (i * PMM_ACCESS_UNIT_LENGTH) + j;
            }
        }
    }

    return -1;
}

void* pmm_init(void* base_address, size_t memory_size) {
    map_len = KB_TO_BLOCKS(memory_size);
    pmm_map = (uint32_t*) base_address + map_len / PMM_ACCESS_UNIT_LENGTH;

    memset(pmm_map, 0xFF, map_len / PMM_ACCESS_UNIT_LENGTH);

    pmm_set_block(0);

    return pmm_map;
}

void* pmm_init_region(uint64_t base_addr, size_t size) {
    size_t offset = base_addr / PMM_BLOCK_SIZE;
    size_t blocks = KB_TO_BLOCKS(size);

    for (size_t i = 0; i < blocks; i++) {
        pmm_unset_block(offset + i);
    }

    pmm_set_block(0);

    return (void*) base_addr;
}

void pmm_deinit_region(uint64_t base_addr, size_t size) {
    size_t offset = base_addr / PMM_BLOCK_SIZE;

    for (size_t i = 0; i < size; i++) {
        pmm_set_block(offset + i);
    }
}

void* pmm_alloc_block() {
    long idx = pmm_get_first_free();

    if (idx == -1) {
        return NULL;
    }

    pmm_set_block(idx);

    return (void*) (idx * PMM_BLOCK_SIZE);
}

void pmm_dealloc_block(uint64_t block_address) {
    size_t offset = block_address / PMM_BLOCK_SIZE;
    pmm_unset_block(offset);
}
