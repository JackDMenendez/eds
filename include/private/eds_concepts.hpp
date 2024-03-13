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
EDS_END_NAMESPACE
#endif
