/**
 *
 * @file ConceptsUGTest.cpp
 * @brief  Document and Implement Unit Concepts Testing
 * @details This file contains the implementation of the unit tests for the concepts.
 * @sa unit_test_concepts_page
 * @author Joaquin "Jack" D. Menéndez
 * @date   March 2024
 * See also @ref ConceptsUGTest "Concepts Testing"
 * @todo Allow only smart pointers to the object for member functions and lambdas, also make
 * for object pointers we can give a message via static assert.
 * @todo Add test comment for each test case
 * @todo Finish parameterization of test cases
 * @todo Comment each test case parameter
 */
#if defined(EDSMSVSBUILD)
     #include "pch.h"
#else
     #include "gtest/gtest.h"
#endif
#include "../include/concept_type.hpp"
#include "../include/custom_gtest.hpp"
#include "../include/object_properties.hpp"
#include "../include/test_class_forwarding_property.hpp"
#include "../include/test_class_parameter_property.hpp"
#include "../include/test_function_selection.hpp"
#include "../include/test_member.hpp"
#include "../include/test_member_copyable.hpp"
#include "../include/test_member_copyable_movable.hpp"
#include "../include/test_member_movable.hpp"
#include "../include/test_object_interface.hpp"
#include "custom_gtest.hpp"
#include "function_type.hpp"
#include "private/eds_concepts.hpp"
#include "private/eds_traits.hpp"
#include "private/eds_util.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <private/eds_env.hpp>
#include <type_traits>

/**
 */
/**  Unique ID for this unit test @ref UT010100 */
#define UNIT_TEST_010100 10100
// #define UNIT_TEST_010101  10101
// #define UNIT_TEST_010102  10102
// #define UNIT_TEST_010103  10103
//  #define UNIT_TEST_010104  10104
// #define UNIT_TEST_010105  10105
// #define UNIT_TEST_010106  10106
// #define UNIT_TEST_010107  10107
// #define UNIT_TEST_010108  10108
// #define UNIT_TEST_010109  10109
//  #define UNIT_TEST_010110  10110
//  #define UNIT_TEST_010111  10111
//  #define UNIT_TEST_010112  10112
//  #define UNIT_TEST_010113  10113
//  #define UNIT_TEST_010114  10114
//  #define UNIT_TEST_010115  10115
//  #define UNIT_TEST_010116  10116
//  #define UNIT_TEST_010117  10117
//  #define UNIT_TEST_010120  10120
//  #define UNIT_TEST_010121  10121
//  #define UNIT_TEST_010122  10122
//  #define UNIT_TEST_010123  10123
//  #define UNIT_TEST_010125  10125
//  #define UNIT_TEST_010126  10126
//  #define UNIT_TEST_010127  10127
//  #define UNIT_TEST_010130  10130
//  #define UNIT_TEST_010131  10131
//  #define UNIT_TEST_010132  10132
//  #define UNIT_TEST_010133  10133
//  #define UNIT_TEST_010134  10134
//  #define UNIT_TEST_010135  10135
//  #define UNIT_TEST_010136  10136
//  #define UNIT_TEST_010137  10137
//  #define UNIT_TEST_010140  10140
//  #define UNIT_TEST_010200  10200
//  #define UNIT_TEST_010205  10205
//  #define UNIT_TEST_010210  10210
//  #define UNIT_TEST_010215  10215
//  #define UNIT_TEST_010220  10220
//  #define UNIT_TEST_010225  10225
//  #define UNIT_TEST_010230  10230
//  #define UNIT_TEST_010235  10235
//  #define UNIT_TEST_010240  10240
using namespace edst;
#define EDST_EXPECTED_CONST_FLAG m_expected_const_flag
/** The instance of the class the uses concepts to specialize template functions to a function
 * type  */
#define EDST_SPECIALIZATION m_specialization
#define EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG m_expected_class_function_called_flag
#define EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG m_expected_class_instance_called_flag
/**
 * A
 * @ref flag_definition "flag"
 * that contains the result of specialization.
 *
 * This value is compared to EDST_EXPECTED_SPECIALIZATION.
 *
 * @result true - specialization found an acceptable template function.
 *
 * @result false - specialization found an unacceptable function
 *
 * See also @ref concepts_testing_strategy "Concepts Testing Strategy"
 */
#define EDST_FOUND_SPECIALIZATION m_specialization_found
#define EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY m_expected_function_parameter_property
#define EDST_EXPECTED_CLASS_PARAMETER_PROPERTY m_expected_class_parameter_property
#define EDST_EXPECTED_CONCEPT_TYPE m_expected_concept_type
#define EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY m_expected_function_parameter_property
#define EDST_EXPECTED_PARAMETER_PROPERTY m_expected_function_parameter_property
#define EDST_EXPECTED_TYPE_DECORATION m_expected_type_decoration
#define EDST_EXPECTED_FUNCTION_TYPE m_expected_function_type
#define EDST_EXPECTED_SPECIALIZATION m_expected_specialization
#define EDST_CLASS_FUNCTION_CALLED_FLAG(_CLASS_) _CLASS_::EDST_TEST_MEMBER_FUNCTION_CALLED
#define EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(_CLASS_)                                       \
     _CLASS_::EDST_TEST_MEMBER_INSTANCE_CALLED
#define EDST_CLASS_CONST_FLAG(_CLASS_) _CLASS_::EDST_TEST_MEMBER_CONST_MEMBER
#define EDST_CLASS_CONCEPT_TYPE(_CLASS_) _CLASS_::EDST_TEST_MEMBER_CONCEPT_TYPE
#define EDST_CLASS_FUNCTION_TYPE(_CLASS_) _CLASS_::EDST_TEST_MEMBER_FUNCTION_TYPE
#define EDST_CLASS_TEST_IT(_CLASS_) _CLASS_::EDST_TEST_MEMBER_TEST_ID
/** Use this macro to access the class type containing methods tested against specialization
 * template methods */
