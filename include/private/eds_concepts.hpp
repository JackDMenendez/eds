#ifndef EDS_CONCEPTS_HPP
#define EDS_CONCEPTS_HPP
#include <type_traits>
#include "eds_traits.hpp"
EDS_BEGIN_NAMESPACE
template<class T>
concept SomeClassType = std::is_class<T>::value;
/// @brief A concept that checks if a type is psuedo class specifying constant or no constant call
template<class T> concept ConstRegime = is_constant_specification_v<T>;
template <class T>
concept ExceptRegime = is_exception_specification_v<T>;
template <class T>
concept TheResourceHandlingRegime = is_resource_handling_regime_v<T>;
/// @brief Allow a template to require a function that is not a functor or member function
///
/// @details Exclude classes, structs, objects
///
///
/// @tparam FUNC proffered type that is required to by a static or C type of function
/// @tparam PARAMS the argument types passed to the function
template <typename FUNC, typename... PARAMS>
concept regular_function = 
        !std::is_class_v<
            std::remove_pointer_t<
            std::remove_reference_t<FUNC>>> // deny structs and classes
     && !std::is_object_v<
            std::remove_pointer<
            std::remove_reference<FUNC>>>  // allow pointers only
                     //&& !std::is_pointer_v<FUNC> // 
                       //&& !std::is_function_v<FUNC>
                     //&& !std::is_member_function_pointer_v<FUNC> 
                     //&& std::is_compound_v<FUNC>
                     ;
template <typename FUNC, typename... PARAMS>
concept lamda_function = std::is_class_v<std::remove_pointer_t<FUNC>>  // only structs and classes
    //&& std::is_object_v<FUNC>
    //&& !std::is_pointer_v<FUNC>
    //&& !std::is_function_v<FUNC>
    //&& std::is_invocable_v<FUNC, PARAMS...>
    //&& !std::is_member_function_pointer_v<FUNC>
    //&& !std::is_rvalue_reference_v<FUNC>
    //&& std::is_compound_v<FUNC>
    //&& !std::is_lvalue_reference_v<FUNC>
    ;
template <typename FUNC, typename... PARAMS>
concept lamda_rc_is_void =
    lamda_function<FUNC, PARAMS...> 
    && std::is_void_v<std::invoke_result_t<FUNC, PARAMS...>>
    ;
EDS_END_NAMESPACE
#endif
