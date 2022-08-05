#include "../include/string.h"
#include <stddef.h>

char* strcpy(const char* src, char* dest) {
    char* tmp = dest;

    while ((*dest++ = *src++))
        ;

    return tmp;
};

size_t strlen(const char* str) {
    size_t len = 0;

    while (str[len])
        len++;

    return len;
}
