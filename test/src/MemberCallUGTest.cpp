#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/event/member_call.hpp"
#include <memory>
#define UT01 1
#define UT02 2
#define UT03 3
#define UT04 4
class MemberCallSpecialization : public ::testing::Test {
    protected:
        MemberCallSpecialization() { }
        virtual ~MemberCallSpecialization() { }
        virtual void
        SetUp() { }
        virtual void
        TearDown() { }
        class TestClass {
                int m_total = 0;
                mutable int m_count = 0;
            public:
                static constexpr int testConstNoParamExpectedValue = 1000;
                static constexpr int testNoParamExpectedValue = 100;
                void
                testMethod(int a, int b) noexcept {
                        m_total = a + b;
                }
                void
                testNoParamMethod() noexcept {
                        m_total = testNoParamExpectedValue;
                }
                void
                testConstMethod(int a, int b) const noexcept {
                        m_count = a + b;
                }
                void
                testConstNoParamMethod() const noexcept {
                        m_count = testConstNoParamExpectedValue;
                }
                int
                getCount() const noexcept {
                        return m_count;
                }
                int
                getTotal() const noexcept {
                        return m_total;
                }
        };
};
#ifdef UT01
EDS_GTESTF(MemberCallUGTest, UT01, MemberCallSpecialization, VoidClassParamsNoExcept) {
        TestClass test;
        auto member_call = EDS create_method_call(&test, &TestClass::testMethod);
        using member_call_type_t = decltype(member_call);
        EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Exception Regime: " << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name() << EDS_EOL();
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
        EDS_PROBE(EXPECT_FALSE(member_call_type_t::constant_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::has_params_v));
        member_call.invoke(1, 2);
        EDS_PROBE(EXPECT_EQ(3, test.getTotal()));
}
#endif
#ifdef UT02
EDS_GTESTF(MemberCallUGTest, UT02, MemberCallSpecialization, VoidClassNoParamsNoExcept) {
        TestClass test;
        auto member_call = EDS create_method_call(&test, &TestClass::testNoParamMethod);
        using member_call_type_t = decltype(member_call);
        EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Exception Regime: " << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name() << EDS_EOL();
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
        EDS_PROBE(EXPECT_FALSE(member_call_type_t::constant_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
        EDS_PROBE(EXPECT_FALSE(member_call_type_t::has_params_v));
        member_call.invoke();
        EDS_PROBE(EXPECT_EQ(TestClass::testNoParamExpectedValue, test.getTotal()));
}
#endif
#ifdef UT03
EDS_GTESTF(MemberCallUGTest, UT03, MemberCallSpecialization, VoidClassParamsConstNoExcept) {
        TestClass test;
        auto member_call = EDS create_method_call(&test, &TestClass::testConstMethod);
        using member_call_type_t = decltype(member_call);
        EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Exception Regime: " << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name() << EDS_EOL();
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::constant_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::has_params_v));
        member_call.invoke(1, 2);
        EDS_PROBE(EXPECT_EQ(3, test.getCount()));
}
#endif
#ifdef UT04
/// @test edsUGTest.MemberCallUGTest.MemberCallUGTest4VoidClassConstNoParamsNoExcept
EDS_GTESTF(MemberCallUGTest, UT04, MemberCallSpecialization, VoidClassConstNoParamsNoExcept) {
        TestClass test;
        auto member_call = EDS create_method_call(&test, &TestClass::testConstNoParamMethod);
        using member_call_type_t = decltype(member_call);
        EDS_INFO(TYPES) << "Method Type: " << typeid(member_call_type_t::Member_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Return Type: " << typeid(member_call_type_t::ReturnCode_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Exception Regime: " << typeid(member_call_type_t::ExceptionRegime_t).name() << EDS_EOL();
        EDS_INFO(TYPES) << "Class Type: " << typeid(member_call_type_t::Class_t).name() << EDS_EOL();
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::is_legit_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::constant_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::noexcept_v));
        EDS_PROBE(EXPECT_TRUE(member_call_type_t::void_rc_v));
        EDS_PROBE(EXPECT_FALSE(member_call_type_t::has_params_v));
        member_call.invoke();
        EDS_PROBE(EXPECT_EQ(TestClass::testConstNoParamExpectedValue, test.getCount()));
}
#endif
