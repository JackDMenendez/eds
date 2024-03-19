#ifndef DELEGATE_RESOURCE_MANAGER_HPP
#define DELEGATE_RESOURCE_MANAGER_HPP
#include "../eds_util.hpp"
#include "resource.hpp"
EDS_BEGIN_NAMESPACE
template <class... PARMS> 
struct DelegateResourceManager: public Resource {
        constexpr DelegateResourceManager() noexcept = default;
        constexpr DelegateResourceManager(const DelegateResourceManager &) noexcept = default;
        constexpr DelegateResourceManager(DelegateResourceManager &&) noexcept = default;
        constexpr DelegateResourceManager &operator=(const DelegateResourceManager &) noexcept = default;
        constexpr DelegateResourceManager &operator=(DelegateResourceManager &&) noexcept = default;
        virtual void invoke(PARMS...) noexcept = 0;
        virtual void operator()(PARMS...) noexcept = 0;
        virtual ~DelegateResourceManager() noexcept = default;
};
template <> 
struct DelegateResourceManager<> : public Resource {
        constexpr DelegateResourceManager() noexcept = default;
        constexpr DelegateResourceManager(const DelegateResourceManager &) noexcept = default;
        constexpr DelegateResourceManager(DelegateResourceManager &&) noexcept = default;
        constexpr DelegateResourceManager &operator=(const DelegateResourceManager &) noexcept = default;
        constexpr DelegateResourceManager &operator=(DelegateResourceManager &&) noexcept = default;
        virtual void invoke() noexcept = 0;
        virtual void operator()() noexcept = 0;
        virtual ~DelegateResourceManager() noexcept override = default;
};
EDS_END_NAMESPACE
#endif
