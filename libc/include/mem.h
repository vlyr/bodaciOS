#pragma once

#include <stddef.h>
#include <stdint.h>

// Set `size` bytes at `addr` to `byte`
void* memset(void* addr, uint8_t byte, size_t size);

// Copy `size` bytes from `src` to `dest`
void* memcpy(void* dest, const void* src, size_t size);
