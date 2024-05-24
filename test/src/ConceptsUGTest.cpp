/**
 *
 * @file ConceptsUGTest.cpp
 * @brief  Implement Unit Concepts Testing
 * @details This file contains the implementation of the unit tests for the concepts.
 * @sa unit_test_concepts_page
 * @author Joaqu�n "Jack" D. Men�ndez
 * @date   March 2024
 * @todo Allow only smart pointers to the object for member functions and lambdas, also make for object pointers we can give a message via static assert
 */
#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_util.hpp"
#include "private/eds_concepts.hpp"
#include <functional>
#include <memory>
#include <private/eds_env.hpp>
#include <type_traits>
#include "../include/custom_gtest.hpp"
#include <gtest/gtest.h>
#define UNIT_TEST_010100 UT010100
#define UNIT_TEST_010101 UT010101
#define UNIT_TEST_010102 UT010102
#define UNIT_TEST_010103 UT010103
#define UNIT_TEST_010104 UT010104
#define UNIT_TEST_010105 UT010105
#define UNIT_TEST_010106 UT010106
#define UNIT_TEST_010107 UT010107
#define UNIT_TEST_010110 UT010110
#define UNIT_TEST_010111 UT010111
#define UNIT_TEST_010112 UT010112
#define UNIT_TEST_010113 UT010113
#define UNIT_TEST_010115 UT010115
#define UNIT_TEST_010116 UT010116
#define UNIT_TEST_010117 UT010117
#define UNIT_TEST_010120 UT010120
#define UNIT_TEST_010121 UT010121
#define UNIT_TEST_010122 UT010122
#define UNIT_TEST_010123 UT010123
#define UNIT_TEST_010125 UT010125
#define UNIT_TEST_010130 UT010130
#define UNIT_TEST_010131 UT010131
#define UNIT_TEST_010132 UT010132
#define UNIT_TEST_010133 UT010133
#define UNIT_TEST_010134 UT010134
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
     enum class object_properties { not_copyable_and_not_movable,
          copyable_and_not_movable,
          copyable_and_movable,
          not_copyable_and_movable
     };
     struct test_object_interface {
          virtual ~test_object_interface() = default;
          virtual bool test(object_properties expected_properties) = 0;
     };
class NotCopyableNotMovable {
     bool m_i_said_it = false;

   public:
     NotCopyableNotMovable() noexcept = default;
     ~NotCopyableNotMovable() noexcept = default;
     NotCopyableNotMovable(const NotCopyableNotMovable &other) noexcept = delete;
     NotCopyableNotMovable(NotCopyableNotMovable &&other) noexcept = delete;
     NotCopyableNotMovable &operator=(const NotCopyableNotMovable &other) noexcept = delete;
     NotCopyableNotMovable &operator=(NotCopyableNotMovable &&other) noexcept = delete;

