#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_concepts.hpp"
#include <memory>
#include <private/eds_env.hpp>
#include <functional>
class ConceptsFT : public ::testing::Test {
   public:
     enum class ConceptType : int { regular_function, lambda_functor, functionalLValue, function_pointer, member, none };
     ConceptsFT() noexcept = default;
     ~ConceptsFT() noexcept override = default;
     void SetUp() override {
          sm_ConceptType = ConceptType::none;
          sm_FunctionCalled = false;
     }
     void TearDown() override {
          // Nothing to do so far
     }
     static ConceptType sm_ConceptType;
     static bool sm_FunctionCalled;
     static void setRegularFunction(ConceptType a) noexcept { sm_ConceptType = a; }
     static void setRegularFunctionNoParams() noexcept {
          sm_FunctionCalled=true;
          sm_ConceptType = ConceptType::member;
     }
     using TestFunction_t = void(ConceptType) noexcept;
     class TestMember {
           bool m_member = false;
           mutable bool m_const_member = false;
        public:
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          void setRegularFunction(ConceptType a) noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_member = true;
          }
          void setRegularFunctionConst(ConceptType a) const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = a;
               m_const_member = true;
          }
          void setRegularFunctionNoParams() noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::member;
               m_member = true;
          }
          void setRegularFunctionNoParamsConst() const noexcept {
               ConceptsFT::sm_FunctionCalled = true;
               ConceptsFT::sm_ConceptType = ConceptType::member;
               m_const_member = true;
          }
     };

     // template<class...>
     // class TestRegularFunctions;
     template <typename... PARAMS> class TestRegularFunctions {
        public:
          ConceptType m_conceptType = ConceptType::none;
          TestRegularFunctions() noexcept = default;
          template <typename FUNC>
               requires eds::a_function<FUNC> && eds::has_noexcept<FUNC> &&
                        eds::has_void_return_code<FUNC> && eds::eligible_delegate<FUNC>
          void setConceptResult(FUNC *pointer_to_function) const noexcept {
               static_assert(!std::is_member_function_pointer_v<FUNC>);
               static_assert(!std::is_member_object_pointer_v<FUNC>);

               static_assert(!std::is_pointer_v<FUNC>);
               static_assert(!std::is_member_pointer_v<FUNC>);
               static_assert(
                   std::is_function_v<std::remove_pointer_t<decltype(pointer_to_function)>>);
               static_assert(std::is_pointer_v<decltype(pointer_to_function)>);
               // make the call to the callback function
               pointer_to_function(ConceptType::function_pointer);
          }
          template <typename FUNC>
              requires eds::RegularFunction<FUNC, PARAMS...>
          void setConceptResult(FUNC &f) const noexcept {
               f(ConceptType::regular_function);
          }
          template <typename FUNC>
               requires std::is_invocable_v<FUNC, ConceptType>
                  && std::is_move_assignable_v<FUNC>
                  //&& eds::FunctionTypeChecker<FUNC>::is_eligible_delegate_v
          void setConceptResult(FUNC &f) const noexcept {
               f(ConceptType::functionalLValue);
          }
          template <typename FUNC>
               requires eds::RegularFunction<FUNC, PARAMS...>
          void setConceptResult(FUNC &&f) const noexcept {
               f(ConceptType::regular_function);
          }
          template<class CLASS, typename FUNC>
               requires eds::some_class_type<CLASS> 
                    &&  eds::FunctionTypeChecker<FUNC>::is_eligible_delegate_v
                    &&(!eds::FunctionTypeChecker<FUNC>::is_constant_v)
                    &&  eds::a_member_function<CLASS, FUNC, PARAMS...>
                    && (eds::FunctionTypeChecker<FUNC>::num_params > 0)
                    && (eds::FunctionTypeChecker<FUNC>::num_params == sizeof...(PARAMS))
          void setConceptResult(CLASS *object, FUNC f) const noexcept {
                (object->*f)(ConceptType::member);
          }
          template<class CLASS, typename FUNC>
               requires eds::some_class_type<CLASS> 
                    &&  eds::FunctionTypeChecker<FUNC>::is_eligible_delegate_v
                    &&  eds::FunctionTypeChecker<FUNC>::is_constant_v
                    &&  eds::a_member_function<CLASS, FUNC, PARAMS...>
                    &&  (eds::FunctionTypeChecker<FUNC>::num_params > 0)
                    &&  (eds::FunctionTypeChecker<FUNC>::num_params == sizeof...(PARAMS))
          void setConceptResult(const CLASS *object, FUNC f) const noexcept {
                (object->*f)(ConceptType::member);
          }

          template <typename FUNC>
               requires eds::some_class_type<FUNC> &&
                        eds::a_functor_with_void_rc<FUNC, ConceptType>
          void setConceptResult(FUNC &&f) const noexcept {
               f(ConceptType::lambda_functor);
          }
          ~TestRegularFunctions() noexcept = default;
     };
     template <> class TestRegularFunctions<> {
        public:
          ConceptType m_conceptType = ConceptType::none;
          TestRegularFunctions() noexcept = default;
          template <typename FUNC>
               requires eds::a_function<FUNC> && eds::has_noexcept<FUNC> &&
                        eds::has_void_return_code<FUNC> && eds::eligible_delegate<FUNC>
          void setConceptResult(FUNC *pointer_to_function) const noexcept {
               static_assert(!std::is_member_function_pointer_v<FUNC>);
               static_assert(!std::is_member_object_pointer_v<FUNC>);

               static_assert(!std::is_pointer_v<FUNC>);
               static_assert(!std::is_member_pointer_v<FUNC>);
               static_assert(
                   std::is_function_v<std::remove_pointer_t<decltype(pointer_to_function)>>);
               static_assert(std::is_pointer_v<decltype(pointer_to_function)>);
               // make the call to the callback function
               pointer_to_function();
               sm_ConceptType = ConceptType::function_pointer;
               sm_FunctionCalled = true;
          }
          template <typename FUNC>
               requires eds::RegularFunction<FUNC>
          void setConceptResult(FUNC &f) const noexcept {
               f();
               sm_ConceptType = ConceptType::regular_function;
          }template <typename FUNC>
               requires eds::RegularFunction<FUNC>
          void setConceptResult(FUNC &&f) const noexcept {
               f();
               sm_ConceptType = ConceptType::regular_function;
          }
          template<class CLASS, typename FUNC>
               requires eds::some_class_type<CLASS> 
                    &&  eds::FunctionTypeChecker<FUNC>::is_eligible_delegate_v
                    &&(!eds::FunctionTypeChecker<FUNC>::is_constant_v)
                    &&  eds::a_member_function<CLASS, FUNC>
                    && (eds::FunctionTypeChecker<FUNC>::num_params == 0)
          void setConceptResult(CLASS *object, FUNC f) const noexcept {
                (object->*f)();
          }
          template<class CLASS, typename FUNC>
               requires eds::some_class_type<CLASS> 
                    &&  eds::FunctionTypeChecker<FUNC>::is_eligible_delegate_v
                    &&  eds::FunctionTypeChecker<FUNC>::is_constant_v
                    &&  eds::a_member_function<CLASS, FUNC>
                    &&  (eds::FunctionTypeChecker<FUNC>::num_params == 0)
          void setConceptResult(const CLASS *object, FUNC f) const noexcept {
                (object->*f)();
          }
          template <typename FUNC>
               requires eds::some_class_type<FUNC> &&
                        eds::a_functor_with_void_rc<FUNC>
          void setConceptResult(FUNC &&f) const noexcept {
               f();
               sm_ConceptType = ConceptType::lambda_functor;
          }
          ~TestRegularFunctions() noexcept = default;
     };
};
ConceptsFT::ConceptType ConceptsFT::sm_ConceptType = ConceptType::none;
bool ConceptsFT::sm_FunctionCalled = false;

EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionPointer) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(ConceptsFT::setRegularFunction);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::function_pointer));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionalFunctionPointer) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     std::function<void(ConceptType)> f(ConceptsFT::setRegularFunction);
     testFunctions.setConceptResult(f);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::functionalLValue));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult([](ConceptType a) noexcept ->void { ConceptsFT::sm_ConceptType = a; });
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::lambda_functor));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionalLambdaFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto f = std::move_only_function<void(ConceptType)>([](ConceptType a) noexcept -> void { ConceptsFT::sm_ConceptType = a; });
     testFunctions.setConceptResult(f);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::functionalLValue));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(
         [&testFunctions](ConceptType a) noexcept -> void { testFunctions.m_conceptType = a; });
     EDS_PROBE(EXPECT_EQ(testFunctions.m_conceptType, ConceptType::lambda_functor));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionalLambdaCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     auto f = std::move_only_function<void(ConceptType)>([&testFunctions](ConceptType a) noexcept -> void { testFunctions.m_conceptType = a; });
     testFunctions.setConceptResult(f);
     EDS_PROBE(EXPECT_EQ(testFunctions.m_conceptType, ConceptType::functionalLValue));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, MemberCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunction);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::member));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionalMemberCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunction);
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunction);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::member));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_TRUE(testMember.isMember()));
     EDS_PROBE(EXPECT_FALSE(testMember.isConstMember()));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, MemberCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunctionConst);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::member));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionPointerNoParams) {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     testFunctions.setConceptResult(ConceptsFT::setRegularFunctionNoParams);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::function_pointer));
     EDS_PROBE(EXPECT_TRUE(sm_FunctionCalled));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaFunctionNoParams) {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     testFunctions.setConceptResult([]() ->void { ConceptsFT::sm_FunctionCalled = true; });
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::lambda_functor));
     EDS_PROBE(EXPECT_TRUE(sm_FunctionCalled));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaCaptureFunctionNoParams) {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     testFunctions.setConceptResult([&testFunctions]() -> void {
          testFunctions.m_conceptType = ConceptType::lambda_functor;
          sm_FunctionCalled = true;
     });
     EDS_PROBE(EXPECT_EQ(testFunctions.m_conceptType, ConceptType::lambda_functor));
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::lambda_functor));
     EDS_PROBE(EXPECT_TRUE(sm_FunctionCalled));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, MemberCaptureFunctionNoParams) {
     ConceptsFT::TestRegularFunctions<> testFunctions;
     ConceptsFT::TestMember testMember;
     testFunctions.setConceptResult(&testMember, &ConceptsFT::TestMember::setRegularFunctionNoParamsConst);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::member));
     EDS_PROBE(EXPECT_TRUE(ConceptsFT::sm_FunctionCalled));
     EDS_PROBE(EXPECT_FALSE(testMember.isMember()));
     EDS_PROBE(EXPECT_TRUE(testMember.isConstMember()));
}
