#include <mem.h>
#include <stdint.h>
#include <string.h>
#include <common.h>

static uint32_t* map;
static uint32_t map_size;

// Sets bit at index `idx` of `memory_map`
static inline void set_frame(size_t idx) { *map |= 1 << idx; }

// Unsets bit at index `idx` of `memory_map`
static inline void unset_frame(size_t idx) { *map &= ~(1 << idx); }

void pmm_init(uint64_t base_addr, size_t mem_size) {
    map = (uint32_t*) base_addr;
    map_size = mem_size / PMM_BLOCK_SIZE;

    if (map_size % BLOCKS_PER_U32) {
        map_size++;
    }

    memset(map, 0x00, map_size);
}

void* pmm_alloc_frame(size_t n) {}