     void say_it() {
          std::cout << "Not Copyable Not Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class NotExplicit {
     bool m_i_said_it = false;

   public:
     void say_it() {
          std::cout << "Not Explicit";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class NotCopyableMovable {
     bool m_i_said_it = false;

   public:
     NotCopyableMovable() noexcept = default;
     ~NotCopyableMovable() noexcept = default;
     NotCopyableMovable(NotCopyableMovable &&other) noexcept = default;
     NotCopyableMovable &operator=(NotCopyableMovable &&other) noexcept = default;
     NotCopyableMovable(const NotCopyableMovable &other) noexcept = delete;
     NotCopyableMovable &operator=(const NotCopyableMovable &other) noexcept = delete;

     void say_it() {
          std::cout << "Not Copyable Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class CopyableNotMovable {
     bool m_i_said_it = false;

   public:
     CopyableNotMovable() noexcept = default;
     ~CopyableNotMovable() noexcept = default;
     CopyableNotMovable(const CopyableNotMovable &other) noexcept = default;
     CopyableNotMovable(CopyableNotMovable &&other) noexcept = delete;
     CopyableNotMovable &operator=(const CopyableNotMovable &other) noexcept = default;
     CopyableNotMovable &operator=(CopyableNotMovable &&other) noexcept = delete;

     void say_it() {
          std::cout << "Copyable Not Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class CopyableMovable {
     bool m_i_said_it = false;

   public:
     CopyableMovable() noexcept = default;
     ~CopyableMovable() noexcept = default;
     CopyableMovable(const CopyableMovable &other) noexcept = default;
     CopyableMovable(CopyableMovable &&other) noexcept = default;
     CopyableMovable &operator=(const CopyableMovable &other) noexcept = default;
     CopyableMovable &operator=(CopyableMovable &&other) noexcept = default;

     void say_it() {
          std::cout << "Copyable And Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
     static constexpr bool supported_specialization = true;
static constexpr bool forbidden_specialization = false;
static bool g_test_result;
static int g_test_result_int;
static void setTestResult(bool p_result, int p_amount, int &p_result_amount) noexcept {
     g_test_result = p_result;
     p_result_amount = p_amount;
}
static constexpr bool g_test_result_default = false;
static constexpr bool g_test_result_expected = true;
static constexpr int g_test_result_int_default = 0;
static constexpr int g_test_result_int_expected = 5;
     /** @brief enumerated types of functions for probes to test. */
     enum class ConceptType : int {
          a_regular_function_pointer,                ///< A global or static function
          a_regular_function_pointer_without_params, ///< A global or static function with no
                                                     ///< parameters
          a_functional_lvalue,                       ///< A std::function
          a_unique_ptr_functional_lvalue,            ///< A unique_ptr containing std::function
          a_shared_ptr_functional_lvalue,            ///< A unique_ptr containing std::function
          a_functional_lvalue_without_parameters,    ///< A std::function
          a_lambda_rvalue,                           ///< A lambda functor
          a_lambda_rvalue_without_parameters,        ///< A lambda functor
          a_member_function_pointer,                 ///< A a_member_function_pointer function
          a_member_function_pointer_without_parameters, ///< A a_member_function_pointer function
          const_member, ///< A const a_member_function_pointer function
          a_const_member_function_pointer_without_parameters, ///< A const a_member_function_pointer function
          not_allowed, ///< A function combination that is not allowed
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
          setTestResult(g_test_result_default, g_test_result_int_default, g_test_result_int);
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
     static void staticMemberPointer(ConceptType p_concept_type) noexcept {
          sm_FunctionCalled = true;
          sm_ConceptType = p_concept_type;
     }
     /**
      * @brief A static function that can be passed as a function pointer or std::function
      */
     static void staticMemberPointerNoParams() noexcept {
          sm_FunctionCalled = true;
          sm_ConceptType = ConceptType::a_regular_function_pointer_without_params;
     }
     template<typename... PARAMS>
     using TestFunction_t = void(PARAMS...) noexcept;

     class TestMember {
          
          bool m_member = false;
          mutable bool m_const_member = false;

        public:
          TestMember() noexcept = default;
          TestMember(const TestMember &) noexcept = delete;
          TestMember(TestMember &&) noexcept = delete;
          TestMember(const TestMember &&) noexcept = delete;
          TestMember &operator=(const TestMember &) noexcept = delete;
          TestMember &operator=(TestMember &&) noexcept = delete;
          TestMember &operator=(const TestMember &&) noexcept = delete;
          virtual ~TestMember() noexcept = default;
              template<typename... PARAMS>
              using TemMember_t = void(TestMember::*)(PARAMS...) noexcept;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = concept_type;
               m_member = true;
          }
          void memberConstFunction(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void memberFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void memberConstFunctionNoParams() const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_const_member_function_pointer_without_parameters;
               m_const_member = true;
          }
     };
     class TestMemberCopyable {
          
          bool m_member = false;
          mutable bool m_const_member = false;

        public:
          TestMemberCopyable() noexcept = default;
          TestMemberCopyable(const TestMemberCopyable &) noexcept = default;
          TestMemberCopyable(TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable(const TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable &operator=(const TestMemberCopyable &) noexcept = default;
          TestMemberCopyable &operator=(TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable &operator=(const TestMemberCopyable &&) noexcept = delete;

          virtual ~TestMemberCopyable() noexcept = default;
              template<typename... PARAMS>
              using TemMember_t = void(TestMember::*)(PARAMS...) noexcept;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = concept_type;
               m_member = true;
          }
          void memberConstFunction(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void memberFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void memberConstFunctionNoParams() const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_const_member_function_pointer_without_parameters;
               m_const_member = true;
          }
     };
     class TestMemberMoveable {
          
          bool m_member = false;
          mutable bool m_const_member = false;

        public:
          TestMemberMoveable() noexcept = default;
          TestMemberMoveable(const TestMemberMoveable &) noexcept = delete;
          TestMemberMoveable(TestMemberMoveable &&) noexcept = default;
          TestMemberMoveable(const TestMemberMoveable &&) noexcept = delete;
          TestMemberMoveable &operator=(const TestMemberMoveable &) noexcept = delete;
          TestMemberMoveable &operator=(TestMemberMoveable &&) noexcept = default;
          //TestMemberMoveable &operator=(const TestMemberMoveable &&) noexcept = default;
          virtual ~TestMemberMoveable() noexcept = default;
              template<typename... PARAMS>
              using TemMember_t = void(TestMember::*)(PARAMS...) noexcept;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = concept_type;
               m_member = true;
          }
          void memberConstFunction(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void memberFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void memberConstFunctionNoParams() const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_const_member_function_pointer_without_parameters;
               m_const_member = true;
          }
     };
     class TestMemberCopyMoveable {
          
          bool m_member = false;
          mutable bool m_const_member = false;

        public:
          TestMemberCopyMoveable() noexcept = default;
          TestMemberCopyMoveable(const TestMemberCopyMoveable &) noexcept = default;
          TestMemberCopyMoveable(TestMemberCopyMoveable &&) noexcept = default;
          TestMemberCopyMoveable &operator=(const TestMemberCopyMoveable &) noexcept = default;
          TestMemberCopyMoveable &operator=(TestMemberCopyMoveable &&) noexcept = default;
          virtual ~TestMemberCopyMoveable() noexcept = default;
              template<typename... PARAMS>
              using TemMember_t = void(TestMember::*)(PARAMS...) noexcept;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = concept_type;
               m_member = true;
          }
          void memberConstFunction(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void memberFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void memberConstFunctionNoParams() const noexcept {
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
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(FUNCPTR *function_pointer) const noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer(ConceptType::a_regular_function_pointer);
               return supported_specialization;
          }
          template <typename FUNCPTR>
               requires eds::a_regular_function_pointer<FUNCPTR, bool, int, int&>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setExternalConceptResult(FUNCPTR *function_pointer) const noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer(g_test_result_expected,g_test_result_int_expected,g_test_result_int);
               return supported_specialization;
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
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(FUNCTIONAL &functional) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               functional(ConceptType::a_functional_lvalue);
               return supported_specialization;
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
               * @tparam PTRTYPE The smart pointer type should be of a form like
               * `std::unique_ptr<std::function<void(PARAMS...)>>`
               *
               * @param smartptr The smart pointer that will be called with the ConceptType. The
               * smart pointer is provided as an rvalue by the test case which, through template
               * specialization picks this template.
               *
               * @anchor UT010110_setConceptResult
               * @sa UT010110
               * @sa UT010120
               * @sa edsUGTest.ConceptsFT.UT010110
               * @sa edsUGTest.ConceptsFT.UT010120
               * @sa unit_test_concepts_page
               * @sa Test
               * @sa eds::a_functional_lvalue
               * @sa ConceptType::a_functional_lvalue
               */
          template <typename PTRTYPE>
               requires eds::a_functional_lvalue<PTRTYPE, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<PTRTYPE>& smartptr) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               smartptr->operator()(ConceptType::a_unique_ptr_functional_lvalue);
               return supported_specialization;
          }
          template <typename PTRTYPE>
               requires eds::a_functional_lvalue<PTRTYPE, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<PTRTYPE>& smartptr) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               smartptr->operator()(ConceptType::a_shared_ptr_functional_lvalue);
               return supported_specialization;
          }
          template <typename PTRTYPE>
               requires eds::a_functional_lvalue<PTRTYPE, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<std::function<PTRTYPE>>& smartptr) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               smartptr->operator()(ConceptType::none);
               return supported_specialization;
          }
          template <typename PTRTYPE>
               requires eds::a_functional_lvalue<PTRTYPE, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<std::function<PTRTYPE>>& smartptr) const noexcept {
               /// @details Call the std::function passing the ConceptType that will be tested
               smartptr->operator()(ConceptType::none);
               return supported_specialization;
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
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(LAMBDA &&lambda) const noexcept {
               /// @details call the lambda passing the ConceptType that will be tested
               lambda(ConceptType::a_lambda_rvalue);
               return supported_specialization;
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
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...> &&
                        eds::some_class_type<CLASS> && eds::noncopyable<CLASS> && 
                        eds::nonmovable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object_pointer->*member_function_pointer)(
                   ConceptType::a_member_function_pointer);
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...> &&
                        eds::some_class_type<CLASS> && eds::copyable<CLASS> && 
                        eds::nonmovable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
               EDS_INFO(MESSAGE) << EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS, object_pointer));
               EDS_INFO(MESSAGE) << EDS_ERROR(__FILE__,__LINE__,EDS_2001(CLASS, object_pointer));
               return forbidden_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...> &&
                        eds::some_class_type<CLASS> && eds::movable<CLASS> && 
                        eds::noncopyable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
               EDS_INFO(MESSAGE) << EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS, object_pointer));
               EDS_INFO(MESSAGE) << EDS_ERROR(__FILE__,__LINE__,EDS_2001(CLASS, object_pointer));
               return forbidden_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<CLASS>& object_pointer,
                                METHOD member_function_pointer) const noexcept {
               (object_pointer.get()->*member_function_pointer)(
                   ConceptType::a_member_function_pointer);
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer<CLASS, METHOD, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<CLASS>& object_pointer,
                                METHOD member_function_pointer) const noexcept {
                    (object_pointer.get()->*member_function_pointer)(
                        ConceptType::a_member_function_pointer);
               return supported_specialization;
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
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(CLASS *object, METHOD &method) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               method(object, ConceptType::a_functional_lvalue);
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_lvalue<METHOD, CLASS, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<CLASS> &object, METHOD &method) const noexcept {
               method(object.get(), ConceptType::a_functional_lvalue);
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_lvalue<METHOD, CLASS, PARAMS...> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<CLASS>& object, METHOD &method) const noexcept {
               method(object.get(), ConceptType::a_functional_lvalue);
               return supported_specialization;
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
               requires eds::a_const_member_function_pointer<CLASS, FUNC, PARAMS...> &&
                        eds::some_class_type<CLASS> && eds::noncopyable<CLASS> && 
                        eds::nonmovable<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(const CLASS *object, FUNC f) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object->*f)(ConceptType::a_member_function_pointer);
               return supported_specialization;
          }
          template <class CLASS, typename FUNC>
               requires eds::a_const_member_function_pointer<CLASS, FUNC, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<CLASS> &object, FUNC f) const noexcept {
               (object.get()->*f)(ConceptType::a_member_function_pointer);
               return supported_specialization;
          }
          template <class CLASS, typename FUNC>
               requires eds::a_const_member_function_pointer<CLASS, FUNC, PARAMS...>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<CLASS>& object, FUNC f) const noexcept {
               (object.get()->*f)(ConceptType::a_member_function_pointer);
               return supported_specialization;
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
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(FUNCPTR *function_pointer) const noexcept {
               /// @details call the function via the pointer passing the ConceptType that will
               /// be tested
               function_pointer();
               return supported_specialization;
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
          bool setConceptResult(FUNCTIONAL &functional) const noexcept {
               functional();
               return supported_specialization;
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
          bool setConceptResult(LAMBDA &&lambda) const noexcept {
               lambda();
               return supported_specialization;
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
          bool setConceptResult(CLASS *object_pointer,
                                METHOD member_function_pointer) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object_pointer->*member_function_pointer)();
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD> && eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<CLASS> &object_pointer,
                                METHOD member_function_pointer) const noexcept {
               (object_pointer.get()->*member_function_pointer)();
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_member_function_pointer_without_params<CLASS, METHOD> && eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<CLASS> &object_pointer,
                                METHOD member_function_pointer) const noexcept {
               (object_pointer.get()->*member_function_pointer)();
               return supported_specialization;
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
          bool setConceptResult(CLASS *object, METHOD method) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               method(object);
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_member_lvalue_without_params<METHOD,CLASS> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::unique_ptr<CLASS> &object, METHOD method) const noexcept {
               method(object.get());
               return supported_specialization;
          }
          template <class CLASS, typename METHOD>
               requires eds::a_functional_member_lvalue_without_params<METHOD,CLASS> &&
                        eds::some_class_type<CLASS>
          [[nodiscard("Required result bool True if is allowed, false if not")]]
          bool setConceptResult(std::shared_ptr<CLASS> &object, METHOD method) const noexcept {
               method(object.get());
               return supported_specialization;
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
          bool setConceptResult(const CLASS *object, FUNC f) const noexcept {
                #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,object_pointer)))
               (object->*f)();
               return supported_specialization;
          }

          ~TestRegularFunctions() noexcept = default;
     };
     };
bool ConceptsFT::g_test_result = false;
int ConceptsFT::g_test_result_int = 0;
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
 100000 | return code       | supported_specialization
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(ConceptsFT::staticMemberPointer)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType,
                                  ConceptType::a_regular_function_pointer));
}
#endif // UNIT_TEST_010100
#ifdef UNIT_TEST_010101
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult
 using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010101

