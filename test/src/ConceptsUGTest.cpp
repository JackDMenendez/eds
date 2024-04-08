/**
 *
 * @file ConceptsUGTest.cpp
 * @brief  Implement Unit Concepts Testing
 * @details This file contains the implementation of the unit tests for the concepts
 * including tests @sa UT010100, @sa UT010105, @sa UT010110, @sa UT010115, and @sa UT010120.
 * @author Joaquín "Jack" D. Menéndez
 * @date   March 2024
 * @todo Allow only smart pointers to the object for member functions and lambdas, also make for object pointers we can give a message via static assert
 */
#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_concepts.hpp"
#include <functional>
#include <memory>
#include <private/eds_env.hpp>
#include <type_traits>
#define UNIT_TEST_010100 UT010100
#define UNIT_TEST_010105 UT010105
#define UNIT_TEST_010110 UT010110
#define UNIT_TEST_010115 UT010115
#define UNIT_TEST_010120 UT010120
#define UNIT_TEST_010125 UT010125
#define UNIT_TEST_010130 UT010130
#define UNIT_TEST_010135 UT010135
#define UNIT_TEST_010140 UT010140
#define UNIT_TEST_010200 UT010200
#define UNIT_TEST_010205 UT010205
#define UNIT_TEST_010210 UT010210
#define UNIT_TEST_010215 UT010215
#define UNIT_TEST_010220 UT010220
#define UNIT_TEST_010225 UT010225
#define UNIT_TEST_010230 UT010230
#define UNIT_TEST_010235 UT010235
#define UNIT_TEST_010240 UT010240
#if 0
#endif
/**
 * @brief A fixture class for testing concepts
 *
 * @details The fixture class is used to test the concepts in the EDS library. The fixture
 * class inherits from the Google Test Fixture class and provides a set of functions that can
 * be used to test the concepts in the EDS library. The fixture class is used to test the
 * concepts in the eds_concepts.hpp file. The fixture class provides a set of functions that
 * can be used to test each concept in the EDS library. The fixture class is used to test the
 * concepts in the EDS by specialization via the template parameter and the concept type. Each
 * of the unit tests in this file are of the TEST_F type and therefore inherit from this
 * fixture class.
 *
 * Custom testing macros EDS_DCL_GTEST_INTERNALS and EDS_IMPL_GTEST_INTERNALS are used to
 * declare the unit test class and implement the unit test class respectively in place of
 * GTEST_F. This allows us to document each test case with a unique test id and description as
 * each test case is a unique class. The macros make the test case type name visible to doxygen
 * allowing a better level of documentation.
 */
class ConceptsFT : public ::testing::Test {
   public:
     /** @brief enumerated types of functions for probes to test. */
     enum class ConceptType : int {
          a_regular_function_pointer,                ///< A global or static function
          a_regular_function_pointer_without_params, ///< A global or static function with no
                                                     ///< parameters
          a_functional_lvalue,                       ///< A std::function
          a_functional_lvalue_without_parameters,    ///< A std::function
          a_lambda_rvalue,                           ///< A lambda functor
          a_lambda_rvalue_without_parameters,        ///< A lambda functor
          a_member_function_pointer,                 ///< A a_member_function_pointer function
          a_member_function_pointer_without_parameters, ///< A a_member_function_pointer function
          const_member, ///< A const a_member_function_pointer function
          a_const_member_function_pointer_without_parameters, ///< A const a_member_function_pointer function
          none          ///< No function type
     };
     ConceptsFT() noexcept = default;
     ~ConceptsFT() noexcept override = default;
     /**
      * @brief Set up the test case
      *
      * @details The test case sets the concept type to none and the function called to false
      * before each test case runs.
      *
      */
     void SetUp() override {
          sm_ConceptType = ConceptType::none;
          sm_FunctionCalled = false;
     }
     void TearDown() override {
          // Nothing to do so far
     }
     static ConceptType sm_ConceptType;
     static bool sm_FunctionCalled;
     /**
      * @brief A static function that can be passed as a function pointer or std::function
      *
      * @param p_concept_type The concept that can be set and tested to make sure this function
      * is routed to the proper caller.
      */
     static void testAMemberPointer(ConceptType p_concept_type) noexcept {
          sm_FunctionCalled = true;
          sm_ConceptType = p_concept_type;
     }
     /**
      * @brief A static function that can be passed as a function pointer or std::function
      */
     static void testAMemberPointerNoParams() noexcept {
          sm_FunctionCalled = true;
          sm_ConceptType = ConceptType::a_regular_function_pointer_without_params;
     }
     using TestFunction_t = void(ConceptType) noexcept;
     class TestMember {
          bool m_member = false;
          mutable bool m_const_member = false;

