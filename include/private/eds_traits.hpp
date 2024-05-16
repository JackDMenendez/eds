#ifndef TRAITS_HPP
#define TRAITS_HPP
#include "eds_util.hpp"
#include <tuple>
#include <type_traits>
#include <functional>
EDS_BEGIN_NAMESPACE
/**
 * @brief Determine if a type is a class.
 *  
 * @details eds::is_class_v is a UnaryTypeTrait.
 * Removes pointers and references then checks whether T is a non-union class type. 
 * 
 * Different than std::is_class, this trait will return true if the type is a class or
 * a pointer to a class or a reference to a class. There is no is_class::value, only
 * is_class_v<T>.
 * 
 * @tparam T The type to check for class.
 * 
 * @returns Provides the member constant value which is equal to true, if T is a class type 
 * (but not union). Otherwise, value is equal to false.
 * 
 * @example
 * 
 * `#include <iostream>`
 * `#include <type_traits>`
 *
 * `struct A {};`
 *
 * `class B {};`
 *
 * `enum class E {};`
 * 
 * `union U { class UC {}; };`
 * `static_assert(not std::is_class_v<U>);`
 * `static_assert(std::is_class_v<U::UC>);`
 * 
 * `int main()`
 * `{`
 * `    std::cout << std::boolalpha;`
 * `    std::cout << eds::is_class_v<A>::value << ": A\n";`
 * `    std::cout << eds::is_class_v<B> << ": B\n";`
 * `    std::cout << eds::is_class_v<B*> << ": B*\n";`
 * `    std::cout << eds::is_class_v<B&> << ": B&\n";`
 * `    std::cout << eds::is_class_v<const B> << ": const B\n";`
 * `    std::cout << eds::is_class<E>::value << ": E\n";`
 * `    std::cout << eds::is_class_v<int> << ": int\n";`
 * `    std::cout << eds::is_class_v<struct S> << ": struct S (incomplete)\n";`
 * `    std::cout << eds::is_class_v<class C> << ": class C (incomplete)\n";`
 * `}`
 *
 * ### Output
 * 
 *        eds::is_class_v          | std::is_class_v              | different
 * ------------------------------- | ---------------------------- | ---------
 * true: A                         | true: A                      |
 * true: B                         | true: B                      |   
 * true: B*                        | false: B*                    | Yes 
 * true B&                         | false: B&                    | Yes
 * true: const B                   | true: const B                |
 * false: E                        | false: E                     |
 * false: int                      | false: int                   |
 * true: struct S (incomplete)     | true: struct S (incomplete)  |
 * true: class C (incomplete)      | true: class C (incomplete)   |
 */
template <typename T>
static constexpr bool is_class_v = std::is_class_v<std::remove_pointer_t<std::remove_reference_t<T>>>; // transfered
template <typename T>
static constexpr bool is_copyable_v =
    (std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>);
template <typename T> static constexpr bool is_not_copyable_v = !is_copyable_v<T>;
template <typename T>
static constexpr bool is_movable_v =
    std::is_move_constructible_v<std::remove_reference_t<T>> &&
    std::is_move_assignable_v<std::remove_reference_t<T>>;
template <typename T> static constexpr bool is_not_movable_v = !is_movable_v<T>;
template <typename T>
static constexpr bool is_not_copyable_and_not_movable_v = is_not_copyable_v<T> && is_not_movable_v<T>;
template <typename T>
static constexpr bool is_copyable_and_movable_v = is_copyable_v<T> && is_movable_v<T>;
template <typename T>
static constexpr bool is_copyable_or_movable_v = is_copyable_v<T> || is_movable_v<T>;
template <typename T>
static constexpr bool is_copyable_and_not_movable_v = is_copyable_v<T> && is_not_movable_v<T>;
template <typename T>
static constexpr bool is_not_copyable_and_movable_v = is_not_copyable_v<T> && is_movable_v<T>;
class PSuedoObject {
   public:
     PSuedoObject() = delete;
     PSuedoObject(const PSuedoObject &) = delete;
     PSuedoObject &operator=(const PSuedoObject &) = delete;
     virtual ~PSuedoObject() = 0;
};
/**
 * @brief Macro that declares a psuedo object.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 *
 * @param DUMMY The name of the psuedo object.
 */
#define EDS_CREATE_PSUEDO(CHILD, PARENT)                                                      \
     class CHILD : PARENT {                                                                   \
        public:                                                                               \
          CHILD() = delete;                                                                   \
          CHILD(const CHILD &) = delete;                                                      \
          CHILD &operator=(const CHILD &) = delete;                                           \
          virtual ~CHILD() = 0;                                                               \
     }