@anchor edsUGTest.ConceptsFT.UT010101

@test Test Explorer: edsUGTest->ConceptsFT->UT010101
@ref edsUGTest.ConceptsFT.UT010101

@sa UT010100_setConceptResult

The targeted function if the test case is successful:
@sa UT010101_setConceptResult
which is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010101
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
@sa UT010101_setConceptResult
 */
class ConceptsFT_UT010101_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010101);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010101);
void ConceptsFT_UT010101_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     EDS_PROBEW(100000,EXPECT_EQ(ConceptsFT::supported_specialization,testFunctions.setExternalConceptResult(ConceptsFT::setTestResult)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::g_test_result));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::g_test_result_int,
                                  ConceptsFT::g_test_result_int_expected));
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
     std::function<void(ConceptType)> f(ConceptsFT::staticMemberPointer);
     // go through the specialization for to call the std::function, this is what we are testing
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(f)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif // UNIT_TEST_010105
#ifdef UNIT_TEST_010106
/**
 @brief Tests the concept eds::a_regular_function_pointer against
 ConceptsFT::setConceptResult using function ConceptsFT::testAMemberPointer test
 ConceptsFT.UT010106

@anchor edsUGTest.ConceptsFT.UT010106

@test Test Explorer: edsUGTest->ConceptsFT->UT010106
@ref edsUGTest.ConceptsFT.UT010106

@sa UT010106_setConceptResult

[The targeted function if the test case is successful](@ref UT010106_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010106
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
class ConceptsFT_UT010106_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010106);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010106);
void ConceptsFT_UT010106_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     // create a std::function<void()> from a static member function with parameters
     auto functional = std::make_unique<std::function<void(ConceptType)>>(ConceptsFT::staticMemberPointer);
     //std::function<void(ConceptType)> f(ConceptsFT::staticMemberPointer);
     // go through the specialization for to call the std::function, this is what we are testing
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(functional)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_unique_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010106
#ifdef UNIT_TEST_010107
/**
 @brief Tests the concept eds::a_regular_function_pointer against
 ConceptsFT::setConceptResult using function ConceptsFT::testAMemberPointer test
 ConceptsFT.UT010107

@anchor edsUGTest.ConceptsFT.UT010107

@test Test Explorer: edsUGTest->ConceptsFT->UT010107
@ref edsUGTest.ConceptsFT.UT010107

@sa UT010107_setConceptResult

[The targeted function if the test case is successful](@ref UT010106_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010107
@sa unit_test_concepts_page
@sa Test
@sa eds::a_functional_lvalue
@sa ConceptType
 */