#define EDST_CLASS_TYPE class_t
/**
 * Provide the class type to be tested by the specialization, change the parameter to.
 * match the class type providing the static and instance method to be used by the unit
 * test case.
 *
 * @param _CLASS_ - The class type to be tested by the specialization. possible values are:
 *   - TestMember non-copyable and non-movable
 *   - TestMemberCopyable copyable and non-movable
 *   - TestMemberMovable non-copyable and movable
 *   - TestMemberCopyableMovable copyable and movable
 *
 * @return EDST_CLASS_TYPE - a using statement return the type.
 */
#define EDST_DCL_CLASS_TYPE(_CLASS_) using EDST_CLASS_TYPE = _CLASS_;
/**
 * The type of a function being passed to specialization.
 *
 * A specialized version of the templated TestFunction_t returned by EDST_DCL_FUNCTION_TYPE.
 */
#define EDST_FUNCTION_TYPE function_t
/**
 * The type of the selection class that contains the template methods to be specialized.
 *
 * A specialized version of the templated TestFunctionSelection returned by
 * EDST_DCL_FUNCTION_TYPE.
 */
#define EDST_SELECTION_TYPE selection_t
/**
 * Provide the parameters the function type passed to the template method specialization.
 * provided by edst::TestFunctionSelection. This is the form of the test function that
 * drives specialization. Param0,Param1,Param2,... = the parameters of the function type.
 *
 * @param __VA_ARGS__ - The parameters of the function type.
 *
 * @return EDST_FUNCTION_TYPE - The function type to be tested.
 * @return EDST_SELECTION_TYPE - The selection type which contains template functions for
 * specialization to be tested.
 */
#define EDST_DCL_FUNCTION_TYPE(...)                                                           \
     using EDST_FUNCTION_TYPE = TestFunction_t<__VA_ARGS__>;                                  \
     using EDST_SELECTION_TYPE = TestFunctionSelection<__VA_ARGS__>;
/** The class instance passed for specialization */
#define EDST_CLASS_INSTANCE m_instance
/** Generate the class instance within the current scope accessed with EDST_CLASS_INSTANCE */
#define EDST_DEF_CLASS_INSTANCE() EDST_CLASS_TYPE EDST_CLASS_INSTANCE;
/** Declares a flag where the result of specialization is stored, EDST_FOUND_SPECIALIZATION */
#define EDST_DCL_FOUND_SPECIALIZATION() bool EDST_FOUND_SPECIALIZATION = false;
#define EDST_DCL_EXPECTED_SPECIALIZATION(EX)                                                  \
     static constexpr bool EDST_EXPECTED_SPECIALIZATION = EX;
/**
 * Expected const flag will be compared to EDST_CLASS_CONST_FLAG.
 *
 * The original function may or may not have the const keyword. For example the method Bar() in
 * the example below is a const function and the parameter EXVAL should be set to true. Always
 * expect false for static functions.
 * @code {.cpp}
 *     class Foo
 *     {
 *        public:
 *          int Bar(int random_arg) const {
 *              // code
 *          }
 *     };
 * @endcode
 * @param EXVAL the expected constness detected by specialization.
 * - _true_ The function is expected to be found const member function.
 * - _false_ The function is not expected to be a const member function.
 * @returns declared boolean flag initialized with the expected constness of the function
 * accessed via the macro EDST_EXPECTED_CONST_FLAG.
 *
 * _see also_ EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG
 */
#define EDST_DCL_EXPECTED_CONST_FLAG(EXVAL)                                                   \
     static constexpr bool EDST_EXPECTED_CONST_FLAG = EXVAL;
/** Create an instance of the EDST_SELECTION_TYPE, the instance can be accessed with
 * EDST_SPECIALIZATION macro */
#define EDST_DCL_SPECIALIZATION_INSTANCE() EDST_SELECTION_TYPE EDST_SPECIALIZATION;
#define EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(EXVAL)                                   \
     const bool EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG = EXVAL;
#define EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(EXVAL)                                   \
     const bool EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG = EXVAL;
#define EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(PP)                                     \
     const ParameterProperty EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY = PP;
#define EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(PP)                                        \
     const ParameterProperty EDST_EXPECTED_CLASS_PARAMETER_PROPERTY = PP;
#define EDST_DCL_EXPECTED_CONCEPT_TYPE(CT) const ConceptType EDST_EXPECTED_CONCEPT_TYPE = CT;
#define EDST_DCL_EXPECTED_TYPE_DECORATION(CM)                                                 \
     const TypeDecoration EDST_EXPECTED_TYPE_DECORATION = CM;
#define EDST_DCL_EXPECTED_FUNCTION_TYPE(FT)                                                   \
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FT;
#define EDST_TEST_SPECIALIZATION(CONCEPT, FUNCTION, ...)                                      \
     EDS_INFO(TRACE) << "test id: " << EDS_EXPECTED_TEST_ID                                   \
                     << " function : " << typeid(decltype(FUNCTION)).name() << EDS_EOL();     \
     EDST_FOUND_SPECIALIZATION =                                                              \
         EDST_SPECIALIZATION.setConceptResult(CONCEPT, FUNCTION, __VA_ARGS__);
#define EDST_TEST_SPECIALIZATION_FORWARD(CONCEPT, FUNCTION, ...)                              \
     EDS_INFO(TRACE) << "test id: " << EDS_EXPECTED_TEST_ID                                   \
                     << " function : " << typeid(decltype(FUNCTION)).name() << EDS_EOL();     \
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(                   \
         CONCEPT, std::forward<decltype(FUNCTION)>(FUNCTION), __VA_ARGS__);
#define EDST_UT_LOCAL_SETUP()                                                                 \
     EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE) = false;                                \
     EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE) = false;                         \
     EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE) = false;                                          \
     EDST_CLASS_TYPE::EDST_TEST_MEMBER_CONCEPT_TYPE = ConceptType::none;                      \
     EDST_CLASS_TYPE::EDST_TEST_MEMBER_FUNCTION_TYPE = FunctionType::none;                    \
     EDST_CLASS_TYPE::EDST_TEST_MEMBER_REQUESTED_CONCEPT_TYPE = ConceptType::none;            \
     EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID = 0;                                           \
     EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY =                    \
         ParameterProperty::none;                                                             \
     EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY =                       \
         ParameterProperty::none;                                                             \
     EDST_SPECIALIZATION.EDST_SPECIALIZATION_CONCEPT_TYPE = ConceptType::none;