/**
 * @brief A psuedo return code that is used to indicate that a function does not return a
 * value.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(VoidReturnCode, PSuedoObject);
/**
 * @brief A psuedo parameter list that is used to indicate that a function does not have
 * parameters.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(VoidParams, PSuedoObject);
/**
 * @brief A psuedo object that is used to indicate that a function does not have an object.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(PsuedoVoidObject, PSuedoObject);
EDS_CREATE_PSUEDO(PseudoConstantSpecification, PSuedoObject);
EDS_CREATE_PSUEDO(PsuedoExceptionRegime, PSuedoObject);
EDS_CREATE_PSUEDO(NotConstant, PseudoConstantSpecification);
EDS_CREATE_PSUEDO(Constant, PseudoConstantSpecification);
EDS_CREATE_PSUEDO(YesException, PsuedoExceptionRegime);
EDS_CREATE_PSUEDO(NoException, PsuedoExceptionRegime);
EDS_CREATE_PSUEDO(ResourceHandlingRegime, PSuedoObject);
EDS_CREATE_PSUEDO(PsuedoMemberPointer, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(FunctionPointer, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(LambdaRef, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(FunctionType, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(UniquePtr, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(SmartPtr, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(DumbPtr, ResourceHandlingRegime);
template <typename T> struct is_psuedo : public std::false_type {};
template <> struct is_psuedo<VoidReturnCode> : public std::true_type {};
template <> struct is_psuedo<VoidParams> : public std::true_type {};
template <> struct is_psuedo<PsuedoVoidObject> : public std::true_type {};
template <> struct is_psuedo<PseudoConstantSpecification> : public std::true_type {};
template <> struct is_psuedo<NotConstant> : public std::true_type {};
template <> struct is_psuedo<Constant> : public std::true_type {};
template <> struct is_psuedo<ResourceHandlingRegime> : public std::true_type {};
template <> struct is_psuedo<PsuedoMemberPointer> : public std::true_type {};
template <> struct is_psuedo<FunctionPointer> : public std::true_type {};
template <> struct is_psuedo<PsuedoExceptionRegime> : public std::true_type {};
template <> struct is_psuedo<LambdaRef> : public std::true_type {};
template <> struct is_psuedo<FunctionType> : public std::true_type {};
template <> struct is_psuedo<YesException> : public std::true_type {};
template <> struct is_psuedo<NoException> : public std::true_type {};
template <> struct is_psuedo<UniquePtr> : public std::true_type {};
template <> struct is_psuedo<SmartPtr> : public std::true_type {};
template <> struct is_psuedo<DumbPtr> : public std::true_type {};
template <typename T> constexpr static bool is_psuedo_v = is_psuedo<T>::value;
template <typename T>
constexpr static bool is_psuedo_constant_specification_v =
    std::is_base_of<PseudoConstantSpecification, T>::value;
template <typename T>
constexpr static bool is_member_pointer_v = std::is_same_v<T, PsuedoMemberPointer>;
template <typename T>
constexpr static bool is_psuedo_function_pointer_v = std::is_same_v<T, FunctionPointer>;
template <typename T>
constexpr static bool is_resource_handling_regime_v =
    std::is_base_of_v<ResourceHandlingRegime, T>;
template <typename T> struct is_constant : public std::false_type {};
template <> struct is_constant<Constant> : public std::true_type {};
template <typename T> struct is_noexcept : public std::false_type {};
template <> struct is_noexcept<NoException> : public std::true_type {};
template <typename T> constexpr static bool is_noexcept_v = is_noexcept<T>::value;
template <typename T> constexpr static bool is_constant_v = is_constant<T>::value;
template <typename T>
constexpr static bool is_exception_specification_v =
    std::is_base_of<PsuedoExceptionRegime, T>::value;
template <typename T> struct is_void_return_code : public std::false_type {};
template <> struct is_void_return_code<VoidReturnCode> : public std::true_type {};
template <typename T>
constexpr static bool is_void_return_code_v = is_void_return_code<T>::value;
// template <typename T> bool is_pointer_to_regular_function_v = ;

template <class...> struct FunctionTypeChecker;
template <class RC, class... PARAMS> struct FunctionTypeChecker<RC(PARAMS...) noexcept> {
     using ReturnType_t = void;
using ParameterList_t = std::tuple<PARAMS...>;
constexpr static size_t num_params = sizeof...(PARAMS);
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class... PARAMS> struct FunctionTypeChecker<void(PARAMS...) noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<PARAMS...>;
constexpr static auto num_params = sizeof...(PARAMS);
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = true;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class RC, class... PARAMS> struct FunctionTypeChecker<RC(PARAMS...)> {
using ReturnType_t = RC;
using ParameterList_t = std::tuple<PARAMS...>;
constexpr static size_t num_params = sizeof...(PARAMS);
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = false;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = false;
static_assert(is_noexcept_v, "Only functions with noexcept are supported as Delegates.");
};
template <class RC> struct FunctionTypeChecker<RC() noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<void>;
constexpr static size_t num_params = 0;
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <> struct FunctionTypeChecker<void() noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<void>;
constexpr static size_t num_params = 0;
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = true;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class RC> struct FunctionTypeChecker<RC()> {
using ReturnType_t = RC;
using ParameterList_t = std::tuple<void>;
constexpr static size_t num_params = 0;
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = false;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = false;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = false;
static_assert(is_noexcept_v, "Only functions with noexcept are supported as Delegates.");
};
template <class RC, class CLASS, class... PARAMS> struct FunctionTypeChecker<RC(CLASS::*)(PARAMS...) noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<PARAMS...>;
constexpr static size_t num_params = sizeof...(PARAMS);
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = true;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class RC, class CLASS> struct FunctionTypeChecker<RC(CLASS::*)() noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<void>;
constexpr static size_t num_params = 0;
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = true;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = false;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class RC, class CLASS, class... PARAMS> struct FunctionTypeChecker<RC(CLASS::*)(PARAMS...) const noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<PARAMS...>;
constexpr static size_t num_params = sizeof...(PARAMS);
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = true;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = true;
constexpr static bool is_function_v = true;
constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};
template <class RC, class CLASS> struct FunctionTypeChecker<RC(CLASS::*)() const noexcept> {
using ReturnType_t = void;
using ParameterList_t = std::tuple<void>;
constexpr static size_t num_params = 0;
constexpr static bool is_function_pointer_v = false;
constexpr static bool is_member_function_v = true;
constexpr static bool is_return_code_void_v = std::is_void_v<RC>;
constexpr static bool is_noexcept_v = true;
constexpr static bool is_constant_v = true;
     constexpr static bool is_function_v = true;
     constexpr static bool is_eligible_delegate_v = is_noexcept_v & is_return_code_void_v;
};

EDS_END_NAMESPACE
#endif
