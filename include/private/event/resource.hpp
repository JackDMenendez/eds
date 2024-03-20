#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include "../eds_util.hpp"
EDS_BEGIN_NAMESPACE
struct Resource {
     constexpr Resource() noexcept = default;
     constexpr Resource(const Resource &) noexcept = default;
     constexpr Resource(Resource &&) noexcept = default;
     constexpr Resource &operator=(const Resource &) noexcept = default;
     constexpr Resource &operator=(Resource &&) noexcept = default;
     virtual size_t get_subscriber_id() const noexcept = 0;
     virtual long get_use_count() const noexcept = 0;
     virtual bool equals(const Resource &other) const noexcept = 0;
     virtual ~Resource() noexcept = default;
};
EDS_END_NAMESPACE
#endif // EDC_RSRC_H
