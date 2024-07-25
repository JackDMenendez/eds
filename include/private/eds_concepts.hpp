#ifndef EDS_CONCEPTS_HPP
/**
 * @file   eds_concepts.hpp
 * @brief  Concepts used in the EDS library
 * @author Joaquín "Jack" Menéndez
 * @date   March 2024
 */
#define EDS_CONCEPTS_HPP
#include "eds_traits.hpp"
#include "eds_types.hpp"
#include <functional>
#include <type_traits>
EDS_BEGIN_NAMESPACE
template <typename T>
concept a_class = eds::is_class_v<T>;
template <typename T>
concept something_copyable = eds::is_copyable_v<T>;
template <typename T>
concept something_not_copyable = eds::is_not_copyable_v<T>;
template <class T>
concept some_class_type = std::is_class<T>::value;
template <typename T>
concept something_movable = eds::is_movable_v<T>;
template <typename T>
concept something_not_movable = eds::is_not_movable_v<T>;
template <typename T>
concept something_not_copyable_and_not_movable = eds::is_not_copyable_and_not_movable_v<T>;
template <typename T>
concept something_copyable_and_movable = eds::is_copyable_and_movable_v<T>;
template <typename T>
concept something_copyable_or_movable = eds::is_copyable_or_movable_v<T>;
template <typename T>
concept something_copyable_but_not_movable = eds::is_copyable_and_not_movable_v<T>;
template <typename T>
concept something_not_copyable_but_movable = eds::is_not_copyable_and_movable_v<T>;
/// @brief A concept that checks if a type is psuedo class specifying constant or no constant
/// call
template <class T>
concept ConstRegime = is_psuedo_constant_specification_v<T>;
template <class T>
concept ExceptRegime = is_exception_specification_v<T>;
template <class T>
concept TheResourceHandlingRegime = is_resource_handling_regime_v<T>;
template <class T>
concept a_function = std::is_function_v<T>;
template <typename FUNC, typename... PARAMS>
concept RegularFunction =
    !std::is_class_v<std::remove_pointer_t<std::remove_reference_t<FUNC>>> // deny structs and
                                                                           // classes
    && !std::is_object_v<std::remove_pointer<std::remove_reference<FUNC>>>;
template <typename FUNC, typename... PARAMS>
concept LambdaFunctor =
    std::is_class_v<std::remove_pointer_t<std::remove_reference_t<FUNC>>> // only structs and
                                                                          // classes
    ;
template <typename CLASS>
concept copyable =
    std::is_nothrow_copy_constructible_v<CLASS> || std::is_nothrow_copy_assignable_v<CLASS> ||
    std::is_copy_constructible_v<CLASS> || std::is_copy_assignable_v<CLASS>;
template <typename CLASS>
concept noncopyable =
    !std::is_nothrow_copy_constructible_v<CLASS> &&
    !std::is_nothrow_copy_assignable_v<CLASS> && !std::is_copy_constructible_v<CLASS> &&
    !std::is_copy_assignable_v<CLASS>;
template <typename CLASS>
concept movable =
    std::is_nothrow_move_constructible_v<CLASS> || std::is_nothrow_move_assignable_v<CLASS> ||
    std::is_move_constructible_v<CLASS> || std::is_move_assignable_v<CLASS>;
template <typename CLASS>
concept nonmovable = !std::is_nothrow_move_constructible_v<CLASS> &&
                     !std::is_nothrow_move_assignable_v<CLASS> &&
                     !std::is_move_constructible_v<CLASS> && !std::is_move_assignable_v<CLASS>;
template <typename FUNC, typename... PARAMS>
concept lamda_rc_is_void =
    LambdaFunctor<FUNC, PARAMS...> && std::is_void_v<std::invoke_result_t<FUNC, PARAMS...>>;