class ConceptsFT_UT010107_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010107);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010107);
void ConceptsFT_UT010107_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     // create a std::function<void()> from a static member function with parameters
     auto functional = std::make_shared<std::function<void(ConceptType)>>(ConceptsFT::staticMemberPointer);
     //std::function<void(ConceptType)> f(ConceptsFT::staticMemberPointer);
     // go through the specialization for to call the std::function, this is what we are testing
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(functional)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_shared_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010107
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult([](ConceptType a) noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = a;
     })));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue));
}
#endif // UNIT_TEST_010110
#ifdef UNIT_TEST_010111
/**
 @brief Tests the concept eds::a_lambda_rvalue against
 ConceptsFT::setConceptResult using inline lambda to test
 ConceptsFT.UT010111

@anchor edsUGTest.ConceptsFT.UT010111

@test Test Explorer: edsUGTest->ConceptsFT->UT010111
@ref edsUGTest.ConceptsFT.UT010111

@sa UT010111_setConceptResult

[The targeted function if the test case is successful](@ref UT010111_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010111
@sa unit_test_concepts_page
@sa Test
@sa eds::a_lambda_rvalue
@sa ConceptType
 */
class ConceptsFT_UT010111_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010111);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010111);
void ConceptsFT_UT010111_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [](ConceptType a) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif // UNIT_TEST_010111
#ifdef UNIT_TEST_010112
/**
 @brief Tests the concept eds::a_lambda_rvalue against
 ConceptsFT::setConceptResult using inline lambda to test
 ConceptsFT.UT010112

@anchor edsUGTest.ConceptsFT.UT010112

@test Test Explorer: edsUGTest->ConceptsFT->UT010112
@ref edsUGTest.ConceptsFT.UT010112

@sa UT010112_setConceptResult

[The targeted function if the test case is successful](@ref UT010112_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010112
@sa unit_test_concepts_page
@sa Test
@sa eds::a_lambda_rvalue
@sa ConceptType
 */
