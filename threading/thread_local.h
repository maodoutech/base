// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)
// 
// Thread-local utilities

#ifndef BASE_THREADING_THREAD_LOCAL_H
#define BASE_THREADING_THREAD_LOCAL_H

#include <new> 
#include <cstddef>

// Provide thread_local keyword (for primitive types) before C++11
// GCC supports thread_local keyword of C++11 since 4.8.0
#if !defined(thread_local) &&                                           \
    (__cplusplus < 201103L ||                                           \
     (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40800)
#define thread_local __thread
#endif

#define THREAD_LOCAL __thread

namespace base {

// Get a thread-local object typed T. The object will be default-constructed
// at the first call to this function, and will be deleted when thread exits.
template <typename T> 
T* get_thread_local();

int thread_atexit(void (*fn)());
int thread_atexit(void (*fn)(void*), void* arg);
void thread_atexit_cancel(void (*fn)());
void thread_atexit_cancel(void (*fn)(void*), void* arg);

// Delete the typed-T object whose address is `arg'.
template <typename T> void delete_object(void* arg) {
    delete static_cast<T*>(arg);
}

}  // namespace base

#include "thread_local_inl.h"

#endif  // BASE_THREADING_THREAD_LOCAL_H