template <typename FUNC>
concept has_noexcept = FunctionTypeChecker<FUNC>::is_noexcept_v;
template <typename FUNC>
concept has_void_return_code = FunctionTypeChecker<FUNC>::is_return_code_void_v;
template <typename FUNC>
concept has_nonvoid_return_code = !FunctionTypeChecker<FUNC>::is_return_code_void_v;
template <typename FUNC>
concept eligible_delegate = FunctionTypeChecker<FUNC>::is_eligible_delegate_v;
template <typename FUNC, typename... PARAMS>
concept a_functor = std::is_invocable_v<FUNC, PARAMS...>;
/// TODO add following to test
template <typename FUNC, typename... PARAMS>
concept a_functor_with_void_rc = std::is_invocable_r_v<void, FUNC, PARAMS...>;
template <typename FUNC, typename... PARAMS>
concept a_functor_with_noexcept = std::is_nothrow_invocable_v<FUNC, PARAMS...>;
template <typename FUNC, typename... PARAMS>
concept a_functor_with_void_rc_noexcept =
    a_functor_with_void_rc<FUNC, PARAMS...> && a_functor_with_noexcept<FUNC, PARAMS...>;
template <typename CLASS, typename FUNC, typename... PARAMS>
concept a_member_function = std::is_member_function_pointer_v<FUNC>;
template <typename FUNC, typename... PARAMS>
concept a_member_object = std::is_member_object_pointer_v<FUNC>;
template <typename FUNC, typename... PARAMS>
concept a_member = FunctionTypeChecker<FUNC>::is_member_v;
template <typename FUNC, typename... PARAMS>
concept a_const_member = FunctionTypeChecker<FUNC>::is_constant_v;
template <typename FUNC, typename... PARAMS>
concept not_a_member_function = FunctionTypeChecker<FUNC>::is_member_function_v == false;
/**
@concept a_regular_function an eligible static or global function. It is the type pointed to by
a pointer to a function.

@tparam FUNCPTR the function pointer type to be checked
@tparam PARAMS the parameters of the function
@sa UT010100
*/
// clang-format off
template <class FUNCPTR, class... PARAMS>
concept a_regular_function_with_RC =
    not_a_member_function<FUNCPTR> == true and
    std::is_member_object_pointer_v<FUNCPTR> == false and // means not a member object
    std::is_class_v<std::remove_pointer_t<FUNCPTR>> == false and // means not a std::function or functor or lambda
    std::is_function_v<std::remove_pointer_t<FUNCPTR>> == true and // means not a std::function
    has_void_return_code<FUNCPTR> == false and
    has_noexcept<FUNCPTR> == true and 
    a_member<FUNCPTR, PARAMS...> == false and 
    eligible_delegate<FUNCPTR> == false and
    (FunctionTypeChecker<FUNCPTR>::num_params == sizeof...(PARAMS));
template <class FUNCPTR, class... PARAMS>
concept a_regular_function_except_rc =
    not_a_member_function<FUNCPTR> == true and
    std::is_member_object_pointer_v<FUNCPTR> == false and // means not a member object
    std::is_class_v<std::remove_pointer_t<FUNCPTR>> == false and // means not a std::function or functor or lambda
    std::is_function_v<std::remove_pointer_t<FUNCPTR>> == true and // means not a std::function
    has_noexcept<FUNCPTR> == false and 
    has_void_return_code<FUNCPTR> == false and
    a_member<FUNCPTR, PARAMS...> == false and 
    eligible_delegate<FUNCPTR> == false and
    (FunctionTypeChecker<FUNCPTR>::num_params == sizeof...(PARAMS));
template <class FUNCPTR, class... PARAMS>
concept a_regular_function_except =
    not_a_member_function<FUNCPTR> == true and
    std::is_member_object_pointer_v<FUNCPTR> == false and // means not a member object
    std::is_class_v<std::remove_pointer_t<FUNCPTR>> == false and // means not a std::function or functor or lambda
    std::is_function_v<std::remove_pointer_t<FUNCPTR>> == true and // means not a std::function
    has_void_return_code<FUNCPTR> == true and
    has_noexcept<FUNCPTR> == false and 
    a_member<FUNCPTR, PARAMS...> == false and 
    eligible_delegate<FUNCPTR> == false and
    (FunctionTypeChecker<FUNCPTR>::num_params == sizeof...(PARAMS));
template <class FUNCPTR, class... PARAMS>
concept a_regular_function =
    not_a_member_function<FUNCPTR> == true and
    std::is_member_object_pointer_v<FUNCPTR> == false and // means not a member object
    std::is_class_v<std::remove_pointer_t<FUNCPTR>> == false and // means not a std::function or functor or lambda
    std::is_function_v<std::remove_pointer_t<FUNCPTR>> == true and // means not a std::function
    has_noexcept<FUNCPTR> == true and 
    has_void_return_code<FUNCPTR> == true and
    std::is_same_v<FUNCPTR, SubscriberFunctionWithParams_t<PARAMS...>> == true and
    a_member<FUNCPTR, PARAMS...> == false and 
    eligible_delegate<FUNCPTR> == true and
    (FunctionTypeChecker<FUNCPTR>::num_params == sizeof...(PARAMS));