        public:
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void testAMemberPointer(ConceptType concept_type) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = concept_type;
               m_member = true;
          }
          void setRegularFunctionConst(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void setRegularFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void setRegularFunctionNoParamsConst() const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_const_member_function_pointer_without_parameters;
               m_const_member = true;
          }
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
      * @tparam PARAMS The parameters to the function types accepted by this class
      */
     template <typename... PARAMS> class TestRegularFunctions {
        public:
          /// @brief The test result attribute which can be used to test that a function was
          /// called properly that is either a member function or a lambda that captured this.
          ConceptType m_test_result = ConceptType::none;
          TestRegularFunctions() noexcept = default;
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
           * @anchor UT010100_setConceptResult "TestRegularFunctions<ConceptsFT::ConceptType>::setConceptResult"
           * @sa UT010100
           * @sa edsUGTest.ConceptsFT.UT010100
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_regular_function_pointer
           * @sa ConceptType::a_regular_function_pointer
           * @sa table_test_concepts_coverage
           */
          // clang-format on
          template <typename FUNCPTR>
               requires eds::a_regular_function_pointer<FUNCPTR, PARAMS...>
          void setConceptResult(FUNCPTR *function_pointer) const noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer(ConceptType::a_regular_function_pointer);
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
           * @sa edsUGTest.ConceptsFT.UT010105
           * @sa edsUGTest.ConceptsFT.UT010115
           * @sa edsUGTest.ConceptsFT.UT010125
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_functional_lvalue
           * @sa ConceptType::a_functional_lvalue
           */
          template <typename FUNCTIONAL>
               requires eds::a_functional_lvalue<FUNCTIONAL, PARAMS...>
          void setConceptResult(FUNCTIONAL &functional) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               functional(ConceptType::a_functional_lvalue);
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
           * @sa UT010110
           * @sa UT010120
           * @sa edsUGTest.ConceptsFT.UT010110
           * @sa edsUGTest.ConceptsFT.UT010120
           * @sa unit_test_concepts_page
           * @sa Test
           * @sa eds::a_lambda_rvalue
           * @sa ConceptType::a_lambda_rvalue
           */
          template <typename LAMBDA>
               requires eds::a_lambda_rvalue<LAMBDA, PARAMS...>
          void setConceptResult(LAMBDA &&lambda) const noexcept {
               /// @details call the lambda passing the ConceptType that will be tested
               lambda(ConceptType::a_lambda_rvalue);
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
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...>
          void setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
               (object_pointer->*member_function_pointer)(
                   ConceptType::a_member_function_pointer);
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
           * `CLASS::void(*)(PARAMS...) noexcept`.
           *
           * \param object pointer to the object that the method will be called on.
           * \param method std::function encapsulating the class method
           */
          template <class CLASS, typename METHOD>
               requires eds::a_functional_lvalue<METHOD, CLASS, PARAMS...> &&
                        eds::some_class_type<CLASS>
          void setConceptResult(CLASS *object, METHOD &method) const noexcept {
               method(object, ConceptType::a_functional_lvalue);
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
           * `CLASS::void(*)(PARAMS...) const noexcept`.
           *              
           * @param object pointer to the object that the method will be called on.
           * @param method std::function encapsulating the class method
           */
          template <class CLASS, typename FUNC>
               requires eds::a_const_member_function_pointer<CLASS, FUNC, PARAMS...>
          void setConceptResult(const CLASS *object, FUNC f) const noexcept {
               (object->*f)(ConceptType::a_member_function_pointer);
          }
          template <typename FUNC>
               requires eds::a_lambda_lvalue<FUNC, PARAMS...>
          void setConceptResult(FUNC &func) const noexcept {
               func(ConceptType::LambdaLValue);
          }

          ~TestRegularFunctions() noexcept = default;
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
     template <> class TestRegularFunctions<> {
        public:
          /// @brief The test result attribute which can be used to test that a function was
          /// called properly that is either a member function or a lambda that captured this.
          ConceptType m_test_result = ConceptType::none;
          TestRegularFunctions() noexcept = default;
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
           * @anchor UT010100_setConceptResult "TestRegularFunctions<ConceptsFT::ConceptType>::setConceptResult"
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
          void setConceptResult(FUNCPTR *function_pointer) const noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer();
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
          void setConceptResult(FUNCTIONAL &functional) const noexcept {
               functional();
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
          void setConceptResult(LAMBDA &&lambda) const noexcept {
               lambda();
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
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD>
          void setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
               (object_pointer->*member_function_pointer)();
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
          void setConceptResult(CLASS *object, METHOD method) const noexcept {
               method(object);
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
               requires eds::a_const_member_function_pointer_without_params<CLASS, FUNC>
          void setConceptResult(const CLASS *object, FUNC f) const noexcept {
               (object->*f)();
          }
          template <typename FUNC>
               requires eds::a_lambda_lvalue<FUNC>
          void setConceptResult(FUNC &func) const noexcept {
               func(ConceptType::LambdaLValue);
          }

          ~TestRegularFunctions() noexcept = default;
     };
     };
ConceptsFT::ConceptType ConceptsFT::sm_ConceptType = ConceptType::none;
bool ConceptsFT::sm_FunctionCalled = false;
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010100
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult
 using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010100

@anchor edsUGTest.ConceptsFT.UT010100

@test Test Explorer: edsUGTest->ConceptsFT->UT010100
@ref edsUGTest.ConceptsFT.UT010100

@sa UT010100_setConceptResult

The targeted function if the test case is successful:
@sa UT010100_setConceptResult
which is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010100
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
@sa UT010100_setConceptResult
 */
class ConceptsFT_UT010100_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010100);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010100);
void ConceptsFT_UT010100_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(ConceptsFT::testAMemberPointer);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_regular_function_pointer));
}
#endif // UNIT_TEST_010100
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010105
/**
 @brief Tests the concept eds::a_regular_function_pointer against
 ConceptsFT::setConceptResult using function ConceptsFT::testAMemberPointer test
 ConceptsFT.UT010105

@anchor edsUGTest.ConceptsFT.UT010105

@test Test Explorer: edsUGTest->ConceptsFT->UT010105
@ref edsUGTest.ConceptsFT.UT010105

@sa UT010105_setConceptResult

[The targeted function if the test case is successful](@ref UT010105_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010105
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
class ConceptsFT_UT010105_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010105);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010105);
void ConceptsFT_UT010105_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     // create a std::function<void()> from a static member function with parameters
     std::function<void(ConceptType)> f(ConceptsFT::testAMemberPointer);
     // go through the specialization for to call the std::function, this is what we are testing
     testFunctions.setConceptResult(f);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif // UNIT_TEST_010105
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010110
/**
 @brief Tests the concept eds::a_lambda_rvalue against
 ConceptsFT::setConceptResult using inline lambda to test
 ConceptsFT.UT010110

@anchor edsUGTest.ConceptsFT.UT010110

@test Test Explorer: edsUGTest->ConceptsFT->UT010110
@ref edsUGTest.ConceptsFT.UT010110

@sa UT010110_setConceptResult

[The targeted function if the test case is successful](@ref UT010110_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010110
@sa unit_test_concepts_page
@sa Test
@sa eds::a_lambda_rvalue
@sa ConceptType
 */
class ConceptsFT_UT010110_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010110);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010110);
void ConceptsFT_UT010110_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult([](ConceptType a) noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = a;
     });
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue));
}
#endif // UNIT_TEST_010110
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010115
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010115

