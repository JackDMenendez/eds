#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include "call_handler.hpp"
#include "subscriber.hpp"
#include <memory>
#include "../eds_traits.hpp"
#include "../eds_concepts.hpp"
EDS_BEGIN_NAMESPACE
template <class... SIGNATURE> class Delegate;
template <class... PARMS>
class Delegate<void(PARMS...) noexcept> : public DelegateResourceManager<PARMS...> {
   public:
     using Signature = void(PARMS...) noexcept;
     using SubscriberType = Subscriber<PARMS...>;
     using ResourceManagerType = DelegateResourceManager<PARMS...>;
     using local_shared_ptr_t = std::shared_ptr<SubscriberType>;
     local_shared_ptr_t m_managed_CallHandler;
     constexpr Delegate() noexcept = default;
     template <class CALLBACK>
     requires a_function<CALLBACK> && has_noexcept<CALLBACK> 
     constexpr explicit Delegate(CALLBACK const *callback) noexcept
         : m_managed_CallHandler(
               std::make_shared<CallHandler<FunctionPointer, PARMS...>>(callback, this)) {}
     template <class CALLBACK>
          requires lamda_rc_is_void<CALLBACK, PARMS...>
     constexpr explicit Delegate(CALLBACK &&callback) noexcept
         : m_managed_CallHandler(std::make_shared<CallHandler<LambdaRef, CALLBACK, PARMS...>>(
               std::forward<CALLBACK>(callback), this)) {}
     template <class CALLBACK>
          requires RegularFunction<CALLBACK, PARMS...>
     constexpr explicit Delegate(CALLBACK &&callback) noexcept
         : m_managed_CallHandler(std::make_shared<CallHandler<FunctionPointer, PARMS...>>(
               std::forward<CALLBACK>(callback), this)) {}
     constexpr Delegate(const local_shared_ptr_t &m_managed_CallHandler)
         : m_managed_CallHandler(m_managed_CallHandler) {}
     constexpr bool operator==(const Delegate &other) const noexcept {
          return m_managed_CallHandler == other.m_managed_CallHandler;
          }
     constexpr bool operator!=(const Delegate &other) const noexcept {
           return m_managed_CallHandler != other.m_managed_CallHandler;
       }
     constexpr bool operator==(const ResourceManagerType &other) const noexcept {
            return m_managed_CallHandler == other.m_managed_CallHandler;
            }
     constexpr bool operator!=(const ResourceManagerType &other) const noexcept {
               return m_managed_CallHandler != other.m_managed_CallHandler;
               }
     constexpr bool equals(const Delegate &other) const noexcept {
           return m_managed_CallHandler == other.m_managed_CallHandler;
       }
     constexpr bool equals(const ResourceManagerType &other) const noexcept {
                return m_managed_CallHandler == other.m_managed_CallHandler;
            }
     bool equals(const Resource &other) const noexcept override {
          return get_subscriber_id() == other.get_subscriber_id();
     }
     void invoke(PARMS... args) noexcept override {
          m_managed_CallHandler->invoke(std::forward<PARMS>(args)...);
     }
     void operator()(PARMS... args) noexcept override {
          m_managed_CallHandler->invoke(std::forward<PARMS>(args)...);
     }
     size_t get_subscriber_id() const noexcept override { return m_managed_CallHandler->id(); }
     long get_use_count() const noexcept override { return m_managed_CallHandler.use_count(); }
     constexpr static auto make_delegate(void (*callback)(PARMS...) noexcept) {
          return Delegate(callback);
     }
     template <class CALLBACK> constexpr static auto make_delegate(CALLBACK &&callback) {
          return Delegate(std::forward<CALLBACK>(callback));
     }

};
EDS_END_NAMESPACE
#endif