// clang-format on
/**
@brief Require an eligible static or global function to be used with an pointer

@tparam FUNCTION the function type to be checked
@tparam PARAMS the parameters of the function
@sa UT010100
*/
// clang-format off
template <class FUNCTION, class... PARAMS>
concept a_functional_lvalue =
    std::is_invocable_v<FUNCTION, PARAMS...> &&
    eds::is_copyable_v<FUNCTION> &&
    eds::is_class_v<FUNCTION> &&
    !std::is_function_v<FUNCTION>
    ;
template <class FUNCTION, class... PARAMS>
concept a_functional_rvalue =
    std::is_invocable_v<FUNCTION, PARAMS...> &&
    eds::is_movable_v<FUNCTION> &&
    eds::is_class_v<FUNCTION> &&
    !std::is_function_v<FUNCTION>
    ;
template <class FUNCTION, class... PARAMS>
concept a_functional_value =
    std::is_invocable_v<FUNCTION, PARAMS...> &&
    eds::is_class_v<FUNCTION> &&
    !std::is_function_v<FUNCTION> &&
    std::is_convertible_v<FUNCTION, SubscriberSTDFunctionWithParams_t<PARAMS...>>
    ;
// clang-format on
template <class FUNCTION, class CLASS, class... PARAMS>
concept a_member_functional_lvalue =
    std::is_invocable_v<FUNCTION, PARAMS...> && eds::is_copyable_v<FUNCTION> &&
    eds::is_class_v<FUNCTION> &&
    std::is_convertible_v<FUNCTION, std::function<void (CLASS::*)(PARAMS...)>>;
template <class CLASS, class FUNC, class... PARAMS>
concept a_member_function_pointer =
    std::is_member_function_pointer_v<FUNC> && some_class_type<CLASS> &&
    (std::is_convertible_v<FUNC, void (CLASS::*)(PARAMS...) noexcept>);
/**
@brief Require an eligible lambda functor as an rvalue
@tparam LAMBDA the std::function type to be checked
@tparam PARAMS the parameters of the functor
@sa UT010110
*/
template <class LAMBDA, class... PARAMS>
concept a_lambda_rvalue =
    eds::is_movable_v<LAMBDA> &&
    //(std::is_convertible_v<LAMBDA, void(PARAMS...) noexcept>) &&
    (eds::is_class_v<LAMBDA>) && std::is_nothrow_invocable_v<LAMBDA, PARAMS...>;
template <class FUNC, class... PARAMS>
concept a_lambda_lvalue =
    std::is_nothrow_invocable_v<FUNC, PARAMS...> && eds::is_copyable_v<FUNC> &&
    //(std::is_convertible_v<FUNC, void(PARAMS...) noexcept>) &&
    (eds::is_class_v<FUNC>);
template <class FUNC, class... PARAMS>
concept a_lambda = std::is_invocable_v<FUNC, PARAMS...>;
/**
 * @brief Require an eligible member function pointer
 *
 * @details This concept checks if the function pointer is a member function pointer and if the
 * number of params is greater than 0 and the number of params is correct.
 */
template <class CLASS, class FUNC, class... PARAMS>
concept a_member_functional =
    some_class_type<CLASS> && FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    (!FunctionTypeChecker<FUNC>::is_constant_v) &&
    (std::is_convertible_v<FUNC, void (CLASS::*)(PARAMS...) noexcept>) &&
    (FunctionTypeChecker<FUNC>::num_params == sizeof...(PARAMS));
/**
 * @brief Require an eligible const member function pointer
 *
 * @details This concept checks if the function pointer is a member function pointer and if the
 * number of params is greater than 0 and the number of params is correct.
 */
template <class CLASS, class FUNC, class... PARAMS>
concept a_const_member_function_pointer =
    std::is_member_function_pointer_v<FUNC> && some_class_type<CLASS> &&
    FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    FunctionTypeChecker<FUNC>::is_constant_v && a_member_function<CLASS, FUNC, PARAMS...> &&
    (FunctionTypeChecker<FUNC>::num_params > 0) &&
    (std::is_convertible_v<FUNC, void (CLASS::*)(PARAMS...) const noexcept>) &&
    (FunctionTypeChecker<FUNC>::num_params == sizeof...(PARAMS));
