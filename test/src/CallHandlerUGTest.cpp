#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_env.hpp"
#include "private/eds_util.hpp"
#include "private/event/call_handler.hpp"
#include "private/event/member_call.hpp"
class TestAdderResource : public EDS DelegateResourceManager<int, int> {
   public:
     using Equivalent_t = void(int, int) noexcept;
     TestAdderResource() noexcept = default;
     ~TestAdderResource() noexcept override = default;
     void invoke(int a, int b) noexcept override {}
     bool equals(const EDS Resource &other) const noexcept override { return false; }
     void operator()(int a, int b) noexcept override {}
     size_t get_subscriber_id() const noexcept override { return 0; }
     long get_use_count() const noexcept override { return 0; }
};
class TestPointerResource : public EDS DelegateResourceManager<int *, int> {
   public:
     using Equivalent_t = void(int *, int) noexcept;
     TestPointerResource() noexcept = default;
     ~TestPointerResource() noexcept override = default;
     void invoke(int *a, int b) noexcept override {}
     bool equals(const EDS Resource &other) const noexcept override { return false; }
     void operator()(int *a, int b) noexcept override {}
     size_t get_subscriber_id() const noexcept override { return 0; }
     long get_use_count() const noexcept override { return 0; }
};
class TestIncrementResource : public EDS DelegateResourceManager<> {
   public:
     using Equivalent_t = void() noexcept;
     TestIncrementResource() noexcept {}
     ~TestIncrementResource() noexcept override {}
     void invoke() noexcept override {}
     bool equals(const EDS Resource &other) const noexcept override { return false; }
     void operator()() noexcept override {}
     size_t get_subscriber_id() const noexcept override { return 0; }
     long get_use_count() const noexcept override { return 0; }
};
class TestSubscriberClass {
   private:
     int m_total = 0;
     mutable int m_mutable_total = 0;

   public:
     TestSubscriberClass() noexcept {}
     ~TestSubscriberClass() noexcept {}

     void incrementTestFunctionConst() const noexcept { m_mutable_total++; }
     void adderTestFunctionConst(int a, int b) const noexcept { m_mutable_total = a + b; }
     void incrementTestFunction() noexcept { m_total++; }
     void adderTestFunction(int a, int b) noexcept { m_total = a + b; }
     int get_total() { return m_total; }
     int get_mutable_total() const { return m_mutable_total; }
};
class IncrementMockResource : public EDS DelegateResourceManager<> {
   public:
     using Equivalent_t = void() noexcept;
     IncrementMockResource() noexcept {}
     ~IncrementMockResource() noexcept override {}
     void invoke() noexcept override {}
     bool equals(const EDS Resource &other) const noexcept override { return false; }
     void operator()() noexcept override {}
     size_t get_subscriber_id() const noexcept override { return 0; }
     long get_use_count() const noexcept override { return 0; }
};
class CallHandlerTF : public ::testing::Test {
   protected:
     static int sm_total;

