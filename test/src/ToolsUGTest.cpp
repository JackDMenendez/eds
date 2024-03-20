#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_info.hxx"
class BuildNumber : public ::testing::Test {};
EDS_GTESTF(ToolsUGTest, BuildNumber, Present) {
     EDS_PROBE(EXPECT_GT(EDS_VERSION_BUILD, 0) << "Build is larger than 0");
}
