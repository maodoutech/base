// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#ifndef BASE_STRINGS_STRING_SPLITTER_H
#define BASE_STRINGS_STRING_SPLITTER_H

#include <stdlib.h>
#include <stdint.h>

// It's common to encode data into strings separated by special characters
// and decode them back, but functions such as `split_string' has to modify
// the input string, which is bad. If we parse the string from scratch, the
// code will be filled with pointer operations and obscure to understand.
//
// What we want is:
// - Scan the string once: just do simple things efficiently.
// - Do not modify input string: Changing input is bad, it may bring hidden
//   bugs, concurrency issues and non-const propagations.
// - Split the string in-place without additional buffer/array.

namespace base {

enum EmptyFieldAction {
    SKIP_EMPTY_FIELD,
    ALLOW_EMPTY_FIELD
};

// Split a string with one character
class StringSplitter {
public:
    // Split `input' with `separator'. If `action' is SKIP_EMPTY_FIELD, zero-
    // length() field() will be skipped.
    inline StringSplitter(const char* input, char separator,
                          EmptyFieldAction action = SKIP_EMPTY_FIELD);
    inline StringSplitter(const char* str_begin, const char* str_end,
                          char separator,
                          EmptyFieldAction = SKIP_EMPTY_FIELD);

    // Move splitter forward.
    inline StringSplitter& operator++();
    inline StringSplitter operator++(int);

    // True iff field() is valid.
    inline operator const void*() const;

    // Beginning address and length of the field. *(field() + length()) may
    // not be '\0' because we don't modify `input'.
    inline const char* field() const;
    inline size_t length() const;

    // Cast field to specific type, and write the value into `pv'.
    // Returns 0 on success, -1 otherwise.
    // NOTE: If separator is a digit, casting functions always return -1.
    inline int to_int8(int8_t *pv) const;
    inline int to_uint8(uint8_t *pv) const;
    inline int to_int(int *pv) const;
    inline int to_uint(unsigned int *pv) const;
    inline int to_long(long *pv) const;
    inline int to_ulong(unsigned long *pv) const;
    inline int to_longlong(long long *pv) const;
    inline int to_ulonglong(unsigned long long *pv) const;
    inline int to_float(float *pv) const;
    inline int to_double(double *pv) const;
    
private:
    inline bool not_end(const char* p) const;
    inline void init();
    
    const char* _head;
    const char* _tail;
    const char* _str_tail;
    const char _sep;
    const EmptyFieldAction _empty_field_action;
};

// Split a string with one of the separators
class StringMultiSplitter {
public:
    // Split `input' with one character of `separators'. If `action' is
    // SKIP_EMPTY_FIELD, zero-length() field() will be skipped.
    // NOTE: This utility stores pointer of `separators' directly rather than
    //       copying the content because this utility is intended to be used
    //       in ad-hoc manner where lifetime of `separators' is generally
    //       longer than this utility.
    inline StringMultiSplitter(const char* input, const char* separators,
                               EmptyFieldAction action = SKIP_EMPTY_FIELD);
    inline StringMultiSplitter(const char* str_begin, const char* str_end,
                               const char* separators,
                               EmptyFieldAction action = SKIP_EMPTY_FIELD);

    // Move splitter forward.
    inline StringMultiSplitter& operator++();
    inline StringMultiSplitter operator++(int);

    // True iff field() is valid.
    inline operator const void*() const;

    // Beginning address and length of the field. *(field() + length()) may
    // not be '\0' because we don't modify `input'.
    inline const char* field() const;
    inline size_t length() const;

    // Cast field to specific type, and write the value into `pv'.
    // Returns 0 on success, -1 otherwise.
    // NOTE: If separators contains digit, casting functions always return -1.
    inline int to_int8(int8_t *pv) const;
    inline int to_uint8(uint8_t *pv) const;
    inline int to_int(int *pv) const;
    inline int to_uint(unsigned int *pv) const;
    inline int to_long(long *pv) const;
    inline int to_ulong(unsigned long *pv) const;
    inline int to_longlong(long long *pv) const;
    inline int to_ulonglong(unsigned long long *pv) const;
    inline int to_float(float *pv) const;
    inline int to_double(double *pv) const;

private:
    inline bool is_sep(char c) const;
    inline bool not_end(const char* p) const;
    inline void init();
    
    const char* _head;
    const char* _tail;
    const char* _str_tail;
    const char* const _seps;
    const EmptyFieldAction _empty_field_action;
};

}  // namespace base

#include "string_splitter_inl.h"

#endif  // BASE_STRINGS_STRING_SPLITTER_H
