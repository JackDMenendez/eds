#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_info.hxx"
class BuildNumberFT : public ::testing::Test {};
EDS_GTESTF(ToolsUGTest, BuildNumberFT, Present) {
     EDS_PROBE(EXPECT_GT(EDS_VERSION_BUILD, 0) << "Build is larger than 0");
}