/**
 * Concepts Test Fixture for Google Test.
 *
 * Drive individual unit test setup and tear down and declare the root function type,
 * TestFunction_t, to which all functions tested can be converted to.
 *
 * A Google Test Fixture is a class that inherits from ::testing::Test. The fixture provides
 * a framework for writing tests. The fixture provides a SetUp and TearDown method that drive
 * custom UnitTestSetUp and UnitTestTearDown methods. The fixture provides a TestBody method
 * in which the tests are written by inheriting specialized test cases.
 *
 * Each test case has a unique test fixture that is derived from ConceptsFT. The test fixture
 * provides the SetUp and TearDown methods
 */
class ConceptsFT : public ::testing::Test {
   public:
     ConceptsFT() noexcept = default;
     ~ConceptsFT() noexcept override = default;
     virtual void UnitTestSetUp() = 0;
     virtual void UnitTestTearDown() = 0;
     void SetUp() override { UnitTestSetUp(); }
     void TearDown() override { UnitTestTearDown(); }
     template <typename... PARAMS> using TestFunction_t = void(PARAMS...) noexcept;
};
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010100
/**
 * A Google Unit Test that validates specialization of static functions. This class together
 * with the implementation of the TestBody function below makeup a Google Test Unit Test.
 *
 * This class is a Google Test Fixture that inherits the common test fixture class ConceptsFT.
 * This class is similar to what the Google Test framework generates when using the TEST_F.
 *
 * Please see unit test description @ref UT010100.
 *
 * @test UT010100 Test that a pointer to a static function,
 * ConceptsFT::StaticMember is selected by a template member of
 * TestFunctionSelection<ConceptType,int>::setConceptResult using the concept
 * eds::a_regular_function. The static function is passed as an address in a pointer.
 */
class ConceptsFT_UT010100_Test : public ConceptsFT {
     // Order is important, the following macros must be in the order shown.
     EDST_DCL_CLASS_TYPE(TestMember)
     EDST_DCL_FUNCTION_TYPE(ConceptType, int)
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010100, UNIT_TEST_010100)
     EDST_DEF_CLASS_INSTANCE()
     EDST_DCL_SPECIALIZATION_INSTANCE()
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     // Expected Class function was called. Tested against EDST_CLASS_FUNCTION_CALLED_FLAG.
     //
     // Param0 - boolean flag expected function called.
     //
     // false - expect that this function is not accommodated or function is static.
     //
     // true - expect the function is accommodated and called on class instance.
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     // Expected class instance specializes properly, test against
     // EDST_CLASS_FUNCTION_CALLED_FLAG
     //
     // Param0 - boolean flag expected instance was specialized and called properly.
     //
     // true - expected class was used in a call
     //
     // false - expect specialization to fail and no call takes place
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     // Expected specialization flag, tested against EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG
     //
     // Param0 - boolean flag expected specialization to succeed
     //
     // true - expect specialization to succeed
     //
     // false - expect specialization to fail
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     // Expected type decoration, tested against EDST_SPECIALIZATION_TYPE_DECORATION
     //
     // Param0 - TypeDecoration enumeration
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     // Expected function parameter property, tested against
     // EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY
     //
     // Param0 - ParameterProperty enumeration
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::pointer)
     // Expected class parameter property, tested against
     // EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY
     //
     // Param0 - ParameterProperty enumeration
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     // Expected concept type, tested against EDST_CLASS_CONCEPT_TYPE
     //
     // Param0 - ConceptType enumeration
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_regular_function)
     // Expected function type, tested against EDST_CLASS_FUNCTION_TYPE
     //
     // Param0 - FunctionType enumeration
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
   public:
     void UnitTestSetUp() override {
          EDST_UT_LOCAL_SETUP()
          // Runs the test specialization
          EDST_TEST_SPECIALIZATION(
              EDST_EXPECTED_CONCEPT_TYPE,
              &EDST_CLASS_TYPE::StaticMemberWithParams, // Function passed in
              EDST_EXPECTED_CONCEPT_TYPE, EDS_EXPECTED_TEST_ID)
     }
     void UnitTestTearDown() override { /* nothing to do yet */ }
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010100);
void ConceptsFT_UT010100_Test::TestBody() {
     EDST_PROBE(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_EQ(EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG,
                                  EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000020, EXPECT_EQ(EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG,
                                  EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000030,
                EXPECT_EQ(EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000040, EXPECT_EQ(EDST_CLASS_CONCEPT_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000050, EXPECT_EQ(EDST_CLASS_FUNCTION_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(
         000060,
         EXPECT_EQ(EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY,
                   EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY));
     EDS_PROBEW(000070,
                EXPECT_EQ(EDST_EXPECTED_CLASS_PARAMETER_PROPERTY,
                          EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY));
     EDS_PROBEW(000080,
                EXPECT_EQ(EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID, EDS_EXPECTED_TEST_ID));
     EDS_PROBEW(000090, EXPECT_EQ(EDST_SPECIALIZATION.EDST_SPECIALIZATION_TYPE_DECORATION,
                                  EDST_EXPECTED_TYPE_DECORATION));
}
#endif // UNIT_TEST_010100
//--------------------------------------------------------------------------------------------
/**
 * @test ConceptsFT_UT010101_TEST Test that a pointer to a static function,
 * ConceptsFT::StaticMember is selected by a template member of
 * TestFunctionSelection<ConceptType,int>::setConceptResult using the concept
 * eds::a_regular_function. The static function is passed as an address in a pointer.
 */
#ifdef UNIT_TEST_010101
class ConceptsFT_UT010101_Test : public ConceptsFT {
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010101, UNIT_TEST_010101)
     void TestBody() override;
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::pointer)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_regular_function_except)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010101);
void ConceptsFT_UT010101_Test::TestBody() {
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE,
                              &EDST_CLASS_TYPE::StaticMemberWithoutNoexcept,
                              EDST_EXPECTED_CONCEPT_TYPE, EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
}
#endif // UNIT_TEST_010100
//--------------------------------------------------------------------------------------------
/**
 * @test ConceptsFT_UT010102_TEST Test that a pointer to a static function,
 * ConceptsFT::StaticMember is selected by a template member of
 * TestFunctionSelection<ConceptType,int>::setConceptResult using the concept
 * eds::a_regular_function. The static function is passed as an address in a pointer.
 */
#ifdef UNIT_TEST_010102
class ConceptsFT_UT010102_Test : public ConceptsFT {
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010102, UNIT_TEST_010102)
     void TestBody() override;
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::pointer)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_regular_function_rc)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010102);
void ConceptsFT_UT010102_Test::TestBody() {
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE, &EDST_CLASS_TYPE::StaticMemberWithRC,
                              EDST_EXPECTED_CONCEPT_TYPE, EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
}
#endif // UNIT_TEST_010100
//--------------------------------------------------------------------------------------------
/**
 * @test ConceptsFT_UT010103_TEST Test that a pointer to a static function,
 * ConceptsFT::StaticMember is selected by a template member of
 * TestFunctionSelection<ConceptType,int>::setConceptResult using the concept
 * eds::a_regular_function. The static function is passed as an address in a pointer.
 */
