#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_traits.hpp"
#include <memory>
#include <private/eds_env.hpp>
#include <functional>
class TraitsFT : public ::testing::Test {
   public:
     enum class TraitType : int { regular_function, lambda_functor, member_pointer, function_pointer, none };
     TraitsFT() noexcept = default;
     ~TraitsFT() noexcept override = default;
     void SetUp() override { sm_ConceptType = TraitType::none; }
     void TearDown() override {
          // Nothing to do so far
     }
     static TraitType sm_ConceptType;
     static void setRegularFunction() noexcept {
          sm_ConceptType = TraitType::function_pointer;
     }
     static void setRegularFunction(TraitType a) noexcept { sm_ConceptType = a; }
     using TestFunction_t = void(TraitType) noexcept;
     using FunctionalTestFunction_t = std::function<void(TraitType) noexcept>;
     using TestFunctionNoParms_t = void() noexcept;
     using FunctionalTestFunctionNoParms_t = std::function<void() noexcept>;
     template <class CLASS>
     using TestMember_t = void(CLASS::*)(TraitType) noexcept;
     template <class CLASS>
     using FunctionalTestMember_t = std::function<void(CLASS::*)(TraitType) noexcept>;
     template <class CLASS>
     using TestMemberConst_t = void(CLASS::*)(TraitType) const noexcept;
     template <class CLASS>
     using FunctionalTestMemberConst_t = std::function<void(CLASS::*)(TraitType) const noexcept>;
     template <class CLASS>
     using TestMemberNoParams_t = void(CLASS::*)() noexcept;
     template <class CLASS>
     using FunctionalTestMemberNoParams_t = std::function<void(CLASS::*)() noexcept>;
     template <class CLASS>
     using TestMemberNoParamsConst_t = void(CLASS::*)() const noexcept;
     template <class CLASS>
     using FunctionalTestMemberNoParamsConst_t = std::function<void(CLASS::*)() const noexcept>;
     // template<class...>
     // class TestRegularFunctions;
     template <typename... PARAMS> class TestRegularFunctions {
        public:
          TraitType m_ConceptType = TraitType::none;
          TestRegularFunctions() noexcept = default;
          void setMemberFunction() noexcept { m_ConceptType = TraitType::member_pointer; }
          void setMemberFunction(TraitType a) noexcept { m_ConceptType = a; }
          template <typename FUNC>
          void setConceptResult(FUNC const *pointer_to_function) const noexcept {
               static_assert(!std::is_member_function_pointer_v<FUNC>);
               static_assert(!std::is_member_object_pointer_v<FUNC>);

               static_assert(!std::is_pointer_v<FUNC>);
               static_assert(!std::is_member_pointer_v<FUNC>);
               static_assert(
                   std::is_function_v<std::remove_pointer_t<decltype(pointer_to_function)>>);
               static_assert(std::is_pointer_v<decltype(pointer_to_function)>);
               // make the call to the callback function
               pointer_to_function(TraitType::function_pointer);
          }
          template <typename FUNC>
          void setBlindConceptResult(FUNC const *pointer_to_function) const noexcept {
               pointer_to_function();
          }
          template <class CLASS, class FUNC> 
          void setConceptResult(CLASS*class_instance, FUNC *f) noexcept {
               f(TraitType::regular_function);
          }
          template <typename FUNC> 
          void setConceptResult(FUNC &&f) const noexcept {
               f(TraitType::regular_function);
          }
          ~TestRegularFunctions() noexcept = default;
     };
};
TraitsFT::TraitType TraitsFT::sm_ConceptType = TraitType::none;
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsNoexceptParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsVoidRCParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<TestFunction_t>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<TestFunction_t>::is_constant_v));
}
//--------------------------------------------------------------------------------------------------- 
/*
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsNoexceptParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsVoidRCParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionalFunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<FunctionalTestFunction_t>::is_constant_v));
}
*/
//--------------------------------------------------------------------------------------------------- 
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsNoexceptParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsVoidRCParams) {
     EDS_PROBE(
         EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(
         EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(
         EXPECT_FALSE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsEligibleParams) {
     EDS_PROBE(
         EXPECT_FALSE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_constant_v));
}
//--------------------------------------------------------------------------------------------------- 
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<TestMember_t<TestRegularFunctions<TraitType>>>::is_constant_v));
}
//--------------------------------------------------------------------------------------------------- 
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParams) {
     EDS_PROBE(EXPECT_FALSE(eds::FunctionTypeChecker<TestMemberNoParams_t<TestRegularFunctions<>>>::is_constant_v));
}
//--------------------------------------------------------------------------------------------------- 
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_constant_v));
}
//--------------------------------------------------------------------------------------------------- 
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_noexcept_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_return_code_void_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_eligible_delegate_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_member_function_v));
}
EDS_GTESTF(TraitsUGTest, TraitsFT, FunctionTypeCheckerIsMemberFunctionNoParamsConst) {
     EDS_PROBE(EXPECT_TRUE(eds::FunctionTypeChecker<TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_constant_v));
}