template <class CLASS, class FUNC, class... PARAMS>
concept a_const_member_functional =
    some_class_type<CLASS> && FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    FunctionTypeChecker<FUNC>::is_constant_v && (FunctionTypeChecker<FUNC>::num_params > 0) &&
    //(std::is_convertible_v<FUNC, void(CLASS::*)(PARAMS...) const noexcept>) &&
    (FunctionTypeChecker<FUNC>::num_params == sizeof...(PARAMS));

/// @brief Require an eligible static or global function to be used with an pointer
///
/// @tparam FUNC the function type to be checked
template <class FUNC>
concept a_regular_function_pointer_without_params =
    std::is_function_v<FUNC> && has_noexcept<FUNC> && has_void_return_code<FUNC> &&
    std::is_convertible_v<FUNC, void (*)() noexcept> && !a_member<FUNC> &&
    eligible_delegate<FUNC> && (FunctionTypeChecker<FUNC>::num_params == 0);
/// @brief Require an eligible std::function as an lvalue that has no parameters
template <class FUNC>
concept a_functional_lvalue_without_params =
    std::is_invocable_v<FUNC> && std::is_move_assignable_v<FUNC> &&
    std::is_move_constructible_v<FUNC> && std::is_class_v<std::remove_reference_t<FUNC>> &&
    std::is_convertible_v<FUNC, std::function<void()>>;
template <class FUNC, class CLASS>
concept a_functional_member_lvalue_without_params =
    std::is_class_v<std::remove_reference_t<CLASS>> && std::is_invocable_v<FUNC, CLASS *> &&
    std::is_move_assignable_v<FUNC> && std::is_move_constructible_v<FUNC> &&
    std::is_class_v<std::remove_reference_t<FUNC>>
    //&& std::is_convertible_v<FUNC, std::function<void(CLASS::*)() noexcept>>
    ;
template <class LAMBDA>
concept a_lambda_without_params =
    eds::is_copyable_or_movable_v<LAMBDA> && (eds::is_class_v<LAMBDA>) &&
    std::is_nothrow_invocable_v<LAMBDA>;
/// @brief Require an eligible functor like a lambda but excluding std::function to be used as
/// an lvalue
template <class FUNC>
concept a_lambda_lvalue_without_params = std::is_nothrow_invocable_v<FUNC> &&
                                         // eds::is_copyable_v<FUNC> &&
                                         //(std::is_convertible_v<FUNC, void() noexcept>) &&
                                         (eds::is_class_v<FUNC>);
template <class LAMBDA>
concept a_lambda_rvalue_without_params =
    // eds::is_movable_v<LAMBDA> &&
    (eds::is_class_v<LAMBDA>) &&
    //(std::is_convertible_v<LAMBDA, void() noexcept>) &&
    std::is_nothrow_invocable_v<LAMBDA>;
template <class CLASS, class FUNC>
concept a_member_function_pointer_without_params =
    std::is_member_function_pointer_v<FUNC> && some_class_type<CLASS> &&
    FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    (!FunctionTypeChecker<FUNC>::is_constant_v) && a_member_function<CLASS, FUNC> &&
    (FunctionTypeChecker<FUNC>::num_params == 0);
template <class CLASS, class FUNC>
concept a_member_functional_without_params =
    some_class_type<CLASS> && FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    (!FunctionTypeChecker<FUNC>::is_constant_v) &&
    (FunctionTypeChecker<FUNC>::num_params == 0);
template <class CLASS, class FUNC>
concept a_const_member_function_pointer_without_params =
    std::is_member_function_pointer_v<FUNC> && some_class_type<CLASS> &&
    FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    FunctionTypeChecker<FUNC>::is_constant_v && a_member_function<CLASS, FUNC> &&
    (FunctionTypeChecker<FUNC>::num_params == 0);
template <class CLASS, class FUNC>
concept a_const_member_functional_without_params =
    some_class_type<CLASS> && FunctionTypeChecker<FUNC>::is_eligible_delegate_v &&
    FunctionTypeChecker<FUNC>::is_constant_v && (FunctionTypeChecker<FUNC>::num_params == 0);

EDS_END_NAMESPACE
#endif
