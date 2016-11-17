// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#ifndef BASE_THREADING_THREAD_LOCAL_INL_H
#define BASE_THREADING_THREAD_LOCAL_INL_H

namespace base {

namespace detail {

template <typename T>
class ThreadLocalHelper {
public:
    inline static T* get() {
        if (__builtin_expect(value != NULL, 1)) {
            return value;
        }
        value = new (std::nothrow) T;
        if (value != NULL) {
            base::thread_atexit(delete_object<T>, value);
        }
        return value;
    }
    static THREAD_LOCAL T* value;
};

template <typename T> THREAD_LOCAL T* ThreadLocalHelper<T>::value = NULL;

}  // namespace detail

template <typename T> inline T* get_thread_local() {
    return detail::ThreadLocalHelper<T>::get();
}

}  // namespace base

#endif  // BASE_THREADING_THREAD_LOCAL_INL_H
