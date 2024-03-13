#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP
#include "../eds_util.hpp" 
#include "resource.hpp"
#include "delegate_resource_manager.hpp"
EDS_BEGIN_NAMESPACE
struct SubscriberBase {
    
        virtual bool equals(const SubscriberBase &other) const noexcept = 0;
        virtual size_t id() const noexcept = 0;
        SubscriberBase() = default;
        virtual Resource &get_delegate() const noexcept = 0;
        virtual void set_delegate(Resource *) noexcept = 0;
        constexpr SubscriberBase(const SubscriberBase &) noexcept = default;
        constexpr SubscriberBase(SubscriberBase &&) noexcept = default;
        constexpr SubscriberBase &operator=(const SubscriberBase &) noexcept = default;
        constexpr SubscriberBase &operator=(SubscriberBase &&) noexcept = default;
        virtual ~SubscriberBase() = default;

};
template <class... PARMS> struct Subscriber : public SubscriberBase {
        virtual void operator()(PARMS... args) noexcept = 0;
        virtual void invoke(PARMS... args) noexcept = 0;
        virtual ~Subscriber() noexcept = default;
};
template <> struct Subscriber<> : public SubscriberBase {
        virtual void operator()() noexcept = 0;
        virtual void invoke() noexcept = 0;
        virtual ~Subscriber() noexcept = default;
};
EDS_END_NAMESPACE
#endif
