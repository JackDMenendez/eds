#ifndef EDS_MEMBER_CALL_HPP
#define EDS_MEMBER_CALL_HPP
/**
 *
 * @file member_call.hpp
 * @brief  Implement encapsulation of member function calls.
 * @author Joaquín "Jack" D. Menéndez
 * @date   March 2024
 * @todo Allow only smart pointers to the object for member functions and lambdas, also make
 * for object pointers we can give a message via static assert
 */
#include "../eds_concepts.hpp"
#include "../eds_hash.hpp"
#include "../eds_traits.hpp"
#include "../eds_util.hpp"
#include <cassert>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>
EDS_BEGIN_NAMESPACE
template <class... PARAMS> struct Caller {
     constexpr Caller() noexcept = default;
     constexpr Caller(const Caller &) noexcept = default;
     constexpr Caller(Caller &&) noexcept = default;
     constexpr Caller &operator=(const Caller &) noexcept = default;
     constexpr Caller &operator=(Caller &&) noexcept = default;
     virtual void operator()(PARAMS... args) noexcept = 0;
     virtual void invoke(PARAMS... args) noexcept = 0;
     virtual size_t hash() const noexcept = 0;
     virtual bool is_in_scope() const noexcept = 0;
     virtual void out_of_scope() noexcept = 0;
     virtual ~Caller() noexcept = default;
};
template <> struct Caller<> {
     constexpr Caller() noexcept = default;
     constexpr Caller(const Caller &) noexcept = default;
     constexpr Caller(Caller &&) noexcept = default;
     constexpr Caller &operator=(const Caller &) noexcept = default;
     constexpr Caller &operator=(Caller &&) noexcept = default;
     virtual void operator()() noexcept = 0;
     virtual void invoke() noexcept = 0;
     virtual size_t hash() const noexcept = 0;
     virtual bool is_in_scope() const noexcept = 0;
     virtual void out_of_scope() noexcept = 0;
     virtual ~Caller() noexcept = default;
};
template <typename... SIGNATURE> class MemberCallBase;
template <typename RC, typename CONSTANT, typename EXCEPT_REGIME, typename CLASS,
          typename POINTER, typename... PARMS>
struct MemberCallBase<RC, CONSTANT, EXCEPT_REGIME, CLASS, POINTER, PARMS...>
    : public Caller<PARMS...> {
   public:
     constexpr MemberCallBase() noexcept = default;
     constexpr MemberCallBase(const MemberCallBase &) noexcept = default;
     constexpr MemberCallBase(MemberCallBase &&) noexcept = default;
     constexpr MemberCallBase &operator=(const MemberCallBase &) noexcept = default;
     constexpr MemberCallBase &operator=(MemberCallBase &&) noexcept = default;
     using ReturnCode_t = RC;
     using Constant_t = CONSTANT;
     using ExceptionRegime_t = EXCEPT_REGIME;
     using Class_t = CLASS;
     using Args_t = std::tuple<PARMS...>;
     using Pointer_t = POINTER;
     static constexpr bool constant_v = is_constant_v<CONSTANT>;
     static constexpr bool noexcept_v = is_noexcept_v<EXCEPT_REGIME>;
     static constexpr bool void_rc_v = is_void_return_code_v<RC>;
     static constexpr bool has_params_v = 0 < std::tuple_size_v<Args_t>;
     constexpr ~MemberCallBase() noexcept = default;
};
template <typename RC, typename CONSTANT, typename EXCEPT_REGIME, typename CLASS,
          typename POINTER>
