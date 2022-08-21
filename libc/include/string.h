#include <stddef.h>

size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
char* strcpy(const char* src, char* dst);
char* strcat(char* s1, const char* s2);
char* strncat(char* dest, const char* src, size_t sz);
char* fmt_int(long long i, char* s, int base);
