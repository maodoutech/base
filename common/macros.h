// Copyright (c) 2016 Maodou.tech, Inc. All Rights Reserved
// Author: Zhang Shilong (jack_zsl@163.com)

#ifndef BASE_COMMON_MACROS_H_
#define BASE_COMMON_MACROS_H_

#include <stddef.h>  // For size_t.
#include <string.h>  // For memcpy.

// There must be many copy-paste versions of these macros which are same
// things, undefine them to avoid conflict.
#undef DISALLOW_COPY
#undef DISALLOW_ASSIGN
#undef DISALLOW_COPY_AND_ASSIGN
#undef DISALLOW_IMPLICIT_CONSTRUCTORS

#if __cplusplus < 201103L  // before c++ 11
// Put this in the private: declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
  TypeName(const TypeName&)

// Put this in the private: declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) \
  void operator=(const TypeName&)

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                    \
  DISALLOW_COPY_AND_ASSIGN(TypeName)

#else  // __cplusplus >= 201103L

#define DISALLOW_COPY(TypeName) \
  TypeName(const TypeName&) = delete

#define DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;     \
  void operator=(const TypeName&) = delete

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                           \
  DISALLOW_COPY_AND_ASSIGN(TypeName)
#endif  // __cplusplus

// Concatenate numbers in c/c++ macros.
#ifndef CONCAT
# define CONCAT(a, b) CONCAT_HELPER(a, b)
# define CONCAT_HELPER(a, b) a##b
#endif

#undef arraysize
// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.  In these rare
// cases, you have to use the unsafe ARRAYSIZE_UNSAFE() macro below.  This is
// due to a limitation in C++'s template system.  The limitation might
// eventually be removed, but it hasn't happened yet.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.    
namespace base {
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
}

namespace base {
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
}

#define arraysize(array) (sizeof(::base::ArraySizeHelper(array)))

// Use implicit_cast as a safe version of static_cast or const_cast
// for upcasting in the type hierarchy (i.e. casting a pointer to Foo
// to a pointer to SuperclassOfFoo or casting a pointer to Foo to
// a const pointer to Foo).
// When you use implicit_cast, the compiler checks that the cast is safe.
// Such explicit implicit_casts are necessary in surprisingly many
// situations where C++ demands an exact type match instead of an
// argument type convertible to a target type.
//
// The From type can be inferred, so the preferred syntax for using
// implicit_cast is the same as for static_cast etc.:
//
//   implicit_cast<ToType>(expr)
//
// implicit_cast would have been part of the C++ standard library,
// but the proposal was submitted too late.  It will probably make
// its way into the language in the future.
namespace base {
template<typename To, typename From>
inline To implicit_cast(From const &f) {
  return f;
}
}

#if __cplusplus >= 201103L

// C++11 supports compile-time assertion directly
#define CASSERT(expr, msg) static_assert(expr, #msg)

#else

// Assert constant boolean expressions at compile-time
// Params:
//   expr     the constant expression to be checked
//   msg      an error infomation conforming name conventions of C/C++
//            variables(alphabets/numbers/underscores, no blanks). For
//            example "cannot_accept_a_number_bigger_than_128" is valid
//            while "this number is out-of-range" is illegal.
//
// when an asssertion like "CASSERT(false, you_should_not_be_here)"
// breaks, a compilation error is printed:
//   
//   foo.cpp:401: error: enumerator value for `you_should_not_be_here___19' not
//   integer constant
//
// You can call CASSERT at global scope, inside a class or a function
// 
//   CASSERT(false, you_should_not_be_here);
//   int main () { ... }
//
//   struct Foo {
//       CASSERT(1 == 0, Never_equals);
//   };
//
//   int bar(...)
//   {
//       CASSERT (value < 10, invalid_value);
//   }
//
namespace base {
template <bool> struct CAssert { static const int x = 1; };
template <> struct CAssert<false> { static const char * x; };
}

#define CASSERT(expr, msg)                                \
    enum { CONCAT(CONCAT(LINE_, __LINE__), __##msg) \
           = ::base::CAssert<!!(expr)>::x };

#endif  // __cplusplus

// Used to explicitly mark the return value of a function as unused. If you are
// really sure you don't want to do anything with the return value of a function
// that has been marked WARN_UNUSED_RESULT, wrap it with this. Example:
//
//   scoped_ptr<MyType> my_var = ...;
//   if (TakeOwnership(my_var.get()) == SUCCESS)
//     ignore_result(my_var.release());
//
namespace base {
template<typename T>
inline void ignore_result(const T&) {
}
} // base

// Convert symbol to string
#ifndef SYMBOLSTR
# define SYMBOLSTR(a) SYMBOLSTR_HELPER(a)
# define SYMBOLSTR_HELPER(a) #a
#endif

#ifndef TYPEOF
# if __cplusplus >= 201103L
#  define TYPEOF decltype
# else
#   define TYPEOF typeof
# endif  // __cplusplus >= 201103L
#endif  // TYPEOF

#if defined(__cplusplus)
namespace base {
template <typename T> struct ArrayDeleter {  
    ArrayDeleter() : arr(0) {}
    ~ArrayDeleter() { delete[] arr; }
    T* arr;
};
}
#endif

// Put following code somewhere global to run it before main():
// 
//   GLOBAL_INIT()
//   {
//       ... your code ...
//   }
//
// Your can:
//   * Write any code and access global variables.
//   * Use ASSERT_*.
//   * Have multiple GLOBAL_INIT() in one scope.
// 
// Since the code run in global scope, quit with exit() or similar functions.

#if defined(__cplusplus)
# define GLOBAL_INIT                                      \
namespace {  /*anonymous namespace */                           \
    struct CONCAT(GlobalInit, __LINE__) {            \
        CONCAT(GlobalInit, __LINE__)() { init(); }   \
        void init();                                            \
    } CONCAT(baidu_global_init_dummy_, __LINE__);         \
}  /* anonymous namespace */                                    \
    void CONCAT(GlobalInit, __LINE__)::init              
#else
# define GLOBAL_INIT                      \
    static void __attribute__((constructor))    \
    CONCAT(global_init_, __LINE__)

#endif  // __cplusplus

#endif  // BASE_MACROS_H_
