#ifndef EDS_UTIL_HPP
#define EDS_UTIL_HPP
#include "eds_env.hpp"
EDS_BEGIN_NAMESPACE
#ifndef EDS_STRINGIFY
#define EDS_STRINGIFY(s) #s
#define EDS_TOSTRING(s) EDS_STRINGIFY(s)
#endif
#ifndef EDS_CONCAT
#define EDS_CONCATINATE(a, b) a##b
#define EDS_CONCAT(LHS, RHS) EDS_CONCATINATE(LHS, RHS)
#endif
#ifndef EDS_EOL
/// End of line character, the character literal is efficient that a string literal, std::endl
/// also does a flush.
#define EDS_EOL() '\n'
#endif
#ifndef EDS_NORETURN
// lets give Intellisense something to chew on.
#define EDS_NORETURN
#endif // EDS_NORETURN
EDS_END_NAMESPACE
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOCATION__ __FILE__ "("__STR1__(__LINE__) ") :"
#define __WARNING__(message) __LOCATION__ "Warning Msg : " message
#define __INFORMATION__(message) __LOCATION__ "Info Msg: " message
#define __ERROR__(message) __LOCATION__ "Error Msg: " message
#define __FATAL__(message) __LOCATION__ "Fatal Msg: " message
#define __ASSERT__(message) __LOCATION__ "Assert Msg: " message
// Message Macros
#define EDS_WARNING(message) __WARNING__(message)
#define EDS_INFORMATION(message) __INFORMATION__(message)
#define EDS_ERROR(message) __ERROR__(message)
#define EDS_FATAL(message) __FATAL__(message)
#define EDS_ASSERT(message) __ASSERT__(message)
// Messages
#define EDS_1001(TYPE, PARAM) "EDS 1001 W Prefer smart pointer for " EDS_TOSTRING(TYPE) " param " EDS_TOSTRING(PARAM)
#define EDS_2001(TYPE, PARAM) "EDS 2001 E Pass class " EDS_TOSTRING(TYPE) " as reference instead of pointer param " EDS_TOSTRING(PARAM)
#endif