class ConceptsFT_UT010112_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010112);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010112);
void ConceptsFT_UT010112_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambdaptr = std::make_unique<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambdaptr)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_unique_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010112
#ifdef UNIT_TEST_010113
/**
 @brief Tests the concept eds::a_lambda_rvalue against
 ConceptsFT::setConceptResult using inline lambda to test
 ConceptsFT.UT010113

@anchor edsUGTest.ConceptsFT.UT010113

@test Test Explorer: edsUGTest->ConceptsFT->UT010113
@ref edsUGTest.ConceptsFT.UT010113

@sa UT010113_setConceptResult

[The targeted function if the test case is successful](@ref UT010113_setConceptResult)

ConceptFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::functionalLValue

@anchor UT010113
@sa unit_test_concepts_page
@sa Test
@sa eds::a_lambda_rvalue
@sa ConceptType
 */
class ConceptsFT_UT010113_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010113);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010113);
void ConceptsFT_UT010113_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambdaptr = std::make_shared<std::function<void(ConceptType)>>(
         [](ConceptType a) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = a;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambdaptr)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_shared_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010113
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
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif
#ifdef UNIT_TEST_010116
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010116

@anchor edsUGTest.ConceptsFT.UT010116

@test Test Explorer: edsUGTest->ConceptsFT->UT010116
@ref edsUGTest.ConceptsFT.UT010116

