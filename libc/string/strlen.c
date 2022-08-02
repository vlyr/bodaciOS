#include "../include/string.h"

int strlen(const char* str) {
    usize len;

    while(str[len])
	len++;

    return len;
}
