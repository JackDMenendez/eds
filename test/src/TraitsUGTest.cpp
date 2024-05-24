#if defined(EDSMSVSBUILD)
     #include "pch.h"
#else
     #include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_traits.hpp"
#include <functional>
#include <memory>
#include <private/eds_env.hpp>
#define UNIT_TEST_020100 UT020100
#define UNIT_TEST_020101 UT020101
#define UNIT_TEST_020102 UT020102
#define UNIT_TEST_020103 UT020103
#define UNIT_TEST_020104 UT020104
#define UNIT_TEST_020105 UT020105
#define UNIT_TEST_020106 UT020106
#define UNIT_TEST_020107 UT020107
#define UNIT_TEST_020110 UT020110
#define UNIT_TEST_020111 UT020111
#define UNIT_TEST_020112 UT020112
#define UNIT_TEST_020113 UT020113
#define UNIT_TEST_020115 UT020115
#define UNIT_TEST_020116 UT020116
#define UNIT_TEST_020117 UT020117
#define UNIT_TEST_020120 UT020120
#define UNIT_TEST_020121 UT020121
#define UNIT_TEST_020122 UT020122
#define UNIT_TEST_020123 UT020123
#define UNIT_TEST_020125 UT020125
#define UNIT_TEST_020130 UT020130
#define UNIT_TEST_020131 UT020131
#define UNIT_TEST_020132 UT020132
#define UNIT_TEST_020133 UT020133
#define UNIT_TEST_020134 UT020134
#define UNIT_TEST_020135 UT020135
#define UNIT_TEST_020140 UT020140
#define UNIT_TEST_020145 UT020145
#define UNIT_TEST_020150 UT020150
#define UNIT_TEST_020155 UT020155
#define UNIT_TEST_020160 UT020160
#define UNIT_TEST_020165 UT020165
#define UNIT_TEST_020170 UT020170
#define UNIT_TEST_020175 UT020175
#define UNIT_TEST_020200 UT020200
#define UNIT_TEST_020205 UT020205
#define UNIT_TEST_020210 UT020210
#define UNIT_TEST_020215 UT020215
#define UNIT_TEST_020220 UT020220
#define UNIT_TEST_020225 UT020225
#define UNIT_TEST_020230 UT020230
#define UNIT_TEST_020235 UT020235
#define UNIT_TEST_020240 UT020240
class TraitsFT : public ::testing::Test {
   public:
     struct Alpha {};

     class Beta {};

     enum class Epsilon {};

     union Upsilon {
          class UpsilonGama {};
     };
     enum class TraitType : int {
          a_regular_function_pointer,
          a_lambda_rvalue,
          member_pointer,
          function_pointer,
          none
     };
     static bool sm_ISaidIt;
     static TraitType sm_ConceptType;
     #ifdef P1169R4
     using static_lambda_t = decltype([]() static {
          TraitsFT::sm_ISaidIt = true;
          TraitsFT::sm_ConceptType = TraitsFT::TraitType::a_lambda_rvalue;
     });
     #endif
     class NotCopyableNotMovable {
          bool m_i_said_it = false;