@anchor edsUGTest.ConceptsFT.UT010115

@test Test Explorer: edsUGTest->ConceptsFT->UT010115
@ref edsUGTest.ConceptsFT.UT010115

@sa UT010115_setConceptResult

[The targeted function if the test case is successful](@ref UT010115_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010115
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
class ConceptsFT_UT010115_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010115);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010115);
void ConceptsFT_UT010115_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda = std::move_only_function<void(ConceptType)>(
         [](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
         });
     testFunctions.setConceptResult(lambda);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010120
// clang-format off
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010120

@anchor edsUGTest.ConceptsFT.UT010120

@test Test Explorer: edsUGTest->ConceptsFT->UT010120
@ref edsUGTest.ConceptsFT.UT010120

@sa UT010115_setConceptResult

[The targeted function if the test case is successful](@ref UT010120_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_regular_function_pointer
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_regular_function_pointer

@anchor UT010120
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010120_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010120);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010120);
void ConceptsFT_UT010120_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(
         [&testFunctions](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_lambda_rvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010125
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010125

@anchor edsUGTest.ConceptsFT.UT010125

@test Test Explorer: edsUGTest->ConceptsFT->UT010125
@ref edsUGTest.ConceptsFT.UT010125

@sa UT010105_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010125
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010125_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010125);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010125);
void ConceptsFT_UT010125_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto functional = std::move_only_function<void(ConceptType)>(
         [&testFunctions](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     testFunctions.setConceptResult(functional);
     EDS_PROBEW(000010,
                EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_functional_lvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010130
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010125

@anchor edsUGTest.ConceptsFT.UT010130

@test Test Explorer: edsUGTest->ConceptsFT->UT010130
@ref edsUGTest.ConceptsFT.UT010130

@sa UT010105_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010130
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010130_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010130);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010130);
void ConceptsFT_UT010130_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::testAMemberPointer);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010135
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010125

