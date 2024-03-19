#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/event/delegate.hpp"
#include <memory>
#include <private/eds_env.hpp>
#define UT01 1
#define UT02 2
#define UT03 3
#define UT04 4
class DelegateSpecializationFT : public ::testing::Test {
    protected:
        static int sm_total;
        DelegateSpecializationFT() { }
        ~DelegateSpecializationFT() override { }
        void
        SetUp() override { }
        void
        TearDown() override { }
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
        static void
        incrementTestFunction() noexcept {
                sm_total++;
        }
        static void
        adderTestFunction(int a, int b) noexcept {
                sm_total = a + b;
        }
        static int
        get_stotal() {
                return sm_total;
        }
};
int DelegateSpecializationFT::sm_total = 0;
#ifdef UT01
EDS_GTESTF(DelegateUGTest, UT01, DelegateSpecializationFT, VoidClassParamsNoExcept) {

        EDS Delegate<void(int, int) noexcept> delegate(adderTestFunction);
        delegate.invoke(1, 2);
        EDS_PROBE(EXPECT_EQ(3, sm_total));
}
#endif
