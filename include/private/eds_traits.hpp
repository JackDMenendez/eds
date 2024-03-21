#ifndef TRAITS_HPP
#define TRAITS_HPP
#include "eds_util.hpp"
#include <tuple>
#include <type_traits>
EDS_BEGIN_NAMESPACE
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
