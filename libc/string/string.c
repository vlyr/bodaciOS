#include "../include/string.h"
#include <stddef.h>

char* strcpy(const char* src, char* dest) {
    if (src == NULL || dest == NULL)
        return NULL;

    char* tmp = dest;

    while ((*dest++ = *src++))
        ;

    return tmp;
};

size_t strlen(const char* str) {
    if (str == NULL)
        return 0;

    size_t len = 0;

    while (str[len])
        len++;

    return len;
}

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
void strrev(char* arr, int start, int end) {
    char temp;

    if (start >= end)
        return;

    temp = *(arr + start);
    *(arr + start) = *(arr + end);
    *(arr + end) = temp;

    start++;
    end--;
    strrev(arr, start, end);
}

char* fmt_int(int number, char* arr, int base) {
    int i = 0, r, negative = 0;

    if (number == 0) {
        arr[i] = '0';
        arr[i + 1] = '\0';
        return arr;
    }

    if (number < 0 && base == 10) {
        number *= -1;
        negative = 1;
    }

    while (number != 0) {
        r = number % base;
        arr[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
        i++;
        number /= base;
    }

    if (negative) {
        arr[i] = '-';
        i++;
    }

    strrev(arr, 0, i - 1);

    arr[i] = '\0';

    return arr;
}

