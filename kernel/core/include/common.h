#pragma once

#include <stdint.h>
#include <stddef.h>

enum log_message_type {
    LOG_MESSAGE_DEBUG,
    LOG_MESSAGE_WARN,
    LOG_MESSAGE_ERROR,
};

__attribute__((noreturn)) void panic(const char* message);

void klog(enum log_message_type type, const char* msg, ...);
