#include "../include/string.h"
#include <stddef.h>

int strlen(const char* str) {
    size_t len = 0;

    while(str[len])
	len++;

    return len;
}
