#ifndef TRAITS_HPP
#define TRAITS_HPP
#include "eds_util.hpp"
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
#define EDS_CREATE_PSUEDO(CHILD, PARENT)                                                                               \
        class CHILD : PARENT {                                                                                         \
            public:                                                                                                    \
                CHILD() = delete;                                                                                      \
                CHILD(const CHILD &) = delete;                                                                         \
                CHILD &operator=(const CHILD &) = delete;                                                              \
                virtual ~CHILD() = 0;                                                                                  \
        }

/**
 * @brief A psuedo return code that is used to indicate that a function does not return a value.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(VoidReturnCode, PSuedoObject);
/**
 * @brief A psuedo parameter list that is used to indicate that a function does not have parameters.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(VoidParams, PSuedoObject);
/**
 * @brief A psuedo object that is used to indicate that a function does not have an object.
 *
 * See @ref edc_traits_psuedo_objects "Psuedo Objects"
 */
EDS_CREATE_PSUEDO(VoidObject, PSuedoObject);
EDS_CREATE_PSUEDO(ConstantSpecification, PSuedoObject);
EDS_CREATE_PSUEDO(ExceptionRegime, PSuedoObject);
EDS_CREATE_PSUEDO(NotConstant, ConstantSpecification);
EDS_CREATE_PSUEDO(Constant, ConstantSpecification);
EDS_CREATE_PSUEDO(YesException, ExceptionRegime);
EDS_CREATE_PSUEDO(NoException, ExceptionRegime);
EDS_CREATE_PSUEDO(ResourceHandlingRegime, PSuedoObject);
EDS_CREATE_PSUEDO(MemberPointer, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(FunctionPointer, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(LambdaRef, ResourceHandlingRegime);
EDS_CREATE_PSUEDO(FunctionType, ResourceHandlingRegime);
template <typename T> struct is_psuedo : public std::false_type { };
template <> struct is_psuedo<VoidReturnCode> : public std::true_type { };
template <> struct is_psuedo<VoidParams> : public std::true_type { };
template <> struct is_psuedo<VoidObject> : public std::true_type { };
template <> struct is_psuedo<ConstantSpecification> : public std::true_type { };
template <> struct is_psuedo<NotConstant> : public std::true_type { };
template <> struct is_psuedo<Constant> : public std::true_type { };
template <> struct is_psuedo<ResourceHandlingRegime> : public std::true_type { };
template <> struct is_psuedo<MemberPointer> : public std::true_type { };
template <> struct is_psuedo<FunctionPointer> : public std::true_type { };
template <> struct is_psuedo<ExceptionRegime> : public std::true_type { };
template <> struct is_psuedo<LambdaRef> : public std::true_type { };
template <> struct is_psuedo<FunctionType> : public std::true_type { };
template <> struct is_psuedo<YesException> : public std::true_type { };
template <> struct is_psuedo<NoException> : public std::true_type { };
template <typename T> constexpr static bool is_psuedo_v = is_psuedo<T>::value;
template <typename T>
constexpr static bool is_constant_specification_v = std::is_base_of<ConstantSpecification, T>::value;
template <typename T> constexpr static bool is_member_pointer_v = std::is_same_v<T, MemberPointer>;
template <typename T> constexpr static bool is_function_pointer_v = std::is_same_v<T, FunctionPointer>;
template <typename T>
constexpr static bool is_resource_handling_regime_v = std::is_base_of_v<ResourceHandlingRegime, T>;
template <typename T> struct is_constant : public std::false_type { };
template <> struct is_constant<Constant> : public std::true_type { };
template <typename T> struct is_noexcept : public std::false_type { };
template <> struct is_noexcept<NoException> : public std::true_type { };
template <typename T> constexpr static bool is_noexcept_v = is_noexcept<T>::value;
template <typename T> constexpr static bool is_constant_v = is_constant<T>::value;
template <typename T> constexpr static bool is_exception_specification_v = std::is_base_of<ExceptionRegime, T>::value;
template <typename T> struct is_void_return_code : public std::false_type { };
template <> struct is_void_return_code<VoidReturnCode> : public std::true_type { };
template <typename T> constexpr static bool is_void_return_code_v = is_void_return_code<T>::value;
EDS_END_NAMESPACE
#endif