@sa UT010115_setConceptResult

[The targeted function if the test case is successful](@ref UT010116_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010116
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
class ConceptsFT_UT010116_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010116);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010116);
void ConceptsFT_UT010116_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
         });
     auto lambda_ptr = std::make_unique<decltype(lambda)>(std::move(lambda));
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda_ptr)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_unique_ptr_functional_lvalue));
}
#endif
#ifdef UNIT_TEST_010117
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010117

@anchor edsUGTest.ConceptsFT.UT010117

@test Test Explorer: edsUGTest->ConceptsFT->UT010117
@ref edsUGTest.ConceptsFT.UT010117

@sa UT010117_setConceptResult

[The targeted function if the test case is successful](@ref UT010117_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |    VARIABLE       |     EXPECT
 ------ | ----------------- | ----------------
 000010 | sm_FunctionCalled | true
 000020 | sm_ConceptType    | ConceptType::a_regular_function_pointer

@anchor UT010117
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
class ConceptsFT_UT010117_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010117);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010117);
void ConceptsFT_UT010117_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
         });
     auto lambda_ptr = std::make_shared<decltype(lambda)>(std::move(lambda));
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda_ptr)));
     EDS_PROBEW(000010, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000020,
                EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_shared_ptr_functional_lvalue));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(
         [&testFunctions](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         })));
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_lambda_rvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_lambda_rvalue));
}
#endif
#ifdef UNIT_TEST_010121
// clang-format off
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010121

@anchor edsUGTest.ConceptsFT.UT010121