#ifdef UNIT_TEST_010103
class ConceptsFT_UT010103_Test : public ConceptsFT {
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010103, UNIT_TEST_010103)
     void TestBody() override;
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::pointer)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_regular_function_except_rc)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010103);
void ConceptsFT_UT010103_Test::TestBody() {
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE,
                              &EDST_CLASS_TYPE::StaticMemberWithRCExcept,
                              EDST_EXPECTED_CONCEPT_TYPE, EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
}
#endif // UNIT_TEST_010100
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010105
class ConceptsFT_UT010105_Test : public ConceptsFT {
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010105, UNIT_TEST_010105)
     void TestBody() override;
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::lvalue)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_functional_lvalue)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010105);
void ConceptsFT_UT010105_Test::TestBody() {
     eds::SubscriberSTDFunctionWithParams_t<ConceptType, int> f(
         &EDST_CLASS_TYPE::StaticMemberWithParams);
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE, f, EDST_EXPECTED_CONCEPT_TYPE,
                              EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_EQ(EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG,
                                  EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000020, EXPECT_EQ(EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG,
                                  EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000030,
                EXPECT_EQ(EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000040, EXPECT_EQ(EDST_CLASS_CONCEPT_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000050, EXPECT_EQ(EDST_CLASS_FUNCTION_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(
         000060,
         EXPECT_EQ(EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY,
                   EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY));
     EDS_PROBEW(000070,
                EXPECT_EQ(EDST_EXPECTED_CLASS_PARAMETER_PROPERTY,
                          EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY));
     EDS_PROBEW(000080,
                EXPECT_EQ(EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID, EDS_EXPECTED_TEST_ID));
     EDS_PROBEW(000090, EXPECT_EQ(EDST_SPECIALIZATION.m_type_decoration,
                                  EDST_EXPECTED_TYPE_DECORATION));
}
#endif // UNIT_TEST_010105
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010106
/**
 * @test ConceptsFT_UT010106_Test Smart pointer move semantics is tested. A unique_ptr to a
 * std::function of a static function is passed initially as lvalue. Move semantics are tested
 * such that the lvalue is turned to rvalue via std::move. We make sure we are left with a
 * nullptr when the call returns. concept tested is eds::a_functional_value.
 */
class ConceptsFT_UT010106_Test : public ConceptsFT {
     void TestBody() override;
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010106, UNIT_TEST_010106)
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::unique_ptr)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::lvalue)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_unique_ptr_functional_value)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010106);
void ConceptsFT_UT010106_Test::TestBody() {
     auto f = std::make_unique<eds::SubscriberSTDFunctionWithParams_t<ConceptType, int>>(
         EDST_CLASS_TYPE::StaticMemberWithParams);
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE, f, EDST_EXPECTED_CONCEPT_TYPE,
                              EDS_EXPECTED_TEST_ID);
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_EQ(EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG,
                                  EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000020, EXPECT_EQ(EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG,
                                  EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000030,
                EXPECT_EQ(EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000040, EXPECT_EQ(EDST_CLASS_CONCEPT_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000050, EXPECT_EQ(EDST_CLASS_FUNCTION_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(
         000060,
         EXPECT_EQ(EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY,
                   EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY));
     EDS_PROBEW(000070,
                EXPECT_EQ(EDST_EXPECTED_CLASS_PARAMETER_PROPERTY,
                          EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY));
     EDS_PROBEW(000080,
                EXPECT_EQ(EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID, EDS_EXPECTED_TEST_ID));
     EDS_PROBEW(000090, EXPECT_EQ(EDST_SPECIALIZATION.m_type_decoration,
                                  EDST_EXPECTED_TYPE_DECORATION));
}
#endif // UNIT_TEST_010106
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010107
class ConceptsFT_UT010107_Test : public ConceptsFT {
     void TestBody() override;
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010107, UNIT_TEST_010107)
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::shared_ptr)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::lvalue)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_shared_ptr_functional_value)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010107);
void ConceptsFT_UT010107_Test::TestBody() {
     auto f = std::make_shared<eds::SubscriberSTDFunctionWithParams_t<ConceptType, int>>(
         EDST_CLASS_TYPE::StaticMemberWithParams);
     EDST_TEST_SPECIALIZATION(EDST_EXPECTED_CONCEPT_TYPE, f, EDST_EXPECTED_CONCEPT_TYPE,
                              EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_EQ(EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG,
                                  EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000020, EXPECT_EQ(EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG,
                                  EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000030,
                EXPECT_EQ(EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000040, EXPECT_EQ(EDST_CLASS_CONCEPT_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000050, EXPECT_EQ(EDST_CLASS_FUNCTION_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(
         000060,
         EXPECT_EQ(EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY,
                   EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY));
     EDS_PROBEW(000070,
                EXPECT_EQ(EDST_EXPECTED_CLASS_PARAMETER_PROPERTY,
                          EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY));
     EDS_PROBEW(000080,
                EXPECT_EQ(EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID, EDS_EXPECTED_TEST_ID));
     EDS_PROBEW(000090, EXPECT_EQ(EDST_SPECIALIZATION.m_type_decoration,
                                  EDST_EXPECTED_TYPE_DECORATION));
}
#endif // UNIT_TEST_010107
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010108
/**
 * @test ConceptsFT_UT010108_Test A std::function of a static function is std::forwarded as
 * rvalue concept tested is eds::a_functional_value. This is how a delegate will handle an
 * lvalue of this type.
 */
class ConceptsFT_UT010108_Test : public ConceptsFT {
     void TestBody() override;
     EDST_DCL_GTEST_INTERNALS(ConceptsFT, UT010108, UNIT_TEST_010108)
     EDST_DCL_FOUND_SPECIALIZATION()
     EDST_DCL_EXPECTED_CONST_FLAG(false)
     EDST_DCL_EXPECTED_CLASS_FUNCTION_CALLED_FLAG(true)
     EDST_DCL_EXPECTED_CLASS_INSTANCE_CALLED_FLAG(false)
     EDST_DCL_EXPECTED_SPECIALIZATION(true)
     EDST_DCL_EXPECTED_TYPE_DECORATION(TypeDecoration::none)
     EDST_DCL_EXPECTED_FUNCTION_PARAMETER_PROPERTY(ParameterProperty::rvalue)
     EDST_DCL_EXPECTED_CLASS_PARAMETER_PROPERTY(ParameterProperty::none)
     EDST_DCL_EXPECTED_CONCEPT_TYPE(ConceptType::a_functional_rvalue)
     EDST_DCL_EXPECTED_FUNCTION_TYPE(FunctionType::StaticMemberWithParams)
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010108);
void ConceptsFT_UT010108_Test::TestBody() {
     eds::SubscriberSTDFunctionWithParams_t<ConceptType, int> f(
         &EDST_CLASS_TYPE::StaticMemberWithParams);
     EDST_TEST_SPECIALIZATION_FORWARD(EDST_EXPECTED_CONCEPT_TYPE, f,
                                      EDST_EXPECTED_CONCEPT_TYPE, EDS_EXPECTED_TEST_ID)
     EDS_PROBEW(000000, EXPECT_EQ(EDST_EXPECTED_SPECIALIZATION, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_EQ(EDST_EXPECTED_CLASS_FUNCTION_CALLED_FLAG,
                                  EDST_CLASS_FUNCTION_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000020, EXPECT_EQ(EDST_EXPECTED_CLASS_INSTANCE_CALLED_FLAG,
                                  EDST_CLASS_INSTANCE_MEMBER_CALLED_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000030,
                EXPECT_EQ(EDST_EXPECTED_CONST_FLAG, EDST_CLASS_CONST_FLAG(EDST_CLASS_TYPE)));
     EDS_PROBEW(000040, EXPECT_EQ(EDST_CLASS_CONCEPT_TYPE(EDST_CLASS_TYPE),
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000050,
                EXPECT_EQ(EDST_CLASS_TYPE::sm_function_type, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(
         000060,
         EXPECT_EQ(EDST_EXPECTED_FUNCTION_PARAMETER_PROPERTY,
                   EDST_SPECIALIZATION.EDST_SPECIALIZATION_FUNCTION_PARAMETER_PROPERTY));
     EDS_PROBEW(000070,
                EXPECT_EQ(EDST_EXPECTED_CLASS_PARAMETER_PROPERTY,
                          EDST_SPECIALIZATION.EDST_SPECIALIZATION_CLASS_PARAMETER_PROPERTY));
     EDS_PROBEW(000080,
                EXPECT_EQ(EDST_CLASS_TYPE::EDST_TEST_MEMBER_TEST_ID, EDS_EXPECTED_TEST_ID));
     EDS_PROBEW(000090, EXPECT_EQ(EDST_SPECIALIZATION.m_type_decoration,
                                  EDST_EXPECTED_TYPE_DECORATION));
}
#endif // UNIT_TEST_010108
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010109
/**
 * @test ConceptsFT_UT010109_Test A std::unique_ptr to a std::function of a static function is
 * std::forwarded as rvalue concept tested is eds::a_functional_value. This is how a delegate
 * will handle an lvalue of this type.
 */
class ConceptsFT_UT010109_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010109);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_unique_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::StaticMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010109);
void ConceptsFT_UT010109_Test::TestBody() {
     eds::SubscriberUniquePTRSTDFunctionWithParams_t<ConceptType> functional =
         std::make_unique<eds::SubscriberSTDFunctionWithParams_t<ConceptType>>(
             ConceptsFT::StaticMember);
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE,
         std::forward<eds::SubscriberUniquePTRSTDFunctionWithParams_t<ConceptType>>(
             functional));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040,
                EXPECT_TRUE(functional == nullptr)); // unique_ptr should now be nullptr
}
#endif // UNIT_TEST_010109
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010110
class ConceptsFT_UT010110_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010110);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_lvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::lambdaNoClosure;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010110);
void ConceptsFT_UT010110_Test::TestBody() {
     auto test_lambda = [](ConceptType a) noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = a;
          ConceptsFT::sm_FunctionType = FunctionType::lambdaNoClosure;
     };
     EDST_FOUND_SPECIALIZATION =
         EDST_TEST_SPECIALIZATION.setConceptResult(EDST_EXPECTED_CONCEPT_TYPE, test_lambda);
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010110
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010111
class ConceptsFT_UT010111_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010111);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_lvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::STDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010111);
void ConceptsFT_UT010111_Test::TestBody() {
     auto f = std::function<void(ConceptType)>([](ConceptType a) noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = a;
          ConceptsFT::sm_FunctionType = FunctionType::STDFunctionLambda;
     });
     EDST_FOUND_SPECIALIZATION =
         EDST_TEST_SPECIALIZATION.setConceptResult(EDST_EXPECTED_CONCEPT_TYPE, f);
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010111
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010112
class ConceptsFT_UT010112_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010112);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_unique_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::UniquePTRSTDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010112);
void ConceptsFT_UT010112_Test::TestBody() {
     auto f = std::make_unique<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
              ConceptsFT::sm_FunctionType = FunctionType::UniquePTRSTDFunctionLambda;
         });
     EDST_FOUND_SPECIALIZATION =
         EDST_TEST_SPECIALIZATION.setConceptResult(EDST_EXPECTED_CONCEPT_TYPE, f);
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040, EXPECT_TRUE(f == nullptr)); // unique_ptr should now be nullptr
}
#endif // UNIT_TEST_010112
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010113
class ConceptsFT_UT010113_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010113);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_shared_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::STDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010113);
void ConceptsFT_UT010113_Test::TestBody() {
     auto f = std::make_shared<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
              ConceptsFT::sm_FunctionType = FunctionType::STDFunctionLambda;
         });
     EDST_FOUND_SPECIALIZATION =
         EDST_TEST_SPECIALIZATION.setConceptResult(EDST_EXPECTED_CONCEPT_TYPE, f);
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040, EXPECT_EQ(f.use_count(), 1)); // shared_ptr should still be good
}
#endif // UNIT_TEST_010113
//--------------------------------------------------------------------------------------------
/**
 * @test ConceptsFT_UT010114_Test A std::shared_ptr to a std::function of a static function is
 * std::forwarded as rvalue. Concept tested is eds::a_functional_value. This is how a delegate
 * will handle an lvalue of this type.
 */
