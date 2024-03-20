#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/event/delegate.hpp"
#include <memory>
#include <private/eds_env.hpp>
class DelegateSpecializationFT : public ::testing::Test {
   protected:
     static int sm_total;
     DelegateSpecializationFT() {}
     ~DelegateSpecializationFT() override {}
     void SetUp() override {}
     void TearDown() override {}
     class TestClass {
          int m_total = 0;
          mutable int m_count = 0;

        public:
          static constexpr int testConstNoParamExpectedValue = 1000;
          static constexpr int testNoParamExpectedValue = 100;
          void testMethod(int a, int b) noexcept { m_total = a + b; }
          void testNoParamMethod() noexcept { m_total = testNoParamExpectedValue; }
          void testConstMethod(int a, int b) const noexcept { m_count = a + b; }
          void testConstNoParamMethod() const noexcept { m_count = testConstNoParamExpectedValue; }
          int getCount() const noexcept { return m_count; }
          int getTotal() const noexcept { return m_total; }
     };
     static void incrementTestFunction() noexcept { sm_total++; }
     static void adderTestFunction(int a, int b) noexcept { sm_total = a + b; }
     static int get_stotal() { return sm_total; }
};
int DelegateSpecializationFT::sm_total = 0;
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, VoidClassParamsNoExcept) {

     EDS Delegate<void(int, int) noexcept> delegate(adderTestFunction);
     delegate.invoke(1, 2);
     EDS_PROBE(EXPECT_EQ(3, sm_total));
}
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, VoidClassParamsNoExcept) {
     auto delegate = EDS Delegate<void(int, int) noexcept>::make_delegate(adderTestFunction);
     delegate.invoke(1, 2);
     EDS_PROBE(EXPECT_EQ(3, sm_total));
}
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, LambdaVoidParamsNoexcept) {
     int total = 0;
     EDS Delegate<void(int *, int) noexcept> delegate(
         [](int *a, int b) noexcept -> void { *a += b; });
     delegate(&total, 2);
     EDS_PROBE(EXPECT_EQ(2, total));
}
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, LambdaVoidParamsNoexcept) {
     int total = 0;
     auto delegate = EDS Delegate<void(int *, int) noexcept>::make_delegate(
         [](int *a, int b) noexcept -> void { *a += b; });
     delegate(&total, 2);
     EDS_PROBE(EXPECT_EQ(2, total));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, CaptureLambdaVoidParamsNoexcept) {
     int another_total = 2;
     int total = 0;
     EDS Delegate<void(int *, int) noexcept> delegate([&](int *a, int b) noexcept -> void {
          *a += b;
          *a += another_total;
     });
     delegate(&total, 2);
     EDS_PROBE(EXPECT_EQ(another_total + 2, total));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(DelegateUGTest, DelegateSpecializationFT, CaptureLambdaVoidParamsNoexcept) {
     int another_total = 2;
     int total = 0;
     auto delegate = EDS Delegate<void(int *, int) noexcept>::make_delegate(
         [&](int *a, int b) noexcept -> void {
              *a += b;
              *a += another_total;
         });
     delegate(&total, 2);
     EDS_PROBE(EXPECT_EQ(another_total + 2, total));
}
