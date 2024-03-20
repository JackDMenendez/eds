#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "ConceptsUGTest.h"
#include "custom_gtest.hpp"
#include "private/eds_concepts.hpp"
#include <memory>
#include <private/eds_env.hpp>
#define UT01 1
#define UT02 2
#define UT03 3
#define UT04 4
#define UT05 5
#define UT06 6
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
          TestRegularFunctions() noexcept = default;
          template <typename FUNC>
               requires eds::a_function<FUNC> && eds::has_noexcept<FUNC>
          void setConceptResult(FUNC const *pointer_to_function) const noexcept {
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
          void setConceptResult(FUNC &&f) const noexcept {
               f(ConceptType::regular_function);
          }
          template <typename FUNC>
               requires eds::SomeClassType<FUNC>
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
