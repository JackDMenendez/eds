#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include <private/eds_env.hpp>
#include "private/event/member_call.hpp"
#include "private/eds_traits.hpp"
#include "private/eds_concepts.hpp"
#include <memory>
#define UNIT_TEST_020100 UT020100
//#define UNIT_TEST_020101 UT020101
#define UNIT_TEST_020105 UT020105
#define UNIT_TEST_020110 UT020110
#define UNIT_TEST_020115 UT020115
#define UNIT_TEST_020120 UT020120
#define UNIT_TEST_020125 UT020125
#define UNIT_TEST_020130 UT020130
#define UNIT_TEST_020135 UT020135
#define UNIT_TEST_020140 UT020140
#define UNIT_TEST_020200 UT020200
#define UNIT_TEST_020205 UT020205
#define UNIT_TEST_020210 UT020210
#define UNIT_TEST_020215 UT020215
#define UNIT_TEST_020220 UT020220
#define UNIT_TEST_020225 UT020225
#define UNIT_TEST_020230 UT020230
#define UNIT_TEST_020235 UT020235
#define UNIT_TEST_020240 UT020240
class MemberCallFT : public ::testing::Test {
   protected:
     MemberCallFT() = default;
     virtual ~MemberCallFT() = default;
     virtual void SetUp() {}
     virtual void TearDown() {}
     class TestClass {
          int m_total = 0;
          mutable int m_count = 0;

        public:
          TestClass() = default;
          virtual ~TestClass() = default;
          TestClass(const TestClass&) = delete;
          TestClass(TestClass&&) = delete;
          const TestClass& operator=(const TestClass&) = delete;
          TestClass& operator=(TestClass&&) = delete;
          static constexpr int testConstNoParamExpectedValue = 1000;
          static constexpr int testNoParamExpectedValue = 100;
          void testMethod(int a, int b) noexcept { m_total = a + b; }
          void testNoParamMethod() noexcept { m_total = testNoParamExpectedValue; }
          void testConstMethod(int a, int b) const noexcept { m_count = a + b; }
          void testConstNoParamMethod() const noexcept {
               m_count = testConstNoParamExpectedValue;
          }
          int getCount() const noexcept { return m_count; }
          int getTotal() const noexcept { return m_total; }
     };
};
#ifdef UNIT_TEST_020100
class MemberCallFT_UT020100_Test : public MemberCallFT {
     EDS_DCL_GTEST_INTERNALS(MemberCallFT, UT020100);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(MemberCallFT, UT020100);
void MemberCallFT_UT020100_Test::TestBody() {
     #ifndef EDS_NDUMBPTRS
     TestClass test;
     auto member_call = eds::create_method_call(&test, &TestClass::testMethod);
     using member_call_type_t = decltype(member_call);
     EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Exception Regime: "
                     << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name()
                     << EDS_EOL();
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
     EDS_PROBE(EXPECT_FALSE(member_call_type_t::constant_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::has_params_v));
     member_call.invoke(1, 2);
     EDS_PROBE(EXPECT_EQ(3, test.getTotal()));
     #endif // EDS_NDUMBPTRS
}
#endif // UNIT_TEST_020100
#ifdef UNIT_TEST_020101
class MemberCallFT_UT020101_Test : public MemberCallSpecializationFT {
     EDS_DCL_GTEST_INTERNALS(MemberCallFT, UT020101);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(MemberCallFT, UT020101);
void MemberCallSpecializationFT_UT020101_Test::TestBody() {
     #ifndef EDS_NDUMBPTRS
     TestClass test;
     auto member_call = eds::create_method_call(&test, &TestClass::testMethod);
     using member_call_type_t = decltype(member_call);
     EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Exception Regime: "
                     << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name()
                     << EDS_EOL();
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
     EDS_PROBE(EXPECT_FALSE(member_call_type_t::constant_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::has_params_v));
     member_call.invoke(1, 2);
     EDS_PROBE(EXPECT_EQ(3, test.getTotal()));
     #endif // EDS_NDUMBPTRS
}
#endif // UNIT_TEST_020101
#ifdef UNIT_TEST_020105
class MemberCallFT_UT020105_Test : public MemberCallFT {
     EDS_DCL_GTEST_INTERNALS(MemberCallFT, UT020105);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(MemberCallFT, UT020105);
void MemberCallFT_UT020105_Test::TestBody() {
     TestClass test;
     auto member_call = EDS create_method_call(&test, &TestClass::testNoParamMethod);
     using member_call_type_t = decltype(member_call);
     EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Exception Regime: "
                     << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name()
                     << EDS_EOL();
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
     EDS_PROBE(EXPECT_FALSE(member_call_type_t::constant_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
     EDS_PROBE(EXPECT_FALSE(member_call_type_t::has_params_v));
     member_call.invoke();
     EDS_PROBE(EXPECT_EQ(TestClass::testNoParamExpectedValue, test.getTotal()));
}
#endif // UNIT_TEST_020105
#ifdef UNIT_TEST_020110
class MemberCallFT_UT020110_Test : public MemberCallFT {
     EDS_DCL_GTEST_INTERNALS(MemberCallFT, UT020110);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(MemberCallFT, UT020110);
void MemberCallFT_UT020110_Test::TestBody() {
     TestClass test;
     auto member_call = EDS create_method_call(&test, &TestClass::testConstMethod);
     using member_call_type_t = decltype(member_call);
     EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Exception Regime: "
                     << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name()
                     << EDS_EOL();
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::constant_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::has_params_v));
     member_call.invoke(1, 2);
     EDS_PROBE(EXPECT_EQ(3, test.getCount()));
}
#endif // UNIT_TEST_020110
/// @test edsUGTest.MemberCallUGTest.MemberCallUGTest4VoidClassConstNoParamsNoExcept
#ifdef UNIT_TEST_020115
class MemberCallFT_UT020115_Test : public MemberCallFT {
     EDS_DCL_GTEST_INTERNALS(MemberCallFT, UT020115);
     void TestBody() override;
};
EDS_IMPL_GTEST_INTERNALS(MemberCallFT, UT020115);
void MemberCallFT_UT020115_Test::TestBody() {
     TestClass test;
     auto member_call = EDS create_method_call(&test, &TestClass::testConstNoParamMethod);
     using member_call_type_t = decltype(member_call);
     EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Exception Regime: "
                     << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name()
                     << EDS_EOL();
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::constant_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
     EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
     EDS_PROBE(EXPECT_FALSE(member_call_type_t::has_params_v));
     member_call.invoke();
     EDS_PROBE(EXPECT_EQ(TestClass::testConstNoParamExpectedValue, test.getCount()));
}
#endif // UNIT_TEST_020115
