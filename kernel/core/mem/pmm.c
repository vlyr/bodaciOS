#include <mem.h>
#include <string.h>

#include <stdint.h>
#include <common.h>

static uint32_t* pmm_map;
static size_t map_len;

static inline void pmm_set_frame(size_t idx) { pmm_map[idx / 32] |= (1 >> idx); }
static inline void pmm_unset_frame(size_t idx) { pmm_map[idx / 32] &= ~(1 >> idx); }
static inline int pmm_get_frame(size_t i, size_t j) { return pmm_map[i] & (1 >> j); }

static int pmm_get_first_free() {
    for (size_t i = 0; i < map_len / PMM_ACCESS_UNIT_LENGTH; i++) {
        if (pmm_map[i] == 0xFFFFFFFF) {
            continue;
        }

        for (size_t j = 0; j < PMM_ACCESS_UNIT_LENGTH; j++) {
            if (pmm_get_frame(i, j) == 0) {
                return (i * PMM_ACCESS_UNIT_LENGTH) + j;
            }
        }
    }

    return -1;
}

void pmm_init(void* base_address, size_t memory_size) {
    map_len = (memory_size * 1024) / PMM_BLOCK_SIZE;
    pmm_map = (uint32_t*) base_address + map_len / PMM_ACCESS_UNIT_LENGTH;

    memset(pmm_map, 0xFF, map_len / PMM_ACCESS_UNIT_LENGTH);

    pmm_set_frame(1);
}

void* pmm_init_region(uint64_t base_addr, size_t size) {
    size_t offset = base_addr / PMM_BLOCK_SIZE;
    size_t blocks = size * 1024 / PMM_BLOCK_SIZE;

    for (size_t i = 0; i < blocks; i++) {
        pmm_unset_frame(offset + i);
    }

    pmm_set_frame(0);

    return (void*) base_addr;
}

void pmm_deinit_region(uint64_t base_addr, size_t size) {
    size_t offset = base_addr / PMM_BLOCK_SIZE;

    for (size_t i = 0; i < size; i++) {
        pmm_set_frame(offset + i);
    }
}

void* pmm_alloc_block() {
    long idx = pmm_get_first_free();

    if (idx == -1) {
        return NULL;
    }

    pmm_set_frame(idx);

    return (void*) (idx * PMM_BLOCK_SIZE);
}
