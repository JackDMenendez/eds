#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include "../eds_concepts.hpp"
#include "../eds_traits.hpp"
#include "call_handler.hpp"
#include "subscriber.hpp"
#include <memory>
#include "../eds_env.hpp"
#include "delegate_resource_manager.hpp"
#include "resource.hpp"
EDS_BEGIN_NAMESPACE
template <class... SIGNATURE> class Delegate;
template <class... PARMS>
/**
 * @brief Delegate supporting functions with parameters.
 * @param PARMS... The parameter types of the function.
 * @details This class is a delegate that can be used to call functions with parameters but
 * the intention is to manage a resource that is a subscriber to an event.
 * @par
 * The Delegate class is copyable but not movable because the payload is a shared pointer. The
 * `std::shared_ptr` is used to manage the lifetime of the subscriber and is stored as a
 * `std::weak_ptr` by the event when the Delegate is added.
 */
class Delegate<void(PARMS...) noexcept> : public DelegateResourceManager<PARMS...> {
   public:
     using Signature_t = void(PARMS...) noexcept;
     using SubscriberType = Subscriber<PARMS...>;
     using ResourceManagerType = DelegateResourceManager<PARMS...>;
     using local_shared_ptr_t = std::shared_ptr<SubscriberType>;
     local_shared_ptr_t m_managed_CallHandler; // The payload
     constexpr Delegate() noexcept = default;
     constexpr Delegate(const Delegate &other) noexcept = default; // copyable
     constexpr Delegate(Delegate &&other) noexcept = delete;       // not movable
     constexpr Delegate &operator=(const Delegate &other) noexcept = default;
     constexpr Delegate &operator=(Delegate &&other) noexcept = delete;

   protected:
     /** @brief Construct a Delegate from a pointer to a non-member or static function */
     template <class FUNCPTR>
          requires a_regular_function_pointer<FUNCPTR, PARMS...>
     constexpr explicit Delegate(FUNCPTR *callback) noexcept
         : m_managed_CallHandler(
               std::make_shared<CallHandler<FunctionPointer, PARMS...>>(callback, this)) {}
     /** @brief Construct a Delegate from a copyable std::function */
     template <typename FUNCTIONAL>
          requires eds::a_functional_lvalue<FUNCTIONAL, PARMS...>
     constexpr explicit Delegate(FUNCTIONAL &callback) noexcept
         : m_managed_CallHandler(std::make_shared<CallHandler<FUNCTIONAL, PARMS...>>(callback, this)) {}
     /** @brief Construct a Delegate from a copyable std::function */
     //template <typename FUNCTIONAL>
     //     requires eds::a_functional_rvalue<FUNCTIONAL, PARMS...>
     //constexpr explicit Delegate(FUNCTIONAL &&callback) noexcept
     //    : m_managed_CallHandler(std::make_shared<CallHandler<FUNCTIONAL, PARMS...>>(callback, this)) {}

   public:
     /** @brief CTOR Return a Delegate from a pointer to a non-member or static function */
     template <class FUNCPTR>
          requires a_regular_function_pointer<FUNCPTR, PARMS...>
     static constexpr Delegate<Signature_t> make_delegate(FUNCPTR *callback) noexcept {
          return Delegate<Signature_t>(callback);
     }
     /** @brief CTOR Return a Delegate from a copyable std::function */
     template <class FUNCTIONAL>
          requires eds::a_functional_lvalue<FUNCTIONAL, PARMS...>
     static constexpr Delegate<Signature_t> make_delegate(FUNCTIONAL &callback) noexcept {
          return Delegate<Signature_t>(std::forward<FUNCTIONAL>(callback));
     }
     /** @brief CTOR Return a Delegate from a move only std::function */
     //template <class FUNCTIONAL>
     //     requires eds::a_functional_rvalue<FUNCTIONAL, PARMS...>
     //static constexpr Delegate<Signature_t> make_delegate(FUNCTIONAL &&callback) noexcept {
     //     return Delegate<Signature_t>(std::move<FUNCTIONAL>(callback));
     //}
     template <class FUNCPTR>
          requires a_regular_function_pointer<FUNCPTR, PARMS...>
     constexpr bool operator==(FUNCPTR *callback) const noexcept {
          return m_managed_CallHandler->id() == reinterpret_cast<size_t>(callback);
     }

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
};
EDS_END_NAMESPACE
#endif