@test Test Explorer: edsUGTest->ConceptsFT->UT010121
@ref edsUGTest.ConceptsFT.UT010121

@sa UT010121_setConceptResult

Requires the compiler support for p288R9.

[The targeted function if the test case is successful](@ref UT010121_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_regular_function_pointer
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_regular_function_pointer

@anchor UT010121
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010121_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010121);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010121);
void ConceptsFT_UT010121_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda_function = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [&testFunctions](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda_function)));
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_functional_lvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
}
#endif // UNIT_TEST_010121
#ifdef UNIT_TEST_010122
// clang-format off
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010122

@anchor edsUGTest.ConceptsFT.UT010122

@test Test Explorer: edsUGTest->ConceptsFT->UT010122
@ref edsUGTest.ConceptsFT.UT010122

@sa UT010122_setConceptResult

[The targeted function if the test case is successful](@ref UT010122_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_regular_function_pointer
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_regular_function_pointer

@anchor UT010122
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010122_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010122);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010122);
void ConceptsFT_UT010122_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda_function = std::make_unique<std::function<void(ConceptType)>>(
         [&testFunctions](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda_function)));
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_unique_ptr_functional_lvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_unique_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010122
#ifdef UNIT_TEST_010123
// clang-format off
/**
 @brief Tests the concept eds::a_regular_function_pointer with a template parameter on
 ConceptsFT::TestRegularFunction::setConceptResult using function
ConceptsFT::testAMemberPointer test ConceptsFT.UT010123

@anchor edsUGTest.ConceptsFT.UT010123

@test Test Explorer: edsUGTest->ConceptsFT->UT010123
@ref edsUGTest.ConceptsFT.UT010123

@sa UT010123_setConceptResult

[The targeted function if the test case is successful](@ref UT010123_setConceptResult)

ConceptsFT::setConceptResult is a templated function using a concept to route the call
parameter to the correct version of the template. The parameter is a function that is called
and pass the correct test id to set sm_ConceptType.The expected output can be seen in the
table below.

 PROBE  |                   VARIABLE                        |     EXPECT
 ------ | ------------------------------------------------- | ----------------
 000020 | ConceptsFT::TestRegularFunctions<>::m_test_result | ConceptType::a_regular_function_pointer
 000020 | sm_FunctionCalled                                 | true
 000030 | sm_ConceptType                                    | ConceptType::a_regular_function_pointer

@anchor UT010123
@sa unit_test_concepts_page
@sa Test
@sa eds::a_regular_function_pointer
@sa ConceptType
 */
// clang-format on
class ConceptsFT_UT010123_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010123);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010123);
void ConceptsFT_UT010123_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto lambda_function = std::make_unique<std::function<void(ConceptType)>>(
         [&testFunctions](ConceptType concept_type) noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda_function)));
     EDS_PROBEW(000010, EXPECT_EQ(testFunctions.m_test_result, ConceptType::a_unique_ptr_functional_lvalue));
     EDS_PROBEW(000020, EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBEW(000030, EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_unique_ptr_functional_lvalue));
}
#endif // UNIT_TEST_010123
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

