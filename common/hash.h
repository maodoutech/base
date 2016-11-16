// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#ifndef BASE_COMMON_HASH_H_
#define BASE_COMMON_HASH_H_

#include <limits>
#include <string>

namespace base {

// WARNING: This hash function should not be used for any cryptographic purpose.
uint32_t SuperFastHash(const char* data, int len);

inline uint32_t Hash(const char* data, size_t length) {
  if (length > static_cast<size_t>(std::numeric_limits<int>::max())) {
    return 0;
  }
  return SuperFastHash(data, static_cast<int>(length));
}

inline uint32_t Hash(const std::string& str) {
  return Hash(str.data(), str.size());
}

}  // namespace base

#endif  // BASE_COMMON_HASH_H_
