#if defined(EDSMSVSBUILD)
     #include "pch.h"
#else
     #include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/event/delegate.hpp"
//#define UNIT_TEST_080100 UT080100
#define UNIT_TEST_080101 UT080101
#define UNIT_TEST_080102 UT080102
#define UNIT_TEST_080103 UT080103
#define UNIT_TEST_080104 UT080104
#define UNIT_TEST_080105 UT080105
#define UNIT_TEST_080106 UT080106
#define UNIT_TEST_080107 UT080107
#define UNIT_TEST_080110 UT080110
#define UNIT_TEST_080111 UT080111
#define UNIT_TEST_080112 UT080112
#define UNIT_TEST_080113 UT080113
#define UNIT_TEST_080115 UT080115
#define UNIT_TEST_080116 UT080116
#define UNIT_TEST_080117 UT080117
#define UNIT_TEST_080120 UT080120
#define UNIT_TEST_080121 UT080121
#define UNIT_TEST_080122 UT080122
#define UNIT_TEST_080123 UT080123
#define UNIT_TEST_080125 UT080125
#define UNIT_TEST_080130 UT080130
#define UNIT_TEST_080131 UT080131
#define UNIT_TEST_080132 UT080132
#define UNIT_TEST_080133 UT080133
#define UNIT_TEST_080134 UT080134
#define UNIT_TEST_080135 UT080135
#define UNIT_TEST_080140 UT080140
#define UNIT_TEST_080200 UT080200
#define UNIT_TEST_080205 UT080205
#define UNIT_TEST_080210 UT080210
#define UNIT_TEST_080215 UT080215
#define UNIT_TEST_080220 UT080220
#define UNIT_TEST_080225 UT080225
#define UNIT_TEST_080230 UT080230
#define UNIT_TEST_080235 UT080235
#define UNIT_TEST_080240 UT080240
class DelegateFT : public ::testing::Test {
   protected:
     DelegateFT() {}
     ~DelegateFT() override {}
     void SetUp() override {
          sm_total = 0;
          sm_FunctionCalled = false;
          sm_ConceptType = ConceptType::none;
     }
     void TearDown() override {}
     /** @brief enumerated types of functions for probes to test. */
     enum class ConceptType : int {
          a_regular_static_function_pointer,
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
     static bool sm_FunctionCalled;
     static ConceptType sm_ConceptType;
     static int sm_total;
     /**
      * @brief A static function that can be passed as a function pointer or std::function
      *
      * @param p_concept_type The concept that can be set and tested to make sure this function
      * is routed to the proper caller.
      */
     static void staticMemberPointer(int _count) noexcept {
          sm_FunctionCalled = true;
          sm_ConceptType = ConceptType::a_regular_static_function_pointer;
          sm_total += _count;
     }
};

bool DelegateFT::sm_FunctionCalled = false;
DelegateFT::ConceptType DelegateFT::sm_ConceptType = DelegateFT::ConceptType::none;
int DelegateFT::sm_total = 0;
#ifdef UNIT_TEST_080100
/**
 * @brief Test that a delegate with parameters can accept a qualified function pointer.
 * 
 * @anchor edsUGTest.DelegateFT.UT080100
 * 
 * @sa DelegateFT::staticMemberPointer
 * @anchor UT080100
 * @sa unit_test_concepts_page
 * @sa Test
 */
class DelegateFT_UT080100_Test : public DelegateFT {
     EDS_DCL_GTEST_INTERNALS(DelegateFT, UT080100);
     using test_delegate_t = eds::Delegate<void(int) noexcept>;
     static constexpr int test_input_value = 5; // The value to pass to the function
     static constexpr int test_expected_value = 5; // The expected value after the 
                                                   // function is called
     static constexpr int test_expected_use_count = 1; // The expected use count of the 
                                                       // shared pointer
     // Create the delegate with the static function pointer that we will test
     test_delegate_t test_delegate = test_delegate_t::make_delegate(staticMemberPointer);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(DelegateFT, UT080100);
void DelegateFT_UT080100_Test::TestBody() {
     test_delegate(test_input_value); // This is the test call to the function
     EDS_PROBEW(100000,EXPECT_EQ(DelegateFT::sm_ConceptType,DelegateFT::ConceptType::a_regular_static_function_pointer));
     EDS_PROBEW(100005,EXPECT_TRUE(DelegateFT::sm_FunctionCalled));
     EDS_PROBEW(100010,EXPECT_EQ(DelegateFT_UT080100_Test::test_expected_value,DelegateFT::sm_total));
     EDS_PROBEW(100015,EXPECT_EQ(DelegateFT_UT080100_Test::test_expected_use_count,test_delegate.get_use_count()));
     EDS_PROBEW(100020,EXPECT_TRUE(test_delegate == DelegateFT::staticMemberPointer));
}
#endif