#ifdef UNIT_TEST_010114
class ConceptsFT_UT010114_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010114);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_shared_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::StaticMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010114);
void ConceptsFT_UT010114_Test::TestBody() {
     eds::SubscriberSharedPTRSTDFunctionWithParams_t<ConceptType> function =
         std::make_shared<std::function<void(ConceptType)>>(ConceptsFT::StaticMember);
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE,
         std::forward<eds::SubscriberSharedPTRSTDFunctionWithParams_t<ConceptType>>(function));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040, EXPECT_EQ(function.use_count(), 0)); // shared_ptr forwarded
}
#endif // UNIT_TEST_010114
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010115
/**
 * @test ConceptsFT_UT010115_Test A lambda is std::forwarded as
 * rvalue concept tested is eds::a_functional_value. This is how a delegate will forward an
 * lvalue of this type to the CallHandler.
 */
class ConceptsFT_UT010115_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010115);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_rvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::lambdaNoClosure;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010115);
void ConceptsFT_UT010115_Test::TestBody() {
     auto test_lambda = [](ConceptType a) noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = a;
          ConceptsFT::sm_FunctionType = FunctionType::lambdaNoClosure;
     };
     using TestLambda = decltype(test_lambda);
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, std::forward<TestLambda>(test_lambda));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010115
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010116
/**
 * @test ConceptsFT_UT010116_Test A std::unique_ptr to a std::function containing a lambda is
 * std::forwarded as rvalue concept tested is eds::a_functional_value. This is how a delegate
 * will forward an lvalue of this type to the CallHandler.
 */
