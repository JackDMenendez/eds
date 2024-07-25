#ifndef TEST_FUNCTION_SELECTION_HPP
#define TEST_FUNCTION_SELECTION_HPP
#include "concept_type.hpp"
#include "custom_gtest.hpp"
#include "test_object_interface.hpp"
#include "test_member.hpp"
#include "test_member_copyable.hpp"
#include "test_member_movable.hpp"
#include "test_member_copyable_movable.hpp"
#include "private/eds_traits.hpp"
#include "private/eds_concepts.hpp"
#include "test_class_forwarding_property.hpp"
#include "test_class_parameter_property.hpp"
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <private/eds_util.hpp>
#include <cassert>

namespace edst {
      #define EDST_SPECIALIZATION_CONCEPT_TYPE m_concept_type
      #define EDST_SPECIALIZATION_TYPE_DECORATION m_type_decoration
      #define EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY m_function_parameter_property
      #define EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY m_class_parameter_property
template <typename... PARAMS> class TestFunctionSelection {
   private:
         template <typename FUNCTIONAL>
              requires eds::a_functional_value<FUNCTIONAL, PARAMS...>
         [[nodiscard("Required result bool True if is allowed, false if not")]] bool
     testMoveSemantics(ConceptType conceptType, std::unique_ptr<FUNCTIONAL> smart_ptr,PARAMS... args) noexcept {
          std::invoke(*smart_ptr, args...);
          return conceptType == ConceptType::a_unique_ptr_functional_value;
     }
         template <typename FUNCTIONAL>
              requires eds::a_functional_value<FUNCTIONAL, PARAMS...>
         [[nodiscard("Required result bool True if is allowed, false if not")]] bool
     testMoveSemantics(ConceptType conceptType, 
                       std::shared_ptr<FUNCTIONAL> smart_ptr, PARAMS... args) noexcept {
          std::invoke(*smart_ptr, args...);
          return smart_ptr.use_count() > 0 && conceptType == ConceptType::a_shared_ptr_functional_value;
     }
     public:
          TestFunctionSelection() noexcept = default;
          ConceptType EDST_SPECIALIZATION_CONCEPT_TYPE = ConceptType::none;
          ParameterProperty EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::none;
          TypeDecoration EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
          ParameterProperty EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
          
          template <typename FUNCPTR>
               requires eds::a_regular_function_with_RC<FUNCPTR, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCPTR* function_pointer, PARAMS... args) noexcept {
               using type_checker = eds::FunctionTypeChecker<FUNCPTR>; 
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               #pragma message(EDS_FATAL(__FILE__,__LINE__,EDS_2003()))
               return ConceptType::a_regular_function_rc == conceptType;
          }
          template <typename FUNCPTR>
               requires eds::a_regular_function_except_rc<FUNCPTR, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCPTR* function_pointer, PARAMS... args) noexcept {
               using type_checker = eds::FunctionTypeChecker<FUNCPTR>; 
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               return ConceptType::a_regular_function_except_rc == conceptType;
          }
          template <typename FUNCPTR>
               requires eds::a_regular_function_except<FUNCPTR, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCPTR* function_pointer, PARAMS... args) noexcept {
               using type_checker = eds::FunctionTypeChecker<FUNCPTR>; 
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               return ConceptType::a_regular_function_except == conceptType;
          }
          template <typename FUNCPTR>
               requires eds::a_regular_function<FUNCPTR, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCPTR* function_pointer, PARAMS... args) noexcept {
               using type_checker = eds::FunctionTypeChecker<FUNCPTR>; 
               assert(function_pointer != nullptr);
               static_assert(std::is_function_v<std::remove_pointer_t<decltype(function_pointer)>> == true);
               static_assert(std::is_same_v<FUNCPTR,eds::SubscriberFunctionWithParams_t<PARAMS...>> == true);
               static_assert(std::is_same_v<decltype(function_pointer),eds::SubscriberFunctionPTRWithParams_t<PARAMS...>> == true);
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::pointer;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               (*function_pointer)(args...);
               return conceptType == ConceptType::a_regular_function;
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, FUNCTIONAL &functional, PARAMS... args) noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::lvalue;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               std::invoke(functional,args...);
               return conceptType == ConceptType::a_functional_lvalue;
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, FUNCTIONAL &&functional,PARAMS... args) noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::rvalue;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               std::invoke(functional,args...);
               return conceptType == ConceptType::a_functional_rvalue;
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<FUNCTIONAL> &smart_ptr, PARAMS... args) noexcept {
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::lvalue;
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::unique_ptr;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               return testMoveSemantics(conceptType, std::move(smart_ptr),args...);
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<FUNCTIONAL> &&smart_ptr, PARAMS... args) noexcept {
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::unique_ptr;
               return testMoveSemantics(conceptType, std::move(smart_ptr));
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<FUNCTIONAL> &smart_ptr, PARAMS... args) noexcept {
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::shared_ptr;
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::lvalue;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               assert(smart_ptr.use_count() == 1);
               return testMoveSemantics(conceptType, std::move(smart_ptr),args...);
          }
          template<typename FUNCTIONAL>
               requires eds::a_functional_value<FUNCTIONAL,PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]] 
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<FUNCTIONAL> &&smart_ptr, PARAMS... args) noexcept {
               EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY = ParameterProperty::rvalue;
               EDST_SPECIALIZATION_TYPE_DECORATION = TypeDecoration::shared_ptr;
               EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY = ParameterProperty::none;
               EDST_SPECIALIZATION_CONCEPT_TYPE = conceptType;
               assert(smart_ptr.use_count() == 1);
               return testMoveSemantics(conceptType, std::move(smart_ptr),args...);
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS* instance, FUNCPTR function_pointer) noexcept {
               (instance->*function_pointer)(ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<CLASS>& instance, FUNCPTR function_pointer) noexcept {
               (instance.get()->*function_pointer)(ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<CLASS>&& instance, FUNCPTR function_pointer) noexcept {
               (instance.get()->*function_pointer)(ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<CLASS>& instance, FUNCPTR function_pointer) noexcept {
               (instance.get()->*function_pointer)(ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<CLASS>&& instance, FUNCPTR function_pointer) noexcept {
               (instance.get()->*function_pointer)(ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS* instance, std::_Mem_fn<FUNCPTR>& function_pointer) noexcept {
               function_pointer(instance,ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS& instance, std::_Mem_fn<FUNCPTR>& function_pointer) noexcept {
               function_pointer(instance,ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS& instance, std::_Mem_fn<FUNCPTR>&& function_pointer) noexcept {
               function_pointer(instance,ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS&& instance, std::_Mem_fn<FUNCPTR>& function_pointer) noexcept {
               function_pointer(instance,ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }
          template <class CLASS, typename FUNCPTR>
               requires eds::a_member_function_pointer<CLASS, FUNCPTR, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS&& instance, std::_Mem_fn<FUNCPTR>&& function_pointer) noexcept {
               function_pointer(instance,ConceptType::a_member_function_pointer);
               return ConceptType::a_member_function_pointer == conceptType;
          }

          ~TestFunctionSelection() noexcept = default;
     };
     /**
      * @brief A class that allows testing of concepts for function with parameters.
      *
      * @details A series of template functions are used to test the concepts of a function
      * in private/eds_concepts.hpp. The functions in this class are called with a parameter
      * of the ConceptType. The ConceptType is set by the function that is called and tested
      * by the Unit Test Case via a probe.
      *
      * The following concepts are tested:
      *
      * - eds::a_regular_function_pointer
      * - eds::a_functional_lvalue
      * - eds::a_lambda_rvalue
      *
      */
     template <> class TestFunctionSelection<> {
        public:
          using FunctionWithoutParams_t = void (*)() noexcept;
          template<class CLASS>
          using MemberFunctionWithoutParams_t = void (CLASS::*)() noexcept;
          template<class CLASS>
          using MemberConstFunctionWithoutParams_t = void (CLASS::*)() const noexcept;
          /// @brief The test result attribute which can be used to test that a function was
          /// called properly that is either a member function or a lambda that captured this.
          ConceptType m_test_result = ConceptType::none;
          TestFunctionSelection() noexcept = default;
          // clang-format off
          /**
           * @brief Require concept eds::a_regular_function_pointer to capture a static member
           * function or global function that has one or more parameters.
           *
           * A function meeting the requirement constraint is passed to this function. The
           * function passed in is called with a parameter of the ConceptType that is 
           * specific to this method and can be tested by a probe in the test case body.
           * 
           * @tparam FUNCPTR The function pointer type should be of a form like
           * `void(*)(PARAMS...)`
           * 
           * @param function_pointer The function pointer that will be called with the 
           * ConceptType. The pointer is provided by the test case which, through template 
           * specialization picks this template.
           * 
           * @anchor UT010100_setConceptResult "TestFunctionSelection<ConceptsFT::ConceptType>::setConceptResult"
           * @sa UT010200
           * @sa edsUGTest.ConceptsFT.UT010100
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_regular_function_pointer
           * @sa ConceptType::a_regular_function_pointer
           * @sa table_test_concepts_coverage
           */
          // clang-format on
          template <typename FUNCPTR>
               requires eds::a_regular_function_pointer_without_params<FUNCPTR>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCPTR *function_pointer) noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer();
               return true;
          }
          /**
           * @brief Require concept eds::a_functional_lvalue with a function that has
           * parameters.
           *
           * @details A std::function meeting the requirement constraint is passed to this
           * function. The function passed in is called with a parameter of the ConceptType
           * that is specific to this method and can be tested by a probe in the test case
           * body.
           *
           * @tparam FUNCTIONAL The std::function lvalue type should be of a form like
           * `std::function<void(*)(PARAMS...)>`
           *
           * @param functional The std::function that will be called with the ConceptType. The
           * std::function is provided as an rvalue by the test case which, through template
           * specialization picks this template.
           *
           * @anchor UT010105_setConceptResult
           * @sa UT010105
           * @sa UT010115
           * @sa edsUGTest.ConceptsFT.UT010205
           * @sa edsUGTest.ConceptsFT.UT010215
           * @sa edsUGTest.ConceptsFT.UT010225
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_functional_lvalue
           * @sa ConceptType::a_functional_lvalue
           */
          template <typename FUNCTIONAL>
               requires eds::a_functional_lvalue_without_params<FUNCTIONAL>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, FUNCTIONAL &functional) noexcept {
               functional();
               return true;
          }
          /**
           * @brief Require concept eds::a_lambda_functor.
           *
           * @details A lambda functor meeting the requirement constraint is passed to this
           * function. The lambda passed in is called with a parameter of the ConceptType that
           * is specific to this method and can be tested by a probe in the test case body
           *
           * @tparam LAMBDA The lambda lvalue type should be of a form like `<void(PARAMS...)>
           * noexcept`
           *
           * @param lambda The lambda that will be called with the ConceptType. The lambda
           * is provided as an rvalue by the test case which, through template specialization
           * picks this template.
           *
           * @anchor UT010110_setConceptResult
           * @sa UT010210
           * @sa UT010220
           * @sa edsUGTest.ConceptsFT.UT010210
           * @sa edsUGTest.ConceptsFT.UT010220
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_lambda_rvalue
           * @sa ConceptType::a_lambda_rvalue
           */
          template <typename LAMBDA>
               requires eds::a_lambda_rvalue_without_params<LAMBDA>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, LAMBDA &&lambda) noexcept {
               lambda();
               return true;
          }
          template <typename LAMBDA>
               requires eds::a_lambda_lvalue_without_params<LAMBDA>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, LAMBDA &lambda) noexcept {
               lambda();
               return true;
          }
          /**
           * @brief Require concept eds::a_member_function_pointer.
           *
           * @details A class method meeting the requirement constraint is passed to this
           * function. The method passed in is called with a parameter of the ConceptType that
           * is specific to this method and can be tested by a probe in the test case body
           *
           * @tparam CLASS The class type should be a struct or class
           * @tparam METHOD The class method pointer type should be of a form like
           * `<void(PARAMS...) noexcept> noexcept`
           *
           * @param object The object that the method will be called on.
           * @param method The method that will be called with the ConceptType. The method
           * is provided as a pointer by the test case which, through template specialization
           * picks this template.
           *
           * @anchor UT010130_setConceptResult
           * @sa UT010130
           * @sa edsUGTest.ConceptsFT.UT010130
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_member_function_pointer
           * @sa ConceptType::a_member_function_pointer
           */
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD> &&
                        eds::some_class_type<CLASS> && eds::noncopyable<CLASS> && 
                        eds::nonmovable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS *object_pointer,
                                METHOD member_function_pointer) noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object_pointer->*member_function_pointer)();
               return true;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD> && eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<CLASS> &object_pointer,
                                METHOD member_function_pointer) noexcept {
               (object_pointer.get()->*member_function_pointer)();
               return true;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD> && eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<CLASS> &object_pointer,
                                METHOD member_function_pointer) noexcept {
               (object_pointer.get()->*member_function_pointer)();
               return true;
          }
          /**
           * @brief Require concept eds::a_functional_lvalue for a class method.
           *
           * @details A class method meeting the requirement constraint is passed to this
           * function. The method is encapsulated in a std::function and is called with a
           * class object.
           *
           * The std::function is called with a parameter of the ConceptType that is specific
           * constraint tested here. The ConceptType can be tested by a probe in the test case.
           *
           * @tparam CLASS The class type should be a struct or class whose instance will be
           * passed to the method.
           * @tparam METHOD The class method pointer type should be of a form like
           * `CLASS::void(*)() noexcept`.
           *
           * \param object pointer to the object that the method will be called on.
           * \param method std::function encapsulating the class method
           */
          template <class CLASS, typename METHOD>
               requires eds::a_functional_member_lvalue_without_params<METHOD,CLASS> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, CLASS *object, METHOD method) noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               method(object);
               return true;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_member_lvalue_without_params<METHOD,CLASS> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::unique_ptr<CLASS> &object, METHOD method) noexcept {
               method(object.get());
               return true;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_member_lvalue_without_params<METHOD,CLASS> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, std::shared_ptr<CLASS> &object, METHOD method) noexcept {
               method(object.get());
               return true;
          }
          /**
           * @brief Require concept eds::a_member_function_pointer for a const class method.
           *             
           * @details A const class method meeting the requirement constraint is passed to this
           * function. The method is encapsulated in a std::function and is called with a
           * class object
           * .
           *              
           * The std::function is called with a parameter of the ConceptType that is specific
           * constraint tested here. The ConceptType can be tested by a probe in the test case.
           *              
           * @tparam CLASS The class type should be a struct or class whose instance will be
           * passed to the method.
           * @tparam METHOD The class method pointer type should be of a form like
           * `void(CLASS::*)() const noexcept`.
           *              
           * @param object pointer to the object that the method will be called on.
           * @param method std::function encapsulating the class method
           */
          template <class CLASS, typename FUNC>
               requires eds::a_const_member_function_pointer_without_params<CLASS, FUNC> &&
                        eds::some_class_type<CLASS> && eds::noncopyable<CLASS> && 
                        eds::nonmovable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(ConceptType conceptType, const CLASS *object, FUNC f) noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object->*f)();
               return true;
          }

          ~TestFunctionSelection() noexcept = default;
     };
} // namespace edst
#endif // TEST_FUNCTION_SELECTION_HPP
