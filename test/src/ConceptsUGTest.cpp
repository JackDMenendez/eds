#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_concepts.hpp"
#include <memory>
#include <private/eds_env.hpp>
class ConceptsFT : public ::testing::Test {
   public:
     enum class ConceptType : int { regular_function, lambda_functor, function_pointer, none };
     ConceptsFT() noexcept = default;
     ~ConceptsFT() noexcept override = default;
     void SetUp() override { sm_ConceptType = ConceptType::none; }
     void TearDown() override {
          // Nothing to do so far
     }
     static ConceptType sm_ConceptType;
     static void setRegularFunction(ConceptType a) noexcept { sm_ConceptType = a; }
     using TestFunction_t = void(ConceptType) noexcept;
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
          }template <typename FUNC>
               requires eds::RegularFunction<FUNC, PARAMS...>
          void setConceptResult(FUNC &&f) const noexcept {
               f(ConceptType::regular_function);
          }
          template <typename FUNC>
               requires eds::some_class_type<FUNC> &&
                        eds::a_functor_with_void_rc<FUNC, ConceptType>
          void setConceptResult(FUNC &&f) const noexcept {
               f(ConceptType::lambda_functor);
          }
          ~TestRegularFunctions() noexcept = default;
     };
};
ConceptsFT::ConceptType ConceptsFT::sm_ConceptType = ConceptType::none;
EDS_GTESTF(ConceptsUGTest, ConceptsFT, FunctionPointer) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(ConceptsFT::setRegularFunction);
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::function_pointer));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult([](ConceptType a) ->void { ConceptsFT::sm_ConceptType = a; });
     EDS_PROBE(EXPECT_EQ(ConceptsFT::sm_ConceptType, ConceptType::lambda_functor));
}
EDS_GTESTF(ConceptsUGTest, ConceptsFT, LambdaCaptureFunction) {
     ConceptsFT::TestRegularFunctions<ConceptType> testFunctions;
     testFunctions.setConceptResult(
         [&testFunctions](ConceptType a) -> void { testFunctions.m_conceptType = a; });
     EDS_PROBE(EXPECT_EQ(testFunctions.m_conceptType, ConceptType::lambda_functor));
}
