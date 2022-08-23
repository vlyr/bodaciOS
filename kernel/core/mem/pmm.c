#include <mem.h>
#include <string.h>

#include <stdint.h>
#include <common.h>

static size_t MAP_LEN;

static uint8_t* pmm_map;

void pmm_init(void* base_address, size_t memory_size) {
    pmm_map = (uint8_t*) base_address;

    MAP_LEN = memory_size / PMM_BLOCK_SIZE;

    memset(pmm_map, (uint8_t) 0xFFFF, MAP_LEN);

    klog(LOG_MESSAGE_DEBUG, "initializing PMM | map = %d at %x", *pmm_map, pmm_map);
}