class ConceptsFT_UT010116_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010116);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_unique_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::UniquePTRSTDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010116);
void ConceptsFT_UT010116_Test::TestBody() {
     auto f = std::make_unique<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
              ConceptsFT::sm_FunctionType = FunctionType::UniquePTRSTDFunctionLambda;
         });
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, std::forward<decltype(f)>(f));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040, EXPECT_TRUE(f == nullptr)); // unique_ptr should now be nullptr
}
#endif // UNIT_TEST_010116
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010117
/**
 * @test ConceptsFT_UT010117_Test A std::shared_ptr to a std::function containing a lambda is
 * std::forwarded as rvalue concept tested is eds::a_functional_value. This is how a delegate
 * will forward an lvalue of this type to the CallHandler.
 */
class ConceptsFT_UT010117_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010117);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_shared_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::STDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010117);
void ConceptsFT_UT010117_Test::TestBody() {
     auto f = std::make_shared<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
              ConceptsFT::sm_FunctionType = FunctionType::STDFunctionLambda;
         });
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, std::forward<decltype(f)>(f));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
     EDS_PROBEW(000040, EXPECT_EQ(f.use_count(), 0)); // shared_ptr forwarded
}
#endif // UNIT_TEST_010117
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010120
class ConceptsFT_UT010120_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010120);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_rvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::lambdaWithClosure;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010120);
void ConceptsFT_UT010120_Test::TestBody() {
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, [=](ConceptType concept_type) noexcept -> void {
              EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
         });
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010121
class ConceptsFT_UT010121_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010121);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_lvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::lambdaWithClosure;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010121);
void ConceptsFT_UT010121_Test::TestBody() {
     auto f = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [=](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
         });
     EDST_FOUND_SPECIALIZATION =
         EDST_TEST_SPECIALIZATION.setConceptResult(EDST_EXPECTED_CONCEPT_TYPE, f);
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010121
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010122
class ConceptsFT_UT010122_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010122);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_unique_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::UniquePTRSTDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010122);
void ConceptsFT_UT010122_Test::TestBody() {
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE,
         std::make_unique<std::function<void(ConceptType)>>(
             [=](ConceptType concept_type) noexcept -> void {
                  EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
                  ConceptsFT::sm_FunctionCalled = true;
                  ConceptsFT::sm_ConceptType = concept_type;
                  ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
             }));
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010122
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010123
class ConceptsFT_UT010123_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010123);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_shared_ptr_functional_value;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::SharedPTRSTDFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010123);
void ConceptsFT_UT010123_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE,
         std::make_shared<std::function<void(ConceptType)>>(
             [=](ConceptType concept_type) noexcept -> void {
                  EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
                  ConceptsFT::sm_FunctionCalled = true;
                  ConceptsFT::sm_ConceptType = concept_type;
                  ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
             }));
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010123
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010125
class ConceptsFT_UT010125_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010125);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_rvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::STDMoveOnlyFunctionLambda;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010125);
void ConceptsFT_UT010125_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     auto functional = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [=](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
         });
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, std::move(functional));
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010125
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010126
class ConceptsFT_UT010126_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010126);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_functional_rvalue;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE = FunctionType::lambdaWithClosure;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010126);
void ConceptsFT_UT010126_Test::TestBody() {
     auto f = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [=](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              EDST_TEST_SPECIALIZATION.m_test_result = concept_type;
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              ConceptsFT::sm_FunctionType = EDST_EXPECTED_FUNCTION_TYPE;
         });
     EDST_FOUND_SPECIALIZATION = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, std::forward<decltype(f)>(f));
     EDS_PROBEW(000001,
                EXPECT_EQ(EDST_TEST_SPECIALIZATION.m_test_result, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100000, EXPECT_EQ(m_expected_found_specialization, EDST_FOUND_SPECIALIZATION));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_FunctionType, EDST_EXPECTED_FUNCTION_TYPE));
}
#endif // UNIT_TEST_010126
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010130
class ConceptsFT_UT010130_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010130);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     EDST_CLASS_TYPE m_testMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010130);
void ConceptsFT_UT010130_Test::TestBody() {
     #pragma message(EDS_WARNING(__FILE__, __LINE__, EDS_1001(CLASS, Object_Pointer)))
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, &m_testMember, &EDST_CLASS_TYPE::memberFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(100010,
                EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100020, EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBEW(100030, EXPECT_TRUE(m_testMember.isMember()));
     EDS_PROBEW(100040, EXPECT_FALSE(m_testMember.isConstMember()));
     EDS_PROBEW(100050,
                EXPECT_EQ(m_testMember.get_function_type(), EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010131
class ConceptsFT_UT010131_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010131);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010131);
void ConceptsFT_UT010131_Test::TestBody() {
     auto testMember = std::make_unique<EDST_CLASS_TYPE>();
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, testMember, &EDST_CLASS_TYPE::memberFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(100010,
                EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100020, EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBEW(100030, EXPECT_TRUE(testMember->isMember()));
     EDS_PROBEW(100040, EXPECT_FALSE(testMember->isConstMember()));
     EDS_PROBEW(100050,
                EXPECT_EQ(testMember->get_function_type(), EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010132
class ConceptsFT_UT010132_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010132);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010132);
void ConceptsFT_UT010132_Test::TestBody() {
     auto testMember = std::make_shared<EDST_CLASS_TYPE>();
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, testMember, &EDST_CLASS_TYPE::memberFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(100010,
                EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100020, EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBEW(100030, EXPECT_TRUE(testMember->isMember()));
     EDS_PROBEW(100040, EXPECT_FALSE(testMember->isConstMember()));
     EDS_PROBEW(100050,
                EXPECT_EQ(testMember->get_function_type(), EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010133
class ConceptsFT_UT010133_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010133);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     EDST_CLASS_TYPECopyable m_testMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010133);
void ConceptsFT_UT010133_Test::TestBody() {
     #pragma message(EDS_WARNING(__FILE__, __LINE__, EDS_1001(CLASS, Object_Pointer)))
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, &m_testMember, &EDST_CLASS_TYPECopyable::memberFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(100010, EXPECT_EQ(EDST_CLASS_TYPECopyable::sm_ConceptType,
                                  EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100020, EXPECT_TRUE(EDST_CLASS_TYPECopyable::sm_FunctionCalled));
     EDS_PROBEW(100030, EXPECT_TRUE(m_testMember.isMember()));
     EDS_PROBEW(100040, EXPECT_FALSE(m_testMember.isConstMember()));
     EDS_PROBEW(100050,
                EXPECT_EQ(m_testMember.get_function_type(), EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010134
class ConceptsFT_UT010134_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010134);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     EDST_CLASS_TYPEMovable m_testMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010134);
void ConceptsFT_UT010134_Test::TestBody() {
     #pragma message(EDS_WARNING(__FILE__, __LINE__, EDS_1001(CLASS, Object_Pointer)))
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, &m_testMember, &EDST_CLASS_TYPEMovable::memberFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(100010,
                EXPECT_EQ(EDST_CLASS_TYPEMovable::sm_ConceptType, EDST_EXPECTED_CONCEPT_TYPE));
     EDS_PROBEW(100020, EXPECT_TRUE(EDST_CLASS_TYPEMovable::sm_FunctionCalled));
     EDS_PROBEW(100030, EXPECT_TRUE(m_testMember.isMember()));
     EDS_PROBEW(100040, EXPECT_FALSE(m_testMember.isConstMember()));
     EDS_PROBEW(100050,
                EXPECT_EQ(m_testMember.get_function_type(), EDST_EXPECTED_FUNCTION_TYPE));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010135
class ConceptsFT_UT010135_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010135);
     TestFunctionSelection<ConceptType> EDST_TEST_SPECIALIZATION;
     bool EDST_FOUND_SPECIALIZATION = false;
     const bool m_expected_found_specialization = true;
     const ConceptType EDST_EXPECTED_CONCEPT_TYPE = ConceptType::a_member_function_pointer;
     const FunctionType EDST_EXPECTED_FUNCTION_TYPE =
         FunctionType::MemberFunctionPTRWithParams;
     EDST_CLASS_TYPE m_testMember;
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010135);
void ConceptsFT_UT010135_Test::TestBody() {
     auto functional = std::mem_fn(&EDST_CLASS_TYPE::memberFunction);
     bool found_specialization = EDST_TEST_SPECIALIZATION.setConceptResult(
         EDST_EXPECTED_CONCEPT_TYPE, &m_testMember, functional);
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010136
class ConceptsFT_UT010136_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010136);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010136);
void ConceptsFT_UT010136_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     auto testMember = std::make_unique<EDST_CLASS_TYPE>();
     auto functional = std::mem_fn(&EDST_CLASS_TYPE::memberFunction);
     bool found_specialization = testFunctions.setConceptResult(testMember, functional);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
#endif
//--------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010137
class ConceptsFT_UT010137_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010137);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010137);
void ConceptsFT_UT010137_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     auto testMember = std::make_shared<EDST_CLASS_TYPE>();
     auto type = typeid(testMember.get()).name();
     auto functional = std::mem_fn(&EDST_CLASS_TYPE::memberFunction);
     bool found_specialization = testFunctions.setConceptResult(testMember, functional);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_functional_lvalue
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
     TestFunctionSelection<ConceptType> testFunctions;
     EDST_CLASS_TYPE testMember;
     bool found_specialization =
         testFunctions.setConceptResult(&testMember, &EDST_CLASS_TYPE::memberConstFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBE(
         EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
//--------------------------------------------------------------------------------------------
class ConceptsFT_UT010141_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010141);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010141);
void ConceptsFT_UT010141_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     auto testMember = std::make_unique<EDST_CLASS_TYPE>();
     bool found_specialization =
         testFunctions.setConceptResult(testMember, &EDST_CLASS_TYPE::memberConstFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBE(
         EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember->isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember->isConstMember()));
}
class ConceptsFT_UT010142_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010142);
     void TestBody() override;
};
//--------------------------------------------------------------------------------------------
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010142);
void ConceptsFT_UT010142_Test::TestBody() {
     TestFunctionSelection<ConceptType> testFunctions;
     auto testMember = std::make_shared<EDST_CLASS_TYPE>();
     bool found_specialization =
         testFunctions.setConceptResult(testMember, &EDST_CLASS_TYPE::memberConstFunction);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBE(
         EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember->isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember->isConstMember()));
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
     TestFunctionSelection<> testFunctions;
     // go through the specialization for to call the std::function, this is what we are
     // testing
     EDS_PROBEW(100000,
                EXPECT_EQ(supported_specialization,
                          testFunctions.setConceptResult(ConceptsFT::StaticMemberNoParams)));
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
     TestFunctionSelection<> testFunctions;
     // create a std::function<void()> from a static member function with no parameters
     std::function<void()> f(StaticMemberNoParams);
     // go through the specialization for to call the std::function, this is what we are
     // testing
     EDS_PROBEW(100000,
                EXPECT_EQ(supported_specialization, testFunctions.setConceptResult(f)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_regular_function_pointer_without_params));
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
     TestFunctionSelection<> testFunctions;
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult([]() noexcept -> void {
                                       ConceptsFT::sm_FunctionCalled = true;
                                       ConceptsFT::sm_ConceptType =
                                           ConceptType::a_lambda_rvalue_without_parameters;
                                  })));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_lambda_rvalue_without_parameters));
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

