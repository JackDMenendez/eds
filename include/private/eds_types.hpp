#ifndef EDS_TYPES_HPP
#define EDS_TYPES_HPP
/**
 * @file eds_types.hpp
 * @brief This file contains the definition of the types used in the EDS library.
 * @author Joaquín "Jack" Menéndez
 * @date 2020-08-06 created
 * @version 0.1 created on 2020-08-06
 */
#include "eds_util.hpp"
#include <functional>
#include <memory>
EDS_BEGIN_NAMESPACE
template <typename... PARAMS>
using SubscriberFunctionWithParams_t = void (PARAMS...) noexcept;
template <typename... PARAMS>
using SubscriberFunctionWithParamsDefinedForSTDFunctions_t = void (PARAMS...);
using SubscriberFunctionWithOutParams_t = void () noexcept;
/// @brief A subscriber type that represents a function pointer with parameters and no return value
template <
      typename... PARAMS ///< The list of parameter types of the subscriber function
>
using SubscriberFunctionPTRWithParams_t = void (*)(PARAMS...) noexcept;
/// @brief A subscriber type that represents a std::function containing a pointer to a regular function with parameters and no return value
template <
      typename... PARAMS ///< The list of parameter types of the subscriber function
>
using SubscriberSTDFunctionWithParams_t = std::function<SubscriberFunctionWithParamsDefinedForSTDFunctions_t<PARAMS...>>;
/// @brief A subscriber type that represents a unique_ptr of std::function containing a pointer to a regular function with parameters and no return value
template <
      typename... PARAMS ///< The list of parameter types of the subscriber function
>
using SubscriberUniquePTRSTDFunctionWithParams_t = std::unique_ptr<SubscriberSTDFunctionWithParams_t<PARAMS...>>;
/// @brief A subscriber type that represents a unique_ptr of std::function containing a pointer to a regular function with parameters and no return value
template <
      typename... PARAMS ///< The list of parameter types of the subscriber function
>
using SubscriberSharedPTRSTDFunctionWithParams_t = std::shared_ptr<SubscriberSTDFunctionWithParams_t<PARAMS...>>;
/// @brief A subscriber type that represents a member function pointer with no parameters and no return value
using SubscriberFunctionPTRWithoutParams_t = void (*)() noexcept;
template<class CLASS,class... PARAMS>
using SubscriberMemberFunctionPTRWithParams_t = void (CLASS::*)(PARAMS...) noexcept;
template<class CLASS,class... PARAMS>
using SubscriberMemberConstFunctionPTRWithParams_t = void (CLASS::*)(PARAMS...) const noexcept;
template<class CLASS>
using MemberFunctionPTRWithoutParams_t = void (CLASS::*)() noexcept;
template<class CLASS>
using MemberConstFunctionPTRWithoutParams_t = void (CLASS::*)() const noexcept;
EDS_END_NAMESPACE
#endif
