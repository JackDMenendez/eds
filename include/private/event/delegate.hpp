#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include "call_handler.hpp"
#include "subscriber.hpp"
#include <memory>
EDS_BEGIN_NAMESPACE
template <class... SIGNATURE> class Delegate;
template <class... PARMS>
class Delegate<void(PARMS...) noexcept>
    : public DelegateResourceManager<PARMS...> {
public:
  using Signature = void(PARMS...) noexcept;
  using SubscriberType = Subscriber<PARMS...>;
  using ResourceManagerType = DelegateResourceManager<PARMS...>;
  using local_shared_ptr_t = std::shared_ptr<SubscriberType>;
  local_shared_ptr_t m_managed_CallHandler;
  constexpr Delegate() noexcept = default;
  constexpr Delegate(void (*callback)(PARMS...) noexcept) noexcept
      : m_managed_CallHandler(
            std::make_shared<CallHandler<FunctionPointer, PARMS...>>(callback,
                                                                     this)) {}
  template <class CALLBACK>
  constexpr Delegate(CALLBACK &&callback) noexcept
      : m_managed_CallHandler(
            std::make_shared<CallHandler<FunctionPointer, PARMS...>>(
                std::forward<CALLBACK>(callback), this)) {}
  constexpr Delegate(const Delegate &delegate) noexcept
      : Delegate(delegate.m_managed_CallHandler) {}
  constexpr Delegate(Delegate &&delegate) noexcept
      : m_managed_CallHandler(std::move(delegate.m_managed_CallHandler)) {}
  bool equals(const Resource &other) const noexcept override {
    return get_subscriber_id() == other.get_subscriber_id();
  }
  constexpr Delegate &operator=(const Delegate &delegate) {
    m_managed_CallHandler = delegate.m_managed_CallHandler;
    return *this;
  }
  constexpr Delegate &operator=(const Delegate &&delegate) noexcept {
    m_managed_CallHandler = std::move(delegate.m_managed_CallHandler);
    return *this;
  }
  void invoke(PARMS... args) noexcept override {
    m_managed_CallHandler->invoke(std::forward<PARMS>(args)...);
  }
  void operator()(PARMS... args) noexcept override {
    m_managed_CallHandler->invoke(std::forward<PARMS>(args)...);
  }
  size_t get_subscriber_id() const noexcept override {
    return m_managed_CallHandler->id();
  }
  long get_use_count() const noexcept override {
    return m_managed_CallHandler.use_count();
  }
  ~Delegate() noexcept override = default;
};
EDS_END_NAMESPACE
#endif
