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
/// End of line character, the character literal is efficient that a string literal, std::endl also
/// does a flush.
#define EDS_EOL() '\n'
#endif
EDS_END_NAMESPACE
#endif
