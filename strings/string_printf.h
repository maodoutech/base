// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)
//
// Utilities to format string. Internal using vsnprintf with
// optimization

#ifndef BASE_STRINGS_STRING_PRINTF_H
#define BASE_STRINGS_STRING_PRINTF_H

#include <string>                                // std::string
#include <stdarg.h>                              // va_list

namespace base {

std::string string_printf(const char* format, ...)
    __attribute__ ((format (printf, 1, 2)));

int string_printf(std::string* output, const char* fmt, ...)
    __attribute__ ((format (printf, 2, 3)));

int string_vprintf(std::string* output, const char* format, va_list args);

int string_appendf(std::string* output, const char* format, ...)
    __attribute__ ((format (printf, 2, 3)));

int string_vappendf(std::string* output, const char* format, va_list args);

}  // namespace base

#endif  // BASE_STRINGS_STRING_PRINTF_H
