#ifndef EDS_ENV_HPP
#define EDS_ENV_HPP
#include <cstddef>
// The following contains the friend macro for the GTest framework
#include "eds_util.hpp"
#include "gtest/gtest_prod.h"
#if defined(__MINGW32__)
     #define EDS_MINGW_OS
     #define EDS_OS_NAME MINGW32
#elif defined(_WIN32)
     #define EDS_WIN_OS
     #define EDS_OS_NAME WIN32
#elif defined(unix) || defined(__unix__) || defined(__unix)
     #define EDS_UNIX_OS
     #define EDS_OS_NAME UNIX
#elif defined(__APPLE__) || defined(__MACH__)
     #define EDS_MAC_OS
     #define EDS_OS_NAME MACOS
#elif defined(__FreeBSD__)
     #define EDS_FREE_BSD_OS
     #define EDS_OS_NAME FREEBSD
#elif defined(__ANDROID__)
     #define EDS_ANDROID_OS
     #define EDS_OS_NAME ANDROID
#endif

#if defined(__clang__)
     #define EDS_CLANG_COMPILER 1
     #define EDS_COMPILER_NAME CLANG
     #define EDS_LIBSTD_VERSION __clang_version__
     #define EDS_COMPILER_VERSION __cplusplus
#elif defined(__GNUC__) || defined(__GNUG__)
     #define EDS_GCC_COMPILER
     #define EDS_COMPILER_NAME GCC
     #ifndef EDS_LIBSTD_VERSION
          #ifdef __GLIBCPP__
               #define EDS_LIBSTD_VERSION __GLIBCPP__
          #elif defined __GLIBCXX__
               #define EDS_LIBSTD_VERSION __GLIBCXX__
          #endif
     #endif
#elif defined(__INTEL_COMPILER)
     #define EDS_INTEL_COMPILER
     #define EDS_COMPILER_NAME INTEL
#elif defined(_MSC_VER)
     #define EDS_MSVC_COMPILER __cplusplus
     #define EDS_COMPILER_NAME MSVC
     #ifndef EDS_LIBSTD_VERSION
          // _CPPLIB_VER       650
          // _MSVC_STL_VERSION 143
          // _MSVC_STL_UPDATE  202310L
          #define EDS_LIBSTD_VERSION _MSC_VER
     #endif
#endif
#ifndef EDS_COMPILER_VERSION
     #if EDS_MSVC_COMPILER == 199711L
          #define EDS_COMPILER_VERSION _MSVC_LANG
     #else
          #define EDS_COMPILER_VERSION __cplusplus
     #endif
#endif
#define EDS_ENV_VERSION_MESSAGE(F,L)                                                          \
EDS_INFORMATION(F,L,EDS_2002(EDS_OS_NAME, EDS_COMPILER_NAME, EDS_COMPILER_VERSION,      \
                                   EDS_LIBSTD_VERSION))
#pragma message(EDS_ENV_VERSION_MESSAGE(__FILE__, __LINE__))
#ifndef EDS_COMPILER_SPECIFICS
     #define EDS_COMPILER_SPECIFICS 1
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
          #if defined(EDS_CLANG_COMPILER)
               #ifndef P1169R4
                    /** 
                     * Standard Library Modules std And std.compat static operator() compiler
                     * version 16 
                     */
                    #define P1169R4 1
               #endif
               /** No support for Move only version of std::function */
               #define EDS_LAMBDA_NOEXCEPT
          #elif defined(EDS_GCC_COMPILER)
               #ifndef P0288R9
                    /** Supports Move only version of std::function Compiler version 12 */
                    #define P0288R9 1
               #endif
               #ifndef P1169R4
                    /** Standard Library Modules std And std.compat static operator() Compiler
                     * version 13
                     */
                    #define P1169R4 1
               #endif
          #elif defined(EDS_INTEL_COMPILER)
               #ifndef P1169R4
                    /** Standard Library Modules std And std.compat static operator() */
                    #define P1169R4 1
               #endif
          #elif defined(EDS_MSVC_COMPILER)
               #if EDS_LIBSTD_VERSION > 1931
                    #if EDS_COMPILER_VERSION > 202003L
                         #ifndef P0288R9
                              /**
                               * Supports Move only version of std::function _MSC_VER 19.32
                               * and compiler version 20204 or greater.
                               */
                              #define P0288R9 1
                         #endif
                    #endif
               #endif
          #endif
     #endif // EDS_CXX23
     #ifdef P0288R9
          #define EDS_CONSERVATIVE_FUNCTION std::move_only_function
     #else
          #define EDS_CONSERVATIVE_FUNCTION std::function
     #endif
     #ifndef EDS_LAMBDA_NOEXCEPT
          #define EDS_LAMBDA_NOEXCEPT noexcept
     #endif
     static_assert(EDS_CXX20 || EDS_CXX23, "EDC requires Compiler support C++ 20 or higher");
// P2465R3 Standard Library Modules std And std.compat
#endif // Compiler_Specifics

#define EDS_NAMESPACE eds
#define EDS ::EDS_NAMESPACE::
#define EDS_BEGIN_NAMESPACE namespace EDS_NAMESPACE {
#define EDS_END_NAMESPACE }
/**
 * @brief Define NDUMPTRS as preprocessor macro at build time to eliminate passing of dumb
 * pointer when they have scope.
 * @anchor NDUMBPTRS
 */
#ifdef NDUMBPTRS
     #define EDS_NDUMBPTRS NDUMBPTRS
#endif // NDUMBPTRS
#endif // EDS_ENV_HPP
