#ifndef CALL_HANDLER_HPP
#define CALL_HANDLER_HPP
#include "../eds_concepts.hpp"
#include "../eds_traits.hpp"
#include "member_call.hpp"
#include "resource.hpp"
#include "subscriber.hpp"
#include <memory>
#include <type_traits>
EDS_BEGIN_NAMESPACE
template <class... SIGNATURE> class CallHandler;
template <class RESOURCE_REGIME, class... SIGNATURE2>
     requires TheResourceHandlingRegime<RESOURCE_REGIME>
class CallHandler<RESOURCE_REGIME, SIGNATURE2...>;
/**
 * functor that encapsulates a Subscriber's handler.
 */
template <class LAMBDA, class... PARAMS>
class CallHandler<LambdaRef, LAMBDA, PARAMS...> : public Subscriber<PARAMS...> {
   public:
     using CallBack_t = void(PARAMS...) noexcept;
     using Subscriber_t = Subscriber<PARAMS...>;
     using delegate_Resource_manager_t = DelegateResourceManager<PARAMS...>;
     using CallBackPtr_t = void (*)(PARAMS...) noexcept;

   private:
     LAMBDA m_call_back;
     size_t m_resource_id;
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &&call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_id((size_t)&m_call_back),
           m_resource_manager(d) {}
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_id((size_t)&m_call_back),
           m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }

     void invoke(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
template <class... PARAMS>
class CallHandler<FunctionPointer, PARAMS...> : public Subscriber<PARAMS...> {
   public:
     using CallBack_t = void(PARAMS...) noexcept;
     using Subscriber_t = Subscriber<PARAMS...>;
     using delegate_Resource_manager_t = DelegateResourceManager<PARAMS...>;
     using CallBackPtr_t = void (*)(PARAMS...) noexcept;

   private:
     union {
          void (*m_call_back)(PARAMS...) noexcept;
          size_t m_resource_id;
     };
     Resource *m_resource_manager = nullptr;

   public:
     constexpr CallHandler(void (*call_back)(PARAMS...) noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(call_back), m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }

     void invoke(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
template <class... PARAMS>
class CallHandler<FunctionType, PARAMS...> : public Subscriber<PARAMS...> {
   public:
     using CallBack_t = void(PARAMS...) noexcept;
     using Subscriber_t = Subscriber<PARAMS...>;
     using delegate_Resource_manager_t = DelegateResourceManager<PARAMS...>;
     using CallBackPtr_t = void (*)(PARAMS...) noexcept;

   private:
     union {
          void (*m_call_back)(PARAMS...) noexcept;
          size_t m_resource_id;
     };
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CALLBACK>
          requires RegularFunction<CALLBACK, PARAMS...>
     constexpr CallHandler(CALLBACK &&call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }

     void invoke(PARAMS... args) noexcept override {
          m_call_back(std::forward<PARAMS>(args)...);
     }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
/**
 * functor that encapsulates a Subscriber's handler.
 */

template <class... PARAMS>
class CallHandler<PsuedoMemberPointer, PARAMS...> : public Subscriber<PARAMS...> {
   public:
     using CallBack_t = void(PARAMS...) noexcept;
     using Subscriber_t = Subscriber<PARAMS...>;
     using delegate_Resource_manager_t = DelegateResourceManager<PARAMS...>;
     using CallBackPtr_t = void (*)(PARAMS...) noexcept;

   private:
     std::shared_ptr<EDS Caller<PARAMS...>> m_call_back;
     size_t m_resource_id;
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS *class_instance,
                           void (CLASS::*call_back)(PARAMS...) const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS *class_instance, void (CLASS::*call_back)(PARAMS...) noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS &class_instance, void (CLASS::*call_back)(PARAMS...) noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS &class_instance,
                           void (CLASS::*call_back)(PARAMS...) const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS &&class_instance,
                           void (CLASS::*call_back)(PARAMS...) noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS &&class_instance,
                           void (CLASS::*call_back)(PARAMS...) const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::make_shared<
                       MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARAMS...>>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()(PARAMS... args) noexcept override {
          m_call_back->invoke(std::forward<PARAMS>(args)...);
     }

     void invoke(PARAMS... args) noexcept override {
          m_call_back->invoke(std::forward<PARAMS>(args)...);
     }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};

template <> class CallHandler<PsuedoMemberPointer> : public Subscriber<> {
   public:
     using CallBack_t = void() noexcept;
     using Subscriber_t = Subscriber<>;
     using delegate_Resource_manager_t = DelegateResourceManager<>;
     using CallBackPtr_t = void (*)() noexcept;

   private:
     std::shared_ptr<Caller<>> m_call_back;
     // void (*m_call_back)(PARAMS...) noexcept;
     size_t m_resource_id;
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS *class_instance,
                           void (CLASS::*call_back)() const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, Constant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS *class_instance, void (CLASS::*call_back)() noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS &class_instance, void (CLASS::*call_back)() noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS &class_instance,
                           void (CLASS::*call_back)() const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, Constant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(CLASS &&class_instance, void (CLASS::*call_back)() noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }
     template <typename CLASS>
          requires some_class_type<CLASS>
     constexpr CallHandler(const CLASS &&class_instance,
                           void (CLASS::*call_back)() const noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(new MemberCall<VoidReturnCode, Constant, NoException, CLASS>(
               class_instance, call_back)),
           m_resource_manager(d) {
          m_resource_id = m_call_back->hash();
     }

     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()() noexcept override { m_call_back->invoke(); }

     void invoke() noexcept override { m_call_back->invoke(); }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};

/**
 * functor that encapsulates a Subscriber's handler.
 */
template <> class CallHandler<FunctionType> : public Subscriber<> {
   public:
     using CallBack_t = void() noexcept;
     using Subscriber_t = Subscriber<>;
     using delegate_Resource_manager_t = DelegateResourceManager<>;
     using CallBackPtr_t = void (*)() noexcept;

   private:
     union {
          void (*m_call_back)() noexcept;
          size_t m_resource_id;
     };
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &&call_back, size_t resource_id,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_manager(d) {}
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()() noexcept override { m_call_back(); }

     void invoke() noexcept override { m_call_back(); }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
template <> class CallHandler<FunctionPointer> : public Subscriber<> {
   public:
     using CallBack_t = void() noexcept;
     using Subscriber_t = Subscriber<>;
     using delegate_Resource_manager_t = DelegateResourceManager<>;
     using CallBackPtr_t = void (*)() noexcept;

   private:
     union {
          void (*m_call_back)() noexcept;
          size_t m_resource_id;
     };
     Resource *m_resource_manager = nullptr;

   public:
     constexpr CallHandler(void (*call_back)() noexcept,
                           delegate_Resource_manager_t *d) noexcept
         : m_call_back(call_back), m_resource_manager(d) {}
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()() noexcept override { m_call_back(); }

     void invoke() noexcept override { m_call_back(); }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
template <class LAMBDA> class CallHandler<LambdaRef, LAMBDA> : public Subscriber<> {
   public:
     using CallBack_t = LAMBDA;
     using Subscriber_t = Subscriber<>;
     using delegate_Resource_manager_t = DelegateResourceManager<>;
     using CallBackPtr_t = LAMBDA *;

   private:
     LAMBDA m_call_back;
     size_t m_resource_id;
     Resource *m_resource_manager = nullptr;

   public:
     template <typename CALLBACK>
     constexpr CallHandler(CALLBACK &call_back, delegate_Resource_manager_t *d) noexcept
         : m_call_back(std::forward<CALLBACK>(call_back)), m_resource_id((size_t)&m_call_back),
           m_resource_manager(d) {}
     Resource &get_delegate() const noexcept override { return *m_resource_manager; }
     void set_delegate(Resource *delegate) noexcept override { m_resource_manager = delegate; }
     void operator()() noexcept override { m_call_back(); }

     void invoke() noexcept override { m_call_back(); }
     bool equals(const SubscriberBase &other) const noexcept override {
          return id() == other.id();
     }
     size_t id() const noexcept override { return m_resource_id; }
     ~CallHandler() noexcept override = default;
};
EDS_END_NAMESPACE
#endif // !CALL_HANDLER_HPP
