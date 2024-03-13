#ifndef EDS_ENV_HPP
#define EDS_ENV_HPP
#include <cstddef>
#if defined(__MINGW32__)
#define EDS_MINGW_OS
#elif defined(_WIN32)
#define EDS_WIN_OS
#elif defined(unix) || defined(__unix__) || defined(__unix)
#define EDS_UNIX_OS
#elif defined(__APPLE__) || defined(__MACH__)
#define EDS_MAC_OS
#elif defined(__FreeBSD__)
#define EDS_FREE_BSD_OS
#elif defined(__ANDROID__)
#define EDS_ANDROID_OS
#endif

#if defined(__clang__)
#define EDS_CLANG_COMPILER
#elif defined(__GNUC__) || defined(__GNUG__)
#define EDS_GCC_COMPILER
#elif defined(_MSC_VER)
#define EDS_MSVC_COMPILER
#endif
#ifndef Compiler_Specifics
#ifndef EDS_COMPILER_VERSION
#if __cplusplus == 199711L
#define EDS_COMPILER_VERSION _MSVC_LANG
#else
#define EDS_COMPILER_VERSION __cplusplus
#endif
#endif
#ifndef EDS_CXX17
#if EDS_COMPILER_VERSION > 201402L
#define EDS_CXX17 1
#else
#define EDS_CXX17 0
#endif
#endif // EDS_CXX17
#ifndef EDS_CXX20
#if EDS_CXX17 && EDS_COMPILER_VERSION > 201703L
#define EDS_CXX20 1
#else
#define EDS_CXX20 0
#endif
#endif // EDS_CXX20
#ifndef EDS_CXX23
#if EDS_CXX20 && EDS_COMPILER_VERSION > 202002L
#define EDS_CXX23 1
#else
#define EDS_CXX23 0
#endif
#endif // EDS_CXX23
static_assert(EDS_CXX20 || EDS_CXX23, "EDC requires Compiler support C++ 20 or higher");
// P2465R3 Standard Library Modules std And std.compat
#endif // Compiler_Specifics
// The following contains the friend macro for the GTest framework
#include "gtest/gtest_prod.h"

#define EDS_NAMESPACE eds
#define EDS ::EDS_NAMESPACE::
#define EDS_BEGIN_NAMESPACE namespace EDS_NAMESPACE {
#define EDS_END_NAMESPACE }
#endif // EDS_ENV_HPP
