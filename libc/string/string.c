#include "../include/string.h"
#include <stdint.h>
#include <stddef.h>

// Copy the contents of `src` to `dest`
char* strcpy(const char* src, char* dest) {
    if (src == NULL || dest == NULL)
        return NULL;

    char* tmp = dest;

    while ((*dest++ = *src++))
        ;

    return tmp;
};

// Return the length of `str`
size_t strlen(const char* str) {
    if (str == NULL)
        return 0;

    size_t len = 0;

    while (str[len])
        len++;

    return len;
}

// Concatenate `s2` to `s1`
char* strcat(char* s1, const char* s2) {
    if (s1 == NULL || s2 == NULL)
        return NULL;

    char* start = s1;

    while (*start != '\0') {
        start++;
    }

    while (*s2 != '\0') {
        *start++ = *s2++;
    }

    *start = '\0';
    return s1;
}

char* strncat(char* dest, const char* src, size_t sz) {
    char* ptr = dest + strlen(dest);

    while (*src != '\0' && sz--) {
        *ptr++ = *src++;
    }

    *ptr = '\0';

    return dest;
}

// https://www.codevscolor.com/c-itoa-function
// Reverse a string.
void strrev(char* buffer, int start, int end) {
    char temp;

    if (start >= end)
        return;

    temp = *(buffer + start);
    *(buffer + start) = *(buffer + end);
    *(buffer + end) = temp;

    start++;
    end--;
    strrev(buffer, start, end);
}

int strcmp(const char* s1, const char* s2) {
    size_t idx = 0;

    if (strlen(s2) > strlen(s1)) {
        while (s1[idx]) {
            if (s1[idx] != s2[idx]) {
                return 1;
            }
            idx++;
        }

        return 0;
    } else {
        while (s2[idx]) {
            if (s1[idx] != s2[idx]) {
                return 1;
            }
            idx++;
        }

        return 0;
    }
}

// Equivalent of `itoa` in the standard C library - convert an integer with a base of `base` to a
// string and put the result in `buffer`.
char* fmt_int(long long number, char* buffer, int base) {
    int i = 0, r, negative = 0;

    if (number == 0) {
        buffer[i] = '0';
        buffer[i + 1] = '\0';
        return buffer;
    }

    if (number < 0 && base == 10) {
        number *= -1;
        negative = 1;
    }

    while (number != 0) {
        r = number % base;
        buffer[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
        i++;
        number /= base;
    }

    if (negative) {
        buffer[i] = '-';
        i++;
    }

    strrev(buffer, 0, i - 1);

    buffer[i] = '\0';

    return buffer;
}

void* memset(void* addr, uint8_t byte, size_t size) {
    uint8_t* ptr = addr;

    for (size_t i = 0; i < size; i++) {
        ptr[i] = byte;
    }

    return addr;
}

void* memcpy(void* dest, const void* src, size_t size) {
    uint8_t* dp = dest;
    const uint8_t* sp = src;

    while (size--) {
        *dp++ = *sp++;
    }

    return dest;
}
