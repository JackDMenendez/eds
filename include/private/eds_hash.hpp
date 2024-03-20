#ifndef EDS_HASH_H
#define EDS_HASH_H
#include "eds_env.hpp"
#include <algorithm>
EDS_BEGIN_NAMESPACE
/// @todo validate this hash function, it doesn't look right
constexpr inline size_t hash64shift(size_t _key_) {
     _key_ = (~_key_) + (_key_ << 21);
     _key_ = _key_ ^ (_key_ >> 24);
     _key_ = (_key_ + (_key_ << 3)) + (_key_ << 8);
     _key_ = _key_ ^ (_key_ >> 14);
     _key_ = (_key_ + (_key_ << 2)) + (_key_ << 4);
     _key_ = _key_ ^ (_key_ >> 28);
     return _key_;
}
constexpr inline size_t hash2upper(size_t _key_) {
     _key_ = _key_ + (_key_ << 31);
     _key_ = 0xffffffff00000000 & _key_;
     return _key_;
}

constexpr inline size_t hash2lower(size_t _key_) {
     _key_ = _key_ + (_key_ >> 31);
     _key_ = 0x00000000ffffffff & _key_;
     return _key_;
}
constexpr size_t hash_to_64_bits(size_t value1, size_t value2) {
     return hash64shift(hash2upper(value1) | hash2lower(value2));
}
EDS_END_NAMESPACE
#endif