Required compiler support for P0288R9 to be enabled

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
     TestFunctionSelection<> testFunctions;
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void()>([]() EDS_LAMBDA_NOEXCEPT -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
     });
     EDS_PROBEW(100000,
                EXPECT_EQ(supported_specialization, testFunctions.setConceptResult(lambda)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_functional_lvalue_without_parameters));
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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_regular_function_pointer
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
     TestFunctionSelection<> testFunctions;
     auto test_lambda = [&testFunctions]() noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = ConceptType::a_lambda_rvalue_without_parameters;
          testFunctions.m_test_result = ConceptType::a_lambda_rvalue_without_parameters;
     };
     auto found_specialization = testFunctions.setConceptResult(test_lambda);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization, found_specialization));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_lambda_rvalue_without_parameters));
}
#endif
//------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_010225
// clang-format off
/**
 @brief Tests the concept eds::a_functional_lvalue with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using a std::function encapsulating a capture lambda to test
 ConceptsFT.UT010225

 Requires compiler support for P0288R9 to be enabled

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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_functional_lvalue
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
     TestFunctionSelection<> testFunctions;
     auto functional =
         EDS_CONSERVATIVE_FUNCTION<void()>([&testFunctions]() EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
              testFunctions.m_test_result =
                  ConceptType::a_functional_lvalue_without_parameters;
         });
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult(functional)));
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result,
                                  ConceptType::a_functional_lvalue_without_parameters));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_functional_lvalue_without_parameters));
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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_functional_lvalue
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
     TestFunctionSelection<> testFunctions;
     EDST_CLASS_TYPE testMember;
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult(
                                      &testMember, &EDST_CLASS_TYPE::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType,
                         ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
class ConceptsFT_UT010231_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010231);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010231);
void ConceptsFT_UT010231_Test::TestBody() {
     TestFunctionSelection<> testFunctions;
     auto testMember = std::make_unique<EDST_CLASS_TYPE>();
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult(
                                      testMember, &EDST_CLASS_TYPE::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType,
                         ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
class ConceptsFT_UT010232_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010232);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010232);
void ConceptsFT_UT010232_Test::TestBody() {
     TestFunctionSelection<> testFunctions;
     auto testMember = std::make_shared<EDST_CLASS_TYPE>();
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult(
                                      testMember, &EDST_CLASS_TYPE::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType,
                         ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_functional_lvalue
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
     TestFunctionSelection<> testFunctions;
     EDST_CLASS_TYPE testMember;
     auto functional = std::mem_fn(&EDST_CLASS_TYPE::memberFunctionNoParams);
     EDS_PROBEW(100000, EXPECT_EQ(supported_specialization,
                                  testFunctions.setConceptResult(&testMember, functional)));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType,
                         ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
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
 000020 | TestFunctionSelection<>::m_test_result | ConceptType::a_functional_lvalue
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
     TestFunctionSelection<> testFunctions;
     EDST_CLASS_TYPE testMember;
     EDS_PROBEW(100000,
                EXPECT_EQ(supported_specialization,
                          testFunctions.setConceptResult(
                              &testMember, &EDST_CLASS_TYPE::memberConstFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(EDST_CLASS_TYPE::sm_ConceptType,
                         ConceptType::a_const_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(EDST_CLASS_TYPE::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
#endif
