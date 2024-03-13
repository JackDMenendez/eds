#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_info.hxx"
#define UT01 1
#define UT02 2
#define UT03 3
class BuildNumber : public ::testing::Test {};
#ifdef UT01
EDS_GTESTF(ToolsUGTest, UT01, BuildNumber, Present) {
      EDS_PROBE(EXPECT_GT(EDS_VERSION_BUILD,0) << "Build is larger than 0");
}
#endif