        public:
          NotCopyableNotMovable() noexcept = default;
          ~NotCopyableNotMovable() noexcept = default;
          NotCopyableNotMovable(const NotCopyableNotMovable &other) noexcept = delete;
          NotCopyableNotMovable(NotCopyableNotMovable &&other) noexcept = delete;
          NotCopyableNotMovable &
          operator=(const NotCopyableNotMovable &other) noexcept = delete;
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
     TraitsFT() noexcept = default;
     ~TraitsFT() noexcept override = default;
     void SetUp() override { sm_ConceptType = TraitType::none; }
     void TearDown() override {
          // Nothing to do so far
     } // TearDown
     static void testAStaticMemberPointer() noexcept {
          sm_ConceptType = TraitType::function_pointer;
     }
     static void testAStaticMemberPointer(TraitType a) noexcept { sm_ConceptType = a; }
     using TestFunction_t = void(TraitType) noexcept;
     using FunctionalTestFunction_t = std::function<void(TraitType) noexcept>;
     using TestFunctionNoParms_t = void() noexcept;
     using FunctionalTestFunctionNoParms_t = std::function<void() noexcept>;
     template <class CLASS> using TestMember_t = void (CLASS::*)(TraitType) noexcept;
     template <class CLASS>
     using FunctionalTestMember_t = std::function<void (CLASS::*)(TraitType) noexcept>;
     template <class CLASS>
     using TestMemberConst_t = void (CLASS::*)(TraitType) const noexcept;
     template <class CLASS>
     using FunctionalTestMemberConst_t =
         std::function<void (CLASS::*)(TraitType) const noexcept>;
     template <class CLASS> using TestMemberNoParams_t = void (CLASS::*)() noexcept;
     template <class CLASS>
     using FunctionalTestMemberNoParams_t = std::function<void (CLASS::*)() noexcept>;
     template <class CLASS> using TestMemberNoParamsConst_t = void (CLASS::*)() const noexcept;
     template <class CLASS>
     using FunctionalTestMemberNoParamsConst_t =
         std::function<void (CLASS::*)() const noexcept>;
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
          void setConceptResult(CLASS *class_instance, FUNC *f) noexcept {
               f(TraitType::a_regular_function_pointer);
          }
          template <typename FUNC> void setConceptResult(FUNC &&f) const noexcept {
               f(TraitType::a_regular_function_pointer);
          }
          ~TestRegularFunctions() noexcept = default;
     };
};
bool TraitsFT::sm_ISaidIt = false;
TraitsFT::TraitType TraitsFT::sm_ConceptType = TraitType::none;
#ifdef UNIT_TEST_020100
/**
 @brief Tests the trait eds::is_copyable_v with a template parameter on
 TraitsFT::Alpha, TraitsFT::Beta, TraitsFT::Beta*, TraitsFT::Beta&, const TraitsFT::Beta,
 TraitsFT::Epsilon, int, struct S, class C.

@anchor edsUGTest.TraitsFT.UT020100

@test Test Explorer: edsUGTest->TraitsFT->UT020100

@ref edsUGTest.Traits.UT020100

@sa TraitsFT::Alpha
@sa TraitsFT::Beta
@sa TraitsFT::Epsilon

@anchor UT020100
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020100_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020100);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020100);
void TraitsFT_UT020100_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_TRUE(eds::is_class_v<TraitsFT::Alpha>));
     EDS_PROBEW(000020, EXPECT_TRUE(eds::is_class_v<TraitsFT::Beta>));
     EDS_PROBEW(000030, EXPECT_TRUE(eds::is_class_v<TraitsFT::Beta *>));
     EDS_PROBEW(000040, EXPECT_TRUE(eds::is_class_v<TraitsFT::Beta &>));
     EDS_PROBEW(000050, EXPECT_TRUE(eds::is_class_v<const TraitsFT::Beta>));
     EDS_PROBEW(000060, EXPECT_FALSE(eds::is_class_v<TraitsFT::Epsilon>));
     EDS_PROBEW(000070, EXPECT_FALSE(eds::is_class_v<int>));
     EDS_PROBEW(000080, EXPECT_TRUE(eds::is_class_v<struct S>));
     EDS_PROBEW(000090, EXPECT_TRUE(eds::is_class_v<class C>));
}
#endif // UNIT_TEST_020100
#ifdef UNIT_TEST_020105
/**
 @brief Tests the trait eds::is_copyable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020105

@test Test Explorer: edsUGTest->TraitsFT->UT020105

@ref edsUGTest.Traits.UT020105

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020105
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020105_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020105);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020105);
void TraitsFT_UT020105_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_FALSE(eds::is_copyable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020, EXPECT_FALSE(eds::is_copyable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030, EXPECT_TRUE(eds::is_copyable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040, EXPECT_TRUE(eds::is_copyable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_TRUE(eds::is_copyable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020105
#ifdef UNIT_TEST_020110
/**
 @brief Tests the trait eds::is_not_copyable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020110

@test Test Explorer: edsUGTest->TraitsFT->UT020110

@ref edsUGTest.Traits.UT020110

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020110
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020110_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020110);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020110);
void TraitsFT_UT020110_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_TRUE(eds::is_not_copyable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020, EXPECT_TRUE(eds::is_not_copyable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030, EXPECT_FALSE(eds::is_not_copyable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040, EXPECT_FALSE(eds::is_not_copyable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_FALSE(eds::is_not_copyable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020110
#ifdef UNIT_TEST_020115
/**
 @brief Tests the trait eds::is_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020115

@test Test Explorer: edsUGTest->TraitsFT->UT020115

@ref edsUGTest.Traits.UT020115

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020115
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020115_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020115);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020115);
void TraitsFT_UT020115_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_TRUE(eds::is_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020, EXPECT_FALSE(eds::is_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030, EXPECT_FALSE(eds::is_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040, EXPECT_TRUE(eds::is_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_TRUE(eds::is_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020115
#ifdef UNIT_TEST_020120
/**
 @brief Tests the trait eds::is_not_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020120

@test Test Explorer: edsUGTest->TraitsFT->UT020120

@ref edsUGTest.Traits.UT020120

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020120
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020120_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020120);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020120);
void TraitsFT_UT020120_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_FALSE(eds::is_not_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020, EXPECT_TRUE(eds::is_not_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030, EXPECT_TRUE(eds::is_not_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040, EXPECT_FALSE(eds::is_not_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_FALSE(eds::is_not_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020120
#ifdef UNIT_TEST_020125
/**
 @brief Tests the trait eds::is_not_copyable_not_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020125

@test Test Explorer: edsUGTest->TraitsFT->UT020125

@ref edsUGTest.Traits.UT020125

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020125
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020125_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020125);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020125);
void TraitsFT_UT020125_Test::TestBody() {
     EDS_PROBEW(
         000010,
         EXPECT_FALSE(eds::is_not_copyable_and_not_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(
         000020,
         EXPECT_TRUE(eds::is_not_copyable_and_not_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(
         000030,
         EXPECT_FALSE(eds::is_not_copyable_and_not_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(
         000040,
         EXPECT_FALSE(eds::is_not_copyable_and_not_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050,
                EXPECT_FALSE(eds::is_not_copyable_and_not_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020125
#ifdef UNIT_TEST_020130
/**
 @brief Tests the trait eds::is_copyable_and_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020130

@test Test Explorer: edsUGTest->TraitsFT->UT020130

@ref edsUGTest.Traits.UT020130

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020130
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020130_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020130);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020130);
void TraitsFT_UT020130_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_FALSE(eds::is_copyable_and_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020,
                EXPECT_FALSE(eds::is_copyable_and_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030,
                EXPECT_FALSE(eds::is_copyable_and_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040,
                EXPECT_TRUE(eds::is_copyable_and_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_TRUE(eds::is_copyable_and_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020130
#ifdef UNIT_TEST_020135
/**
 @brief Tests the trait eds::is_copyable_or_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020135

@test Test Explorer: edsUGTest->TraitsFT->UT020135

@ref edsUGTest.Traits.UT020135

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020135
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020135_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020135);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020135);
void TraitsFT_UT020135_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_TRUE(eds::is_copyable_or_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(000020,
                EXPECT_FALSE(eds::is_copyable_or_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030,
                EXPECT_TRUE(eds::is_copyable_or_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040, EXPECT_TRUE(eds::is_copyable_or_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050, EXPECT_TRUE(eds::is_copyable_or_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020135
#ifdef UNIT_TEST_020140
/**
 @brief Tests the trait eds::is_copyable_and_not_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020140

@test Test Explorer: edsUGTest->TraitsFT->UT020140

@ref edsUGTest.Traits.UT020140

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020140
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020140_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020140);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020140);
void TraitsFT_UT020140_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_FALSE(
                            eds::is_copyable_and_not_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(
         000020,
         EXPECT_FALSE(eds::is_copyable_and_not_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030,
                EXPECT_TRUE(eds::is_copyable_and_not_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040,
                EXPECT_FALSE(eds::is_copyable_and_not_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050,
                EXPECT_FALSE(eds::is_copyable_and_not_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020140
#ifdef UNIT_TEST_020145
/**
 @brief Tests the trait eds::is_not_copyable_and_movable_v with a template parameter on
 TraitsFT::NotCopyableNotMovable, TraitsFT::NotExplicit, TraitsFT::NotCopyableMovable,
 TraitsFT::CopyableNotMovable, TraitsFT::CopyableMovable.

@anchor edsUGTest.TraitsFT.UT020145

@test Test Explorer: edsUGTest->TraitsFT->UT020145

@ref edsUGTest.Traits.UT020145

@sa TraitsFT::NotCopyableNotMovable
@sa TraitsFT::NotExplicit
@sa TraitsFT::NotCopyableMovable
@sa TraitsFT::CopyableNotMovable
@sa TraitsFT::CopyableMovable

@anchor UT020145
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020145_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020145);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020145);
void TraitsFT_UT020145_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_TRUE(eds::is_not_copyable_and_movable_v<TraitsFT::NotCopyableMovable>));
     EDS_PROBEW(
         000020,
         EXPECT_FALSE(eds::is_not_copyable_and_movable_v<TraitsFT::NotCopyableNotMovable>));
     EDS_PROBEW(000030, EXPECT_FALSE(
                            eds::is_not_copyable_and_movable_v<TraitsFT::CopyableNotMovable>));
     EDS_PROBEW(000040,
                EXPECT_FALSE(eds::is_not_copyable_and_movable_v<TraitsFT::CopyableMovable>));
     EDS_PROBEW(000050,
                EXPECT_FALSE(eds::is_not_copyable_and_movable_v<TraitsFT::NotExplicit>));
}
#endif // UNIT_TEST_020145
#ifdef UNIT_TEST_020150
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestFunction_t

@anchor edsUGTest.TraitsFT.UT020150

@test Test Explorer: edsUGTest->TraitsFT->UT020150

@ref edsUGTest.Traits.UT020150

@sa TraitsFT::TestFunction_t
@sa eds::FunctionTypeChecker

@anchor UT020150
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020150_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020150);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020150);
void TraitsFT_UT020150_Test::TestBody() {
     EDS_PROBEW(000010, EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_function_v));
     EDS_PROBEW(000020, EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_noexcept_v));
     EDS_PROBEW(000030,
                EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_return_code_void_v));
     EDS_PROBEW(000040,
                EXPECT_TRUE(eds::FunctionTypeChecker<TestFunction_t>::is_eligible_delegate_v));
     EDS_PROBEW(000050,
                EXPECT_FALSE(eds::FunctionTypeChecker<TestFunction_t>::is_member_function_v));
     EDS_PROBEW(000060, EXPECT_FALSE(eds::FunctionTypeChecker<TestFunction_t>::is_constant_v));
}
#endif // UNIT_TEST_020150
//---------------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_020155
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestFunctionNoParams_t

@anchor edsUGTest.TraitsFT.UT020155

@test Test Explorer: edsUGTest->TraitsFT->UT020155

@ref edsUGTest.Traits.UT020155

@sa TraitsFT::TestFunctionNoParams_t
@sa eds::FunctionTypeChecker

@anchor UT020155
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020155_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020155);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020155);
void TraitsFT_UT020155_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_function_v));
     EDS_PROBEW(000020,
                EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_noexcept_v));
     EDS_PROBEW(
         000030,
         EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_return_code_void_v));
     EDS_PROBEW(
         000040,
         EXPECT_TRUE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_eligible_delegate_v));
     EDS_PROBEW(
         000050,
         EXPECT_FALSE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_member_function_v));
     EDS_PROBEW(000060,
                EXPECT_FALSE(eds::FunctionTypeChecker<TestFunctionNoParms_t>::is_constant_v));
}
#endif // UNIT_TEST_020140
//---------------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_020160
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestMember_t

@anchor edsUGTest.TraitsFT.UT020160

@test Test Explorer: edsUGTest->TraitsFT->UT020160

@ref edsUGTest.Traits.UT020160

@sa TraitsFT::TestMember_t
@sa eds::FunctionTypeChecker

@anchor UT020160
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020160_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020160);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020160);
void TraitsFT_UT020160_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_TRUE(eds::FunctionTypeChecker<
                            TestMember_t<TestRegularFunctions<TraitType>>>::is_function_v));
     EDS_PROBEW(000020,
                EXPECT_TRUE(eds::FunctionTypeChecker<
                            TestMember_t<TestRegularFunctions<TraitType>>>::is_noexcept_v));
     EDS_PROBEW(
         000030,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMember_t<TestRegularFunctions<TraitType>>>::is_return_code_void_v));
     EDS_PROBEW(
         000040,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMember_t<TestRegularFunctions<TraitType>>>::is_eligible_delegate_v));
     EDS_PROBEW(
         000050,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMember_t<TestRegularFunctions<TraitType>>>::is_member_function_v));
     EDS_PROBEW(000060,
                EXPECT_FALSE(eds::FunctionTypeChecker<
                             TestMember_t<TestRegularFunctions<TraitType>>>::is_constant_v));
}
#endif // UNIT_TEST_020160
//---------------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_020165
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestMemberNoParams_t

@anchor edsUGTest.TraitsFT.UT020165

@test Test Explorer: edsUGTest->TraitsFT->UT020165

@ref edsUGTest.Traits.UT020165

@sa TraitsFT::TestMemberNoParams_t
@sa eds::FunctionTypeChecker

@anchor UT020165
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020165_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020165);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020165);
void TraitsFT_UT020165_Test::TestBody() {
     EDS_PROBEW(000010,
                EXPECT_TRUE(eds::FunctionTypeChecker<
                            TestMemberNoParams_t<TestRegularFunctions<>>>::is_function_v));
     EDS_PROBEW(000020,
                EXPECT_TRUE(eds::FunctionTypeChecker<
                            TestMemberNoParams_t<TestRegularFunctions<>>>::is_noexcept_v));
     EDS_PROBEW(
         000030,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParams_t<TestRegularFunctions<>>>::is_return_code_void_v));
     EDS_PROBEW(
         000040,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParams_t<TestRegularFunctions<>>>::is_eligible_delegate_v));
     EDS_PROBEW(
         000050,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParams_t<TestRegularFunctions<>>>::is_member_function_v));
     EDS_PROBEW(000060,
                EXPECT_FALSE(eds::FunctionTypeChecker<
                             TestMemberNoParams_t<TestRegularFunctions<>>>::is_constant_v));
}
#endif // UNIT_TEST_020165
//---------------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_020170
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestMemberConst_t

@anchor edsUGTest.TraitsFT.UT020170

@test Test Explorer: edsUGTest->TraitsFT->UT020170

@ref edsUGTest.Traits.UT020170

@sa TraitsFT::TestMemberConst_t
@sa eds::FunctionTypeChecker

@anchor UT020170
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020170_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020170);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020170);
void TraitsFT_UT020170_Test::TestBody() {
     EDS_PROBEW(
         000010,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_function_v));
     EDS_PROBEW(
         000020,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_noexcept_v));
     EDS_PROBEW(
         000030,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_return_code_void_v));
     EDS_PROBEW(
         000040,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_eligible_delegate_v));
     EDS_PROBEW(
         000050,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_member_function_v));
     EDS_PROBEW(
         000060,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberConst_t<TestRegularFunctions<TraitType>>>::is_constant_v));
}
#endif // UNIT_TEST_020170
//---------------------------------------------------------------------------------------------------
#ifdef UNIT_TEST_020175
/**
 @brief Tests the trait eds::FunctionTypeChecker with TraitsFT::TestMemberNoParamsConst_t

@anchor edsUGTest.TraitsFT.UT020170

@test Test Explorer: edsUGTest->TraitsFT->UT020175

@ref edsUGTest.Traits.UT020175

@sa TraitsFT::TestMemberNoParamsConst_t
@sa eds::FunctionTypeChecker

@anchor UT020175
@sa unit_test_traits_page
@sa Test
 */
class TraitsFT_UT020175_Test : public TraitsFT {
     EDS_DCL_GTEST_INTERNALS(TraitsFT, UT020175);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(TraitsFT, UT020175);
void TraitsFT_UT020175_Test::TestBody() {
     EDS_PROBEW(
         000010,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_function_v));
     EDS_PROBEW(
         000020,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_noexcept_v));
     EDS_PROBEW(
         000030,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_return_code_void_v));
     EDS_PROBEW(
         000040,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_eligible_delegate_v));
     EDS_PROBEW(
         000050,
         EXPECT_TRUE(
             eds::FunctionTypeChecker<
                 TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_member_function_v));
     EDS_PROBEW(
         000060,
         EXPECT_TRUE(eds::FunctionTypeChecker<
                     TestMemberNoParamsConst_t<TestRegularFunctions<>>>::is_constant_v));
}
#endif // UNIT_TEST_020175
//---------------------------------------------------------------------------------------------------
