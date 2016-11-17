// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)
//
// This file defines some bit utilities.

#ifndef BASE_STRING_BITS_H_
#define BASE_STRING_BITS_H_

#include "common/basictypes.h"

namespace base {
namespace bits {

// Returns the integer i such as 2^i <= n < 2^(i+1)
inline int Log2Floor(uint32_t n) {
  if (n == 0) {
    return -1;
  }

  int log = 0;
  uint32_t value = n;
  for (int i = 4; i >= 0; --i) {
    int shift = (1 << i);
    uint32_t x = value >> shift;
    if (x != 0) {
      value = x;
      log += shift;
    }
  }

  return log;
}

// Returns the integer i such as 2^(i-1) < n <= 2^i
inline int Log2Ceiling(uint32_t n) {
  if (n == 0) {
    return -1;
  } else {
    // Log2Floor returns -1 for 0, so the following works correctly for n=1.
    return 1 + Log2Floor(n - 1);
  }
}

}  // namespace bits
}  // namespace base

#endif  // BASE_STRING_BITS_H_