@anchor edsUGTest.ConceptsFT.UT010135

@test Test Explorer: edsUGTest->ConceptsFT->UT010135
@ref edsUGTest.ConceptsFT.UT010135

@sa UT010105_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a std::function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010135
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010135_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010135);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010135);
void ConceptsFT_UT010135_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     auto functional = std::mem_fn(&ConceptsFT::TestMember::testAMemberPointer);
     testFunctions.setConceptResult(&testMember, functional);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010140
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010140

@anchor edsUGTest.ConceptsFT.UT010140

@test Test Explorer: edsUGTest->ConceptsFT->UT010140
@ref edsUGTest.ConceptsFT.UT010140

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a std::function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010140
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010140_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010140);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010140);
void ConceptsFT_UT010140_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember,
                                    &ConceptsFT::TestMember::setRegularFunctionConst);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
#endif
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010200
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult
 using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010200

@anchor edsUGTest.ConceptsFT.UT010200

@test Test Explorer: edsUGTest->ConceptsFT->UT010200
@ref edsUGTest.ConceptsFT.UT010200

@sa UT010200_setConceptResult

The targeted function if the test case is successful:
@sa UT010200_setConceptResult
which is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010200
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
@sa UT010200_setConceptResult
 */
class ConceptsFT_UT010200_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010200);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010200);
void ConceptsFT_UT010200_Test::TestBody() {
     // instantiate the test class selecting on no parameter to the functions.
     ConceptsFT::TestRegularFunctions<> testFunctions;
     // go through the specialization for to call the std::function, this is what we are testing
     testFunctions.setConceptResult(ConceptsFT::testAMemberPointerNoParams);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_regular_function_pointer_without_params));
}
#endif // UNIT_TEST_010200
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010205
/**
 @brief Tests the concept eds::a_regular_function_pointer against
 ConceptsFT::setConceptResult using function ConceptsFT::testAMemberPointer test
 ConceptsFT.UT010205

@anchor edsUGTest.ConceptsFT.UT010205

@test Test Explorer: edsUGTest->ConceptsFT->UT010205
@ref edsUGTest.ConceptsFT.UT010205

@sa UT010205_setConceptResult

[The targeted function if the test case is successful](@ref UT010205_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010205
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
class ConceptsFT_UT010205_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010205);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010205);
void ConceptsFT_UT010205_Test::TestBody() {
     // instantiate the test class selecting on no parameter to the functions.
     ConceptsFT::TestRegularFunctions<> testFunctions;
     // create a std::function<void()> from a static member function with no parameters
     std::function<void()> f(testAMemberPointerNoParams);
     // go through the specialization for to call the std::function, this is what we are testing
     testFunctions.setConceptResult(f);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_regular_function_pointer_without_params));
}
#endif // UNIT_TEST_010205
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010210
/**
 @brief Tests the concept eds::a_lambda_rvalue against
 ConceptsFT::setConceptResult using inline lambda to test
 ConceptsFT.UT010210

@anchor edsUGTest.ConceptsFT.UT010210

@test Test Explorer: edsUGTest->ConceptsFT->UT010210
@ref edsUGTest.ConceptsFT.UT010210

@sa UT010210_setConceptResult

[The targeted function if the test case is successful](@ref UT010210_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010210
@sa unit_test_concepts_page
@sa Test
@sa eds::a_lambda_rvalue
@sa ConceptType
 */
