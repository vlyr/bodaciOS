#pragma once
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
char* strcpy(const char* src, char* dst);
char* strcat(char* s1, const char* s2);
char* strncat(char* dest, const char* src, size_t sz);
char* fmt_int(long long i, char* s, int base);

// Set `size` bytes at `addr` to `byte`
void* memset(void* addr, uint8_t byte, size_t size);

// Copy `size` bytes from `src` to `dest`
void* memcpy(void* dest, const void* src, size_t size);
