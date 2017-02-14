// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#ifndef BASE_COMMON_MD5_H_
#define BASE_COMMON_MD5_H_

#include "string_piece.h"

namespace base {

// MD5 stands for Message Digest algorithm 5.
// MD5 is a robust hash function, designed for cyptography, but often used
// for file checksums.  The code is complex and slow, but has few
// collisions.
// See Also:
//   http://en.wikipedia.org/wiki/MD5

// These functions perform MD5 operations. The simplest call is MD5Sum() to
// generate the MD5 sum of the given data.
//
// You can also compute the MD5 sum of data incrementally by making multiple
// calls to MD5Update():
//   MD5Context ctx; // intermediate MD5 data: do not use
//   MD5Init(&ctx);
//   MD5Update(&ctx, data1, length1);
//   MD5Update(&ctx, data2, length2);
//   ...
//
//   MD5Digest digest; // the result of the computation
//   MD5Final(&digest, &ctx);
//
// You can call MD5DigestToBase16() to generate a string of the digest.

// The output of an MD5 operation.
struct MD5Digest {
  unsigned char a[16];
};

// Used for storing intermediate data during an MD5 computation. Callers
// should not access the data.
typedef char MD5Context[88];

// Computes the MD5 sum of the given data buffer with the given length.
// The given 'digest' structure will be filled with the result data.
void MD5Sum(const void* data, size_t length, MD5Digest* digest);

// Initializes the given MD5 context structure for subsequent calls to
// MD5Update().
void MD5Init(MD5Context* context);

// For the given buffer of |data| as a StringPiece, updates the given MD5
// context with the sum of the data. You can call this any number of times
// during the computation, except that MD5Init() must have been called first.
void MD5Update(MD5Context* context, const StringPiece& data);

// Finalizes the MD5 operation and fills the buffer with the digest.
void MD5Final(MD5Digest* digest, MD5Context* context);

// MD5IntermediateFinal() generates a digest without finalizing the MD5
// operation.  Can be used to generate digests for the input seen thus far,
// without affecting the digest generated for the entire input.
void MD5IntermediateFinal(MD5Digest* digest,
                                      const MD5Context* context);

// Converts a digest into human-readable hexadecimal.
std::string MD5DigestToBase16(const MD5Digest& digest);

// Returns the MD5 (in hexadecimal) of a string.
std::string MD5String(const StringPiece& str);

}  // namespace base

#endif  // BASE_COMMON_MD5_H_
