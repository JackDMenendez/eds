#ifndef EDS_MEMBER_CALL_HPP
#define EDS_MEMBER_CALL_HPP
#include "../eds_concepts.hpp"
#include "../eds_hash.hpp"
#include "../eds_traits.hpp"
#include "../eds_util.hpp"
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
     virtual ~Caller() noexcept = default;
};
template <typename... SIGNATURE> class MemberCallBase;
template <typename RC, typename CONSTANT, typename EXCEPT_REGIME, typename CLASS, typename... PARMS>
struct MemberCallBase<RC, CONSTANT, EXCEPT_REGIME, CLASS, PARMS...> : public Caller<PARMS...> {
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
     static constexpr bool constant_v = is_constant_v<CONSTANT>;
     static constexpr bool noexcept_v = is_noexcept_v<EXCEPT_REGIME>;
     static constexpr bool void_rc_v = is_void_return_code_v<RC>;
     static constexpr bool has_params_v = 0 < std::tuple_size_v<Args_t>;
     constexpr ~MemberCallBase() noexcept = default;
};
template <typename RC, typename CONSTANT, typename EXCEPT_REGIME, typename CLASS>
struct MemberCallBase<RC, CONSTANT, EXCEPT_REGIME, CLASS> : public Caller<> {
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
     static constexpr bool constant_v = is_constant_v<CONSTANT>;
     static constexpr bool noexcept_v = is_noexcept_v<EXCEPT_REGIME>;
     static constexpr bool void_rc_v = is_void_return_code_v<RC>;
     static constexpr bool has_params_v = 0 < std::tuple_size_v<Args_t>;
     virtual ~MemberCallBase() noexcept = default;
};
template <typename... FOOTPRINT> class MemberCall;
template <class CLASS, class... PARMS>
     requires SomeClassType<CLASS>
class MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...>
    : public MemberCallBase<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...> {
   public:
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
     constexpr MemberCall(CLASS *object, void (CLASS::*member)(PARMS...) noexcept) noexcept
         : m_object(object), m_member(member) {}
     constexpr MemberCall(const MemberCall &other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall(const MemberCall &&other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall &operator=(const MemberCall &other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     size_t hash() const noexcept override { return hash_to_64_bits(hash_object, hash_member); }
     constexpr void operator()(PARMS... args) noexcept override {
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr void invoke(PARMS... args) noexcept override {
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr auto operator==(const Caller<PARMS...> &other) const noexcept -> bool {
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept {}
};
template <class CLASS>
     requires SomeClassType<CLASS>
class MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>
    : public MemberCallBase<VoidReturnCode, NotConstant, NoException, CLASS> {
   public:
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
     size_t hash() const noexcept override { return hash_to_64_bits(hash_object, hash_member); }

     constexpr MemberCall(CLASS *object, void (CLASS::*member)() noexcept) noexcept
         : m_object(object), m_member(member) {}
     constexpr MemberCall(const MemberCall &other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall(const MemberCall &&other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall &operator=(const MemberCall &other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr void operator()() noexcept override { (this->m_object->*this->m_member)(); }
     constexpr void invoke() noexcept override { (this->m_object->*this->m_member)(); }
     constexpr auto operator==(Caller<> const &other) const noexcept -> bool {
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept = default;
};
template <class CLASS, class... PARMS>
     requires SomeClassType<CLASS>
class MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARMS...>
    : public MemberCallBase<VoidReturnCode, Constant, NoException, CLASS, PARMS...> {
   public:
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
     size_t hash() const noexcept override { return hash_to_64_bits(hash_object, hash_member); }

     constexpr MemberCall(const CLASS &&object,
                          void (CLASS::*member)(PARMS...) const noexcept) noexcept
         : m_object(&object), m_member(member) {}
     constexpr MemberCall(const CLASS &object,
                          void (CLASS::*member)(PARMS...) const noexcept) noexcept
         : m_object(&object), m_member(member) {}
     constexpr MemberCall(const CLASS *object,
                          void (CLASS::*member)(PARMS...) const noexcept) noexcept
         : m_object(object), m_member(member) {}
     constexpr MemberCall(const MemberCall &other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall(const MemberCall &&other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall operator=(const MemberCall &other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr MemberCall operator=(const MemberCall &&other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr void operator()(PARMS... args) noexcept override {
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr void invoke(PARMS... args) noexcept override {
          (this->m_object->*this->m_member)(std::forward<PARMS>(args)...);
     }
     constexpr auto operator==(const Caller<PARMS...> &other) const noexcept -> bool {
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept {}
};
template <class CLASS>
     requires SomeClassType<CLASS>
class MemberCall<VoidReturnCode, Constant, NoException, CLASS>
    : public MemberCallBase<VoidReturnCode, Constant, NoException, CLASS> {
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
     size_t hash() const noexcept override { return hash_to_64_bits(hash_object, hash_member); }

     constexpr MemberCall(const CLASS *object, void (CLASS::*member)() const noexcept) noexcept
         : m_object(object), m_member(member) {}
     constexpr MemberCall(const CLASS &object, void (CLASS::*member)() const noexcept) noexcept
         : m_object(&object), m_member(member) {}
     constexpr MemberCall(const CLASS &&object, void (CLASS::*member)() const noexcept) noexcept
         : m_object(&object), m_member(member) {}

     constexpr MemberCall(const MemberCall &other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall(const MemberCall &&other) noexcept
         : m_object(other.m_object), m_member(other.m_member) {}
     constexpr MemberCall operator=(const MemberCall other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr MemberCall operator=(const MemberCall &other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr MemberCall operator=(const MemberCall &&other) noexcept {
          this->m_object = other.m_object;
          this->m_member = other.m_member;
          return *this;
     }
     constexpr void operator()() noexcept override { (this->m_object->*this->m_member)(); }
     constexpr void invoke() noexcept override { (this->m_object->*this->m_member)(); }
     constexpr auto operator==(const Caller<> &other) const noexcept -> bool {
          return hash() == other.hash();
     }
     constexpr auto operator!=(MemberCall const &other) const noexcept -> bool {
          return !(*this == other);
     }
     constexpr ~MemberCall() noexcept {}
};
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(CLASS *object, void (CLASS::*member)(PARMS...) noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...>(object, member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(CLASS &object, void (CLASS::*member)(PARMS...) noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS, PARMS...>(&object, member);
}
template <typename CLASS>
constexpr auto create_method_call(CLASS &object, void (CLASS::*member)() noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>(&object, member);
}
template <typename CLASS>
constexpr auto create_method_call(CLASS *object, void (CLASS::*member)() noexcept) noexcept
    -> MemberCall<VoidReturnCode, NotConstant, NoException, CLASS> {
     return MemberCall<VoidReturnCode, NotConstant, NoException, CLASS>(object, member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(const CLASS &object,
                                  void (CLASS::*member)(PARMS...) const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARMS...> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARMS...>(&object, member);
}
template <typename CLASS, typename... PARMS>
constexpr auto create_method_call(const CLASS *object,
                                  void (CLASS::*member)(PARMS...) const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARMS...> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS, PARMS...>(object, member);
}
template <typename CLASS>
constexpr auto create_method_call(const CLASS &object,
                                  void (CLASS::*member)() const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS>(&object, member);
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
constexpr auto create_method_call(CLASS *object, void (CLASS::*member)() const noexcept) noexcept
    -> MemberCall<VoidReturnCode, Constant, NoException, CLASS> {
     return MemberCall<VoidReturnCode, Constant, NoException, CLASS>(object, member);
}
EDS_END_NAMESPACE
#endif
