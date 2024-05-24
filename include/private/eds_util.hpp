#ifndef EDS_UTIL_HPP
#define EDS_UTIL_HPP
#ifndef EDS_STRINGIFY
#define EDS_STRINGIFY(s) #s
#define EDS_TOSTRING(s) EDS_STRINGIFY(s)
#endif
#ifndef EDS_CONCAT
#define EDS_CONCATINATE(a, b) a##b
#define EDS_CONCAT(LHS, RHS) EDS_CONCATINATE(LHS, RHS)
#endif
#ifndef EDS_UNUSEDPARAM
     #define EDS_UNUSEDPARAM(param) (void)param
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
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOCATION__(F,L) F "(" __STR1__(L) ") :"
#define __WARNING__(F,L,...) __LOCATION__(F,L) "Warning Msg : " __VA_ARGS__
#define __INFORMATION__(F,L,...) __LOCATION__(F,L) "Info Msg: " __VA_ARGS__
#define __ERROR__(F,L,...) __LOCATION__(F,L) "Error Msg: " __VA_ARGS__
#define __FATAL__(F,L,...) __LOCATION__(F,L) "Fatal Msg: " __VA_ARGS__
#define __ASSERT__(F,L,...) __LOCATION__(F,L) "Assert Msg: " __VA_ARGS__
// Message Macros
#define EDS_WARNING(F,L,...) __WARNING__(F,L,__VA_ARGS__)
#define EDS_INFORMATION(F,L,...) __INFORMATION__(F,L,__VA_ARGS__)
#define EDS_ERROR(F,L,...) __ERROR__(F,L,__VA_ARGS__)
#define EDS_FATAL(F,L,...) __FATAL__(F,L,__VA_ARGS__)
#define EDS_ASSERT(F,L,...) __ASSERT__(F,L,__VA_ARGS__)
// Messages
#define EDS_1001(TYPE, PARAM) "EDS 1001 W Prefer smart pointer for " EDS_TOSTRING(TYPE) " param " EDS_TOSTRING(PARAM)
#define EDS_2001(TYPE, PARAM) "EDS 2001 E Pass class " EDS_TOSTRING(TYPE) " as reference instead of pointer param " EDS_TOSTRING(PARAM)
#define EDS_2002(_OS, _COMPILER, _COMPILER_VERSION,_LIBSTD_VERSION)                                              \
     "EDS 2002 I OS: " EDS_TOSTRING(_OS) " COMPILER: " EDS_TOSTRING(_COMPILER) \
" COMPILER VERSION: " EDS_TOSTRING(_COMPILER_VERSION) " STD LIB VERSION: " EDS_TOSTRING(_LIBSTD_VERSION)
#include "eds_env.hpp"
#endif 