Requires the compiler support for p288R9.

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
     auto functional = EDS_CONSERVATIVE_FUNCTION<void(ConceptType)>(
         [&testFunctions](ConceptType concept_type) EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = concept_type;
              testFunctions.m_test_result = concept_type;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(functional)));
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
     #pragma message(EDS_WARNING(__FILE__,__LINE__,EDS_1001(CLASS,Object_Pointer)))
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization, testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::memberFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
#endif
#ifdef UNIT_TEST_010131
class ConceptsFT_UT010131_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010131);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010131);
void ConceptsFT_UT010131_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_unique<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, &ConceptsFT::TestMember::memberFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
#endif
#ifdef UNIT_TEST_010132
class ConceptsFT_UT010132_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010132);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010132);
void ConceptsFT_UT010132_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_shared<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, &ConceptsFT::TestMember::memberFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
#endif
#ifdef UNIT_TEST_010133
/** Test detection of disallowed call passing a pointer to a copyable class */
class ConceptsFT_UT010133_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010133);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010133);
void ConceptsFT_UT010133_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMemberCopyable testMemberCopyable;
     EDS_PROBEW(100010,EXPECT_EQ(forbidden_specialization, testFunctions.setConceptResult(&testMemberCopyable, &ConceptsFT::TestMemberCopyable::memberFunction)));
}
#endif
#ifdef UNIT_TEST_010134
/** Test detection of disallowed call passing a pointer to a copyable class */
class ConceptsFT_UT010134_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010134);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010134);
void ConceptsFT_UT010134_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMemberCopyable testMemberMoveable;
     EDS_PROBEW(100010,EXPECT_EQ(forbidden_specialization, testFunctions.setConceptResult(&testMemberMoveable, &ConceptsFT::TestMemberMoveable::memberFunction)));
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
     auto functional = std::mem_fn(&ConceptsFT::TestMember::memberFunction);
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(&testMember, functional)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
class ConceptsFT_UT010136_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010136);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010136);
void ConceptsFT_UT010136_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_unique<ConceptsFT::TestMember>();
     auto functional = std::mem_fn(&ConceptsFT::TestMember::memberFunction);
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, functional)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
class ConceptsFT_UT010137_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010137);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010137);
void ConceptsFT_UT010137_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_shared<ConceptsFT::TestMember>();
     auto functional = std::mem_fn(&ConceptsFT::TestMember::memberFunction);
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, functional)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_functional_lvalue));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(&testMember,
                                    &ConceptsFT::TestMember::memberConstFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
class ConceptsFT_UT010141_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010141);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010141);
void ConceptsFT_UT010141_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_unique<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember,
                                    &ConceptsFT::TestMember::memberConstFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember->isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember->isConstMember()));
}
class ConceptsFT_UT010142_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010142);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010142);
void ConceptsFT_UT010142_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto testMember = std::make_shared<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember,
                                    &ConceptsFT::TestMember::memberConstFunction)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
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
     ConceptsFT::TestRegularFunctions<> testFunctions;
     // go through the specialization for to call the std::function, this is what we are testing
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(ConceptsFT::staticMemberPointerNoParams)));
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
     std::function<void()> f(staticMemberPointerNoParams);
     // go through the specialization for to call the std::function, this is what we are testing
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(f)));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult([]() noexcept -> void {
          ConceptsFT::sm_FunctionCalled = true;
          ConceptsFT::sm_ConceptType = ConceptType::a_lambda_rvalue_without_parameters;
     })));
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
     ConceptsFT::TestRegularFunctions<> testFunctions;
     auto lambda = EDS_CONSERVATIVE_FUNCTION<void() noexcept>(
         []() EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(lambda)));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(
         [&testFunctions]() noexcept -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_lambda_rvalue_without_parameters;
              testFunctions.m_test_result = ConceptType::a_lambda_rvalue_without_parameters;
         })));
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
     auto functional = EDS_CONSERVATIVE_FUNCTION<void() noexcept>(
         [&testFunctions]() EDS_LAMBDA_NOEXCEPT -> void {
              ConceptsFT::sm_FunctionCalled = true;
              ConceptsFT::sm_ConceptType = ConceptType::a_functional_lvalue_without_parameters;
              testFunctions.m_test_result = ConceptType::a_functional_lvalue_without_parameters;
         });
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(functional)));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
class ConceptsFT_UT010231_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010231);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010231);
void ConceptsFT_UT010231_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     auto testMember = std::make_unique<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, &ConceptsFT::TestMember::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember->isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember->isConstMember()));
}
class ConceptsFT_UT010232_Test : public ConceptsFT {
     EDS_DCL_GTEST_INTERNALS(ConceptsFT, UT010232);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(ConceptsFT, UT010232);
void ConceptsFT_UT010232_Test::TestBody() {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     auto testMember = std::make_shared<ConceptsFT::TestMember>();
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(testMember, &ConceptsFT::TestMember::memberFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
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
     auto functional = std::mem_fn(&ConceptsFT::TestMember::memberFunctionNoParams);
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(&testMember, functional)));
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
     EDS_PROBEW(100000,EXPECT_EQ(supported_specialization,testFunctions.setConceptResult(&testMember,
                                    &ConceptsFT::TestMember::memberConstFunctionNoParams)));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::a_const_member_function_pointer_without_parameters));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
#endif