     using AdderTestWrapper_t = EDS CallHandler<EDS FunctionPointer, int, int>;
     using AdderMemberTestWrapper_t = EDS CallHandler<EDS PsuedoMemberPointer, int, int>;
     using IncrementMemberTestWrapper_t = EDS CallHandler<EDS PsuedoMemberPointer>;
     using IncrementTestWrapper_t = EDS CallHandler<EDS FunctionPointer>;
     CallHandlerTF() {}
     virtual void SetUp() { sm_total = 0; }
     virtual void TearDown() {}
     ~CallHandlerTF() {}
     static void incrementTestFunction() noexcept { sm_total++; }
     static void adderTestFunction(int a, int b) noexcept { sm_total = a + b; }
     static int get_stotal() { return sm_total; }
};
int CallHandlerTF::sm_total = 0;
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, VoidParamsNoexcept) {
     EDS_INFO(TYPES) << "CallHandler Type: " << typeid(AdderTestWrapper_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Call Back Function Type: " << typeid(AdderTestWrapper_t::CallBack_t).name()
                     << EDS_EOL();
     const bool expected_CallBack_type_comparison_result = true;
     bool actual_CallBack_type_comparison_result =
         std::is_same_v<TestAdderResource::Equivalent_t, AdderTestWrapper_t::CallBack_t>;
     EDS_PROBE(EXPECT_EQ(expected_CallBack_type_comparison_result,
                         actual_CallBack_type_comparison_result));
     TestAdderResource resource;
     // normally done by the delegate
     AdderTestWrapper_t ch(adderTestFunction, &resource);
     ch(1, 2);
     EDS_PROBE(EXPECT_EQ(3, get_stotal()));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidNoparamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate without parameters.
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, VoidNoparamsNoexcept) {
     EDS_INFO(TYPES) << "CallHandler Type: " << typeid(IncrementTestWrapper_t).name() << EDS_EOL();
     EDS_INFO(TYPES) << "Call Back Function Type: "
                     << typeid(IncrementTestWrapper_t::CallBack_t).name() << EDS_EOL();
     const bool expected_CallBack_type_comparison_result = true;
     bool actual_CallBack_type_comparison_result =
         std::is_same_v<IncrementMockResource::Equivalent_t, IncrementTestWrapper_t::CallBack_t>;
     EDS_PROBE(EXPECT_EQ(expected_CallBack_type_comparison_result,
                         actual_CallBack_type_comparison_result));
     IncrementMockResource resource;
     // normally done by the delegate
     IncrementTestWrapper_t ch(incrementTestFunction, &resource);
     ch();
     EDS_PROBE(EXPECT_EQ(1, get_stotal()));
}
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, MemberVoidParamsNoexcept) {
     EDS_INFO(TYPES) << "CallHandler Type: " << typeid(AdderMemberTestWrapper_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Call Back Function Type: "
                     << typeid(AdderMemberTestWrapper_t::CallBack_t).name() << EDS_EOL();
     const bool expected_CallBack_type_comparison_result = true;
     bool actual_CallBack_type_comparison_result =
         std::is_same_v<TestAdderResource::Equivalent_t, AdderMemberTestWrapper_t::CallBack_t>;
     EDS_PROBE(EXPECT_EQ(expected_CallBack_type_comparison_result,
                         actual_CallBack_type_comparison_result));
     TestAdderResource resource;
     TestSubscriberClass subscriber_class;
     AdderMemberTestWrapper_t ch(&subscriber_class, &TestSubscriberClass::adderTestFunction,
                                 &resource);
     EDS_INFO(TYPES) << "Member Call Type: " << typeid(ch).name() << EDS_EOL();
     ch(1, 2);
     EDS_PROBE(EXPECT_EQ(3, subscriber_class.get_total()));
}
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, MemberVoidParamsConstNoexcept) {
     EDS_INFO(TYPES) << "CallHandler Type: " << typeid(AdderMemberTestWrapper_t).name()
                     << EDS_EOL();
     EDS_INFO(TYPES) << "Call Back Function Type: "
                     << typeid(AdderMemberTestWrapper_t::CallBack_t).name() << EDS_EOL();
     const bool expected_CallBack_type_comparison_result = true;
     bool actual_CallBack_type_comparison_result =
         std::is_same_v<TestAdderResource::Equivalent_t, AdderMemberTestWrapper_t::CallBack_t>;
     EDS_PROBE(EXPECT_EQ(expected_CallBack_type_comparison_result,
                         actual_CallBack_type_comparison_result));
     TestAdderResource resource;
     TestSubscriberClass subscriber_class;
     AdderMemberTestWrapper_t ch(&subscriber_class, &TestSubscriberClass::adderTestFunctionConst,
                                 &resource);
     EDS_INFO(TYPES) << "Member Call Type: " << typeid(ch).name() << EDS_EOL();
     ch(1, 2);
     EDS_PROBE(EXPECT_EQ(3, subscriber_class.get_mutable_total()));
}
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, MemberVoidNoexcept) {
     TestIncrementResource resource;
     TestSubscriberClass subscriber_class;
     IncrementMemberTestWrapper_t ch(&subscriber_class, &TestSubscriberClass::incrementTestFunction,
                                     &resource);
     EDS_INFO(TYPES) << "Member Call Type: " << typeid(ch).name() << EDS_EOL();
     ch();
     EDS_PROBE(EXPECT_EQ(1, subscriber_class.get_total()));
}
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, MemberVoidConstNoexcept) {
     TestIncrementResource resource;
     TestSubscriberClass subscriber_class;
     IncrementMemberTestWrapper_t ch(&subscriber_class,
                                     &TestSubscriberClass::incrementTestFunctionConst, &resource);
     EDS_INFO(TYPES) << "Member Call Type: " << typeid(ch).name() << EDS_EOL();
     ch();
     EDS_PROBE(EXPECT_EQ(1, subscriber_class.get_mutable_total()));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, LambdaVoidParamsNoexcept) {
     using AdderTestWrapper_t = EDS CallHandler<EDS FunctionPointer, int *, int>;
     TestPointerResource resource;
     int total = 0;
     auto lambda = [](int *a, int b) noexcept -> void { *a += b; };
     AdderTestWrapper_t ch(lambda, &resource);
     ch(&total, 2);
     EDS_PROBE(EXPECT_EQ(2, total));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, CaptureLambdaVoidParamsNoexcept) {
     TestPointerResource resource;
     int another_total = 2;
     int total = 0;
     auto lambda = [&](int *a, int b) noexcept -> void {
          *a += b;
          *a += another_total;
     };
     using AdderTestWrapper_t = EDS CallHandler<EDS LambdaRef, decltype(lambda), int *, int>;
     AdderTestWrapper_t ch(lambda, &resource);
     ch(&total, 2);
     EDS_PROBE(EXPECT_EQ(another_total + 2, total));
}
/// @test edsUGTest.CallHandlerTF.CallHandlerUGTest1VoidParamsNoexcept
/// tests the creation of an eds::CallHandler for a static delegate with parameters.
EDS_GTESTF(CallHandlerUGTest, CallHandlerTF, CaptureLambdaVoidNoexcept) {
     TestIncrementResource resource;
     int another_total = 2;
     int total = 0;
     auto lambda = [&]() noexcept -> void { total += another_total; };
     using AdderTestWrapper_t = EDS CallHandler<EDS LambdaRef, decltype(lambda)>;
     AdderTestWrapper_t ch(lambda, &resource);
     ch();
     EDS_PROBE(EXPECT_EQ(another_total, total));
}