class ConceptsFT_UT010210_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010210);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010210);
void ConceptsFT_UT010210_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     testFunctions.setConceptResult([]() noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = ConceptType::a_lambda_rvalue_without_parameters;
     });
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue_without_parameters));
}
#endif // UNIT_TEST_010210
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010215
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010215

@anchor edsUGTest.ConceptsFT.UT010215

@test Test Explorer: edsUGTest->ConceptsFT->UT010215
@ref edsUGTest.ConceptsFT.UT010215

@sa UT010215_setConceptResult

[The targeted function if the test case is successful](@ref UT010215_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010215
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
class ConceptsFT_UT010215_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010215);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010215);
void ConceptsFT_UT010215_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     auto lambda = std::move_only_function<void() noexcept>(
         []() noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
         });
     testFunctions.setConceptResult(lambda);
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue_without_parameters));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010220
// clang-format off
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010220

@anchor edsUGTest.ConceptsFT.UT010220

@test Test Explorer: edsUGTest->ConceptsFT->UT010220
@ref edsUGTest.ConceptsFT.UT010220

@sa UT010215_setConceptResult

[The targeted function if the test case is successful](@ref UT010220_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_regular_function_pointer
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_regular_function_pointer

@anchor UT010220
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010220_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010220);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010220);
void ConceptsFT_UT010220_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     testFunctions.setConceptResult(
         [&testFunctions]() noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_lambda_rvalue_without_parameters;
              testFunctions.m_test_result = ConceptType::a_lambda_rvalue_without_parameters;
         });
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue_without_parameters));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010225
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010225

@anchor edsUGTest.ConceptsFT.UT010225

@test Test Explorer: edsUGTest->ConceptsFT->UT010225
@ref edsUGTest.ConceptsFT.UT010225

@sa UT010205_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010225
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010225_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010225);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010225);
void ConceptsFT_UT010225_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     auto functional = std::move_only_function<void() noexcept>(
         [&testFunctions]() noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
              testFunctions.m_test_result = ConceptType::a_functional_lvalue_without_parameters;
         });
     testFunctions.setConceptResult(functional);
     EDS_PROBEW(000010,
                EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_functional_lvalue_without_parameters));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue_without_parameters));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010230
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010225

@anchor edsUGTest.ConceptsFT.UT010230

@test Test Explorer: edsUGTest->ConceptsFT->UT010230
@ref edsUGTest.ConceptsFT.UT010230

@sa UT010205_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010230
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010230_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010230);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010230);
void ConceptsFT_UT010230_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunctionNoParams);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010235
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010225

@anchor edsUGTest.ConceptsFT.UT010235

@test Test Explorer: edsUGTest->ConceptsFT->UT010235
@ref edsUGTest.ConceptsFT.UT010235

@sa UT010205_setConceptResult

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a std::function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010235
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010235_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010235);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010235);
void ConceptsFT_UT010235_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     ConceptsFT::TestMember testMember;
     auto functional = std::mem_fn(&ConceptsFT::TestMember::setRegularFunctionNoParams);
     testFunctions.setConceptResult(&testMember, functional);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010240
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010240

@anchor edsUGTest.ConceptsFT.UT010240

@test Test Explorer: edsUGTest->ConceptsFT->UT010240
@ref edsUGTest.ConceptsFT.UT010240

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a std::function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_functional_lvalue
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_functional_lvalue

@anchor UT010240
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010240_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010240);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010240);
void ConceptsFT_UT010240_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember,
                                    &ConceptsFT::TestMember::setRegularFunctionNoParamsConst);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_const_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
#endif