struct MemberCallBase<RC, CONSTANT, EXCEPT_REGIME, CLASS, POINTER> : public Caller<> {
   public:
     constexpr MemberCallBase() noexcept = default;
     constexpr MemberCallBase(const MemberCallBase &) noexcept = default;
     constexpr MemberCallBase(MemberCallBase &&) noexcept = default;
     constexpr MemberCallBase &operator=(const MemberCallBase &) noexcept = default;
     constexpr MemberCallBase &operator=(MemberCallBase &&) noexcept = default;
     using ReturnCode_t = RC;
     using Constant_t = CONSTANT;
     using ExceptionRegime_t = EXCEPT_REGIME;
     using Class_t = CLASS;
     using Args_t = std::tuple<>;
     using Pointer_t = POINTER;
     static constexpr bool constant_v = is_constant_v<CONSTANT>;
     static constexpr bool noexcept_v = is_noexcept_v<EXCEPT_REGIME>;
     static constexpr bool void_rc_v = is_void_return_code_v<RC>;
     static constexpr bool has_params_v = 0 < std::tuple_size_v<Args_t>;
     virtual ~MemberCallBase() noexcept = default;
};
template <typename... FOOTPRINT> class MemberCall;
/**
 * @brief Member call wrapper for non-const member with dumb ptr.
 *
 * @details This class issues a static assert if a dumb pointer is used and NDUMBPTRS is
 * defined as a build parameter.
 *
 * @sa NDUMBPTRS
 *
 * @note We may ban dumb pointers in the future in which case this class will issue a static
 * assert as information to the programmer.
 *
 * @sa MemberCallSpecializationFT_UT020100_Test
 */
template <class CLASS, class... PARMS>
     requires some_class_type<CLASS>
class MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr, PARMS...>
    : public MemberCallBase<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr,
                            PARMS...> {
   public:
#ifdef EDS_NDUMBPTRS
     static_assert(false, "Dumb pointer to CLASS are not allowed in MemberCall. Please use a "
                          "smart pointer instead.");
#endif // EDS_NDUMBPTRS
     static constexpr bool is_legit_v = true;
     /// @brief The type of the member function invoked by this object.
     using Member_t = void (CLASS::*)(PARMS...) noexcept;

   private:
     union {

          CLASS *m_object;
          size_t hash_object;
     };
     union {
          void (CLASS::*m_member)(PARMS...) noexcept;
          size_t hash_member;
     };

   public:
     /**
      * @brief CTOR for encapsulating non-const member function and pointer to non-const class
      * pointer.
      *
      * @details The class instance is used to call the member function with the parameters and
      * class scope. This class implements move and copy protocols because of dumb pointers.
      *
      * @param class_instance_pointer The pointer to the instantiated class containing the
      * member function, member.
      * @param member_function_pointer The pointer to the member function of the class to be
      * called. The member function is required to be a member of the class passed in as
      * class_instance_pointer
      * @sa MemberCallSpecializationFT_UT020100_Test
      */
     constexpr MemberCall(CLASS *class_instance_pointer,
                          void (CLASS::*member_function_pointer)(PARMS...) noexcept) noexcept
         : m_object(class_instance_pointer), m_member(member_function_pointer) {

          assert(!std::is_copy_assignable_v<CLASS>);
          assert(!std::is_copy_constructible_v<CLASS>);
          assert(!std::is_move_assignable_v<CLASS>);
          assert(!std::is_move_constructible_v<CLASS>);
          assert(member_function_pointer != nullptr);
          assert(m_object != nullptr);
     }
     constexpr MemberCall() = default;                                   // move or copy
     constexpr MemberCall(const MemberCall &other) = default;            // copy
     constexpr MemberCall(MemberCall &&other) = default;                 // move
     constexpr MemberCall &operator=(const MemberCall &other) = default; // copy
     constexpr MemberCall &operator=(MemberCall &&other) = default;      // move
     void out_of_scope() noexcept override { m_object = nullptr; }
     bool is_in_scope() const noexcept override { return m_object != nullptr; }
     size_t hash() const noexcept override {
          assert(is_in_scope());
          return hash_to_64_bits(hash_object, hash_member);
     }
     constexpr void operator()(PARMS... args) noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr void invoke(PARMS... args) noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr auto operator==(const Caller<PARMS...> &other) const noexcept -> bool {
          assert(is_in_scope());
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          assert(is_in_scope());
          return !(*this == other);
     }
     virtual ~MemberCall() = default; // move or copy
};
template <class CLASS>
     requires some_class_type<CLASS>
class MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr>
    : public MemberCallBase<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr> {
   public:
#ifdef EDS_NDUMBPTRS
     static_assert(false, "Dumb pointer to CLASS are not allowed in MemberCall. Please use a "
                          "smart pointer instead.");
#endif // EDS_NDUMBPTRS
     static constexpr bool is_legit_v = true;
     /// @brief The type of the member function invoked by this object.
     using Member_t = void (CLASS::*)() noexcept;

   private:
     union {
          CLASS *m_object;
          size_t hash_object;
     };
     union {
          void (CLASS::*m_member)() noexcept;
          size_t hash_member;
     };

   public:
     /**
      * @brief CTOR for encapsulating non-const member function and pointer to non-const class
      * pointer.
      *
      * @details The class instance is used to call the member function with the parameters and
      * class scope. This class implements move and copy protocols because of dumb pointers.
      *
      * @param class_instance_pointer The pointer to the instantiated class containing the
      * member function, member.
      * @param member_function_pointer The pointer to the member function of the class to be
      * called. The member function is required to be a member of the class passed in as
      * class_instance_pointer
      * @sa MemberCallSpecializationFT_UT020100_Test
      */
     constexpr MemberCall(CLASS *class_instance_pointer,
                          void (CLASS::*member_function_pointer)() noexcept) noexcept
         : m_object(class_instance_pointer), m_member(member_function_pointer) {
          assert(member_function_pointer != nullptr);
          assert(m_object != nullptr);
     }
     constexpr MemberCall() = default;                                   // move or copy
     constexpr MemberCall(const MemberCall &other) = default;            // copy
     constexpr MemberCall(MemberCall &&other) = default;                 // move
     constexpr MemberCall &operator=(const MemberCall &other) = default; // copy
     constexpr MemberCall &operator=(MemberCall &&other) = default;      // move
     bool is_in_scope() const noexcept override { return m_object != nullptr; }
     void out_of_scope() noexcept override { m_object = nullptr; }
     size_t hash() const noexcept override {
          assert(is_in_scope());
          return hash_to_64_bits(hash_object, hash_member);
     }

     constexpr void operator()() noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)();
     }
     constexpr void invoke() noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)();
     }
     constexpr auto operator==(Caller<> const &other) const noexcept -> bool {
          assert(is_in_scope());
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          assert(is_in_scope());
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept = default;
};
template <class CLASS, class... PARMS>
     requires some_class_type<CLASS>
class MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...>
    : public MemberCallBase<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...> {
   public:
#ifdef EDS_NDUMBPTRS
     static_assert(false, "Dumb pointer to CLASS are not allowed in MemberCall. Please use a "
                          "smart pointer instead.");
#endif // EDS_NDUMBPTRS
     static constexpr bool is_legit_v = true;
     /// @brief The type of the member function invoked by this object.
     using Member_t = void (CLASS::*)(PARMS...) const noexcept;

   private:
     union {
          const CLASS *m_object;
          const size_t hash_object;
     };
     union {
          void (CLASS::*m_member)(PARMS...) const noexcept;
          const size_t hash_member;
     };

   public:
     /**
      * @brief CTOR for encapsulating non-const member function and pointer to non-const class
      * pointer.
      *
      * @details The class instance is used to call the member function with the parameters and
      * class scope. This class implements move and copy protocols because of dumb pointers.
      *
      * @param class_instance_pointer The pointer to the instantiated class containing the
      * member function, member.
      * @param member_function_pointer The pointer to the member function of the class to be
      * called. The member function is required to be a member of the class passed in as
      * class_instance_pointer
      * @sa MemberCallSpecializationFT_UT020100_Test
      */
     constexpr MemberCall(const CLASS *class_instance_pointer,
                          void (CLASS::*member_function_pointer)(PARMS...)
                              const noexcept) noexcept
         : m_object(class_instance_pointer), m_member(member_function_pointer) {
          assert(member_function_pointer != nullptr);
          assert(m_object != nullptr);
     }
     constexpr MemberCall() = default;                                   // move or copy
     constexpr MemberCall(const MemberCall &other) = default;            // copy
     constexpr MemberCall(MemberCall &&other) = default;                 // move
     constexpr MemberCall &operator=(const MemberCall &other) = default; // copy
     constexpr MemberCall &operator=(MemberCall &&other) = default;      // move
     void out_of_scope() noexcept override { m_object = nullptr; }
     bool is_in_scope() const noexcept override { return true; }
     size_t hash() const noexcept override {
          assert(is_in_scope());
          return hash_to_64_bits(hash_object, hash_member);
     }

     constexpr void operator()(PARMS... args) noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr void invoke(PARMS... args) noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr auto operator==(const Caller<PARMS...> &other) const noexcept -> bool {
          assert(is_in_scope());
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          assert(is_in_scope());
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept {}
};
template <class CLASS>
     requires some_class_type<CLASS>
class MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr>
    : public MemberCallBase<VoidReturnCode, Constant, NoException, CLASS, DumbPtr> {
   public:
     static constexpr bool is_legit_v = true;
     /// @brief The type of the member function invoked by this object.
     using Member_t = void (CLASS::*)() const noexcept;

   private:
     union {
          const CLASS *m_object;
          size_t hash_object;
     };
     union {
          void (CLASS::*m_member)() const noexcept;
          size_t hash_member;
     };

   public:
     /**
      * @brief CTOR for encapsulating non-const member function and pointer to non-const class
      * pointer.
      *
      * @details The class instance is used to call the member function with the parameters and
      * class scope. This class implements move and copy protocols because of dumb pointers.
      *
      * @param class_instance_pointer The pointer to the instantiated class containing the
      * member function, member.
      * @param member_function_pointer The pointer to the member function of the class to be
      * called. The member function is required to be a member of the class passed in as
      * class_instance_pointer
      * @sa MemberCallSpecializationFT_UT020100_Test
      */
     constexpr MemberCall(const CLASS *class_instance_pointer,
                          void (CLASS::*member_function_pointer)()
                              const noexcept) noexcept
         : m_object(class_instance_pointer), m_member(member_function_pointer) {
          assert(member_function_pointer != nullptr);
          assert(m_object != nullptr);
     }
     constexpr MemberCall() = default;                                   // move or copy
     constexpr MemberCall(const MemberCall &other) = default;            // copy
     constexpr MemberCall(MemberCall &&other) = default;                 // move
     constexpr MemberCall &operator=(const MemberCall &other) = default; // copy
     constexpr MemberCall &operator=(MemberCall &&other) = default;      // move
     void out_of_scope() noexcept override { m_object = nullptr; }
     bool is_in_scope() const noexcept override { return true; }
     size_t hash() const noexcept override {
          assert(is_in_scope());
          return hash_to_64_bits(hash_object, hash_member);
     }

     constexpr void operator()() noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)();
     }
     constexpr void invoke() noexcept override {
          assert(is_in_scope());
          (this->m_object->*this->m_member)();
     }
     constexpr auto operator==(const Caller<> &other) const noexcept -> bool {
          assert(is_in_scope());
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          assert(is_in_scope());
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept {}
};
/**
 * Create a non-const method call.
 *
 * /sa MemberCallSpecializationFT_UT020100_Test
 */
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(CLASS *object,
                                  void (CLASS::*member)(PARMS...) noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr, PARMS...> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr, PARMS...>(
         object, member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(CLASS &object,
                                  void (CLASS::*member)(PARMS...) noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr, PARMS...> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr, PARMS...>(
         &object, member);
}
template <typename CLASS>
constexpr auto create_method_call(CLASS &object, void (CLASS::*member)() noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr>(&object,
                                                                                 member);
}
template <typename CLASS>
constexpr auto create_method_call(CLASS *object, void (CLASS::*member)() noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, DumbPtr>(object,
                                                                                 member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(const CLASS &object,
                                  void (CLASS::*member)(PARMS...) const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...>(
         &object, member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(const CLASS *object,
                                  void (CLASS::*member)(PARMS...) const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr, PARMS...>(
         object, member);
}
template <typename CLASS>
constexpr auto create_method_call(const CLASS &object,
                                  void (CLASS::*member)() const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr>(&object, member);
}
/// @brief Create a member call with pointer to object for a const member
/// function.
///
/// @tparam CLASS The type of the instantiated class containing the member
/// function.
/// @returns An instance of MemberCall and not a reference or pointer to it.
/// This is the most
///         efficient way to use this class.
/// @see
/// edsUGTest.MemberCallUGTest.MemberCallUGTest4VoidClassConstNoParamsNoExcept
template <typename CLASS>
constexpr auto create_method_call(CLASS *object,
                                  void (CLASS::*member)() const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, DumbPtr>(object, member);
}
EDS_END_NAMESPACE
#endif
