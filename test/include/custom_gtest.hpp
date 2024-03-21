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
/// An enhanced version of GTEST's TEST_F macro that allows to define a test case with a
/// meaningful name
///
/// @param UNIT The name of the unit under test for example xxxx.cpp the UNIT would be xxxx
/// @param UTID The unique identifier of the test case
/// @param FIXTURE The name of the fixture class for TEST_F
/// @param DESCRIPTION The description of the test case without spaces or underscores
#define EDS_GTESTF(UNIT, FIXTURE, DESCRIPTION)                                                \
     TEST_F(FIXTURE, EDS_CONCAT(UNIT, EDS_CONCAT(__LINE__, DESCRIPTION)))
#endif
