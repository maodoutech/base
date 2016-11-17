// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#include "find_cstr.h"

namespace base {

__thread StringMapThreadLocalTemp tls_stringmap_temp = { false, {} };

}  // namespace base
