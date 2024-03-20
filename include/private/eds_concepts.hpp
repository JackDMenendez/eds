#ifndef EDS_CONCEPTS_HPP
#define EDS_CONCEPTS_HPP
#include "eds_traits.hpp"
#include <type_traits>
EDS_BEGIN_NAMESPACE
template <class T>
concept SomeClassType = std::is_class<T>::value;
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
template <typename FUNC, typename... PARAMS>
concept lamda_rc_is_void =
    LambdaFunctor<FUNC, PARAMS...> && std::is_void_v<std::invoke_result_t<FUNC, PARAMS...>>;
template <typename FUNC>
concept has_noexcept = FunctionTypeChecker<FUNC>::is_noexcept_v;
template <typename FUNC>
concept has_void_return_code = FunctionTypeChecker<FUNC>::is_void_return_code_v;
EDS_END_NAMESPACE
#endif
