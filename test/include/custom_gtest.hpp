#ifndef CUSTOM_GTEST_HPP
#define CUSTOM_GTEST_HPP
#include "private/eds_util.hpp"
#ifndef EDS_TEST_REGIME
#define EDS_TEST_REGIME 1
#endif
/// Informational message in a test goes to std::cerr because most test runners ignore
/// std::cout unless the test fails and trace is on
#define EDS_INFO_OUT std::cerr
/// Error message in a test goes to std::cout because most test runners capture std::cout only
/// when there is a failure.
#define EDS_TRACE_OUT std::cout
#define EDS_INFO(MI) EDS_INFO_OUT << "[    " << EDS_TOSTRING(MI) << " ] "
#define EDS_TRACE(MI) EDS_TRACE_OUT << "[    " << EDS_TOSTRING(MI) << " ] "
/// A macro to define a probe in a test case, the probe is a message that is printed to the
/// console and the test runner
///
/// The goal of the probe showing up during normal tests is to be able to diagnose the test
/// case without having to run the test in debug mode, of in a debugger. 85% of cases can be
/// diagnosed this way.
/// @param PASSERTION The embedded assertion executed by the probe. Can be any valid GTEST
/// assertion.
/// @param ... std::iostream style arguments to be printed to the console and the test runner.
/// @returns A message containing the line number and the arguments to the probe.
#define EDS_PROBE(PASSERTION, ...)                                                            \
     EDS_INFO(PROBE) << '(' << __LINE__ << ')' << #PASSERTION << ' ' __VA_ARGS__              \
                     << EDS_EOL();                                                            \
     PASSERTION
#define EDS_PROBEW(ID, PASSERTION, ...)                                                       \
     EDS_INFO(PROBE) << ID << '(' << __LINE__ << ')' << #PASSERTION << ' ' __VA_ARGS__        \
                     << EDS_EOL();                                                            \
     PASSERTION
/// An enhanced version of GTEST's TEST_F macro that allows to define a test case with a
/// meaningful name
///
/// @param UNIT The name of the unit under test for example xxxx.cpp the UNIT would be xxxx
/// @param UTID The unique identifier of the test case
/// @param FIXTURE The name of the fixture class for TEST_F
/// @param DESCRIPTION The description of the test case without spaces or underscores
#define EDS_GTESTF(UNIT, FIXTURE, DESCRIPTION) TEST_F(FIXTURE, EDS_CONCAT(UNIT, DESCRIPTION))
#define EDS_GTESTW(UNIT, FIXTURE, ID, DESCRIPTION)                                            \
     TEST_F(FIXTURE, EDS_CONCAT(UNIT, EDS_CONCAT(ID, DESCRIPTION)))
#define EDS_DCL_GTEST_INTERNALS(test_suite_name, test_name)                                   \
   public:                                                                                    \
     GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() = default;                          \
     ~GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() override = default;                \
     GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                       \
     (const GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &) = delete;                   \
     GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &operator=(                           \
         const GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &) = delete;                \
     GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                       \
     (GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &&) noexcept = delete;               \
     GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &operator=(                           \
         GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &&) noexcept = delete;            \
                                                                                              \
   private:                                                                                   \
     static ::testing::TestInfo *const test_info_
#define EDS_IMPL_GTEST_INTERNALS(test_suite_name, test_name)                                  \
     ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,                       \
                                                       test_name)::test_info_ =               \
         ::testing::internal::MakeAndRegisterTestInfo(                                        \
             EDS_STRINGIFY(test_suite_name), EDS_STRINGIFY(test_name), 0, 0,                  \
             ::testing::internal::CodeLocation(__FILE__, __LINE__ + 1),                       \
             (::testing::internal::GetTypeId<test_suite_name>()),                             \
             test_suite_name::SetUpTestCase, test_suite_name::TearDownTestCase,               \
             new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(test_suite_name, \
                                                                             test_name)>)
#endif
