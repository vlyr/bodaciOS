#include <mem.h>
#include <stdint.h>
#include <string.h>
#include <common.h>

static uint32_t* map;
static uint32_t map_size;

// Sets bit at index `idx` of `memory_map`
static inline void pmm_set_frame(size_t idx) { *map |= 1 << idx; }

// Unsets bit at index `idx` of `memory_map`
static inline void pmm_unset_frame(size_t idx) { *map &= ~(1 << idx); }

// Returns 0 when the frame at `idx` is unused
static inline int pmm_get_frame(size_t idx) { return (*map & (1 << idx)); }

void pmm_init(uint64_t base_addr, size_t mem_size) {
    map = (uint32_t*) base_addr;
    map_size = mem_size / PMM_BLOCK_SIZE;

    // Check if there are more blocks than how many bits can fit in a u32
    if (map_size % BLOCKS_PER_U32) {
        map_size++;
    }

    memset(map, 0xFF, map_size);

    pmm_unset_frame(0);
}

void* pmm_init_region(uint64_t base_addr, size_t size) {
    size_t blocks = size / PMM_BLOCK_SIZE;
    size_t idx = base_addr / PMM_BLOCK_SIZE;

    for (int i = 0; i < blocks; i++) {
        pmm_unset_frame(idx);
    }

    klog(LOG_MESSAGE_DEBUG, "PMM memory region initialized at %x for %d blocks, memory map = %x\n",
         base_addr, blocks, *map);

    return (void*) base_addr;
}

void pmm_deinit_region(uint64_t base_addr, size_t size) {
    size_t blocks = size / PMM_BLOCK_SIZE;
    size_t idx = base_addr / PMM_BLOCK_SIZE;

    for (int i = 0; i < blocks; i++) {
        pmm_set_frame(idx);
    }
}

void* pmm_alloc_frame(size_t n) {}
