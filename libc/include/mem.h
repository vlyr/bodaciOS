#pragma once

#include <stddef.h>
#include <stdint.h>

void* memset(void* addr, uint8_t byte, size_t size);
void* memcpy(void* dest, const void* src, size_t size);
