###########################################################################################################
# No testing has been done with CMake versions less the 3.28.1
############################################################################################################
cmake_minimum_required (VERSION 3.28.0)
############################################################################################################
if (${CMAKE_CXX_COMPILER_ID} MSVC) # This check avoids a warning when the compiler is not MSVC
   # Enable Hot Reload for MSVC compilers if supported. This was added by 
   # Visual Studio 2022
   if (POLICY CMP0141)
      cmake_policy(SET CMP0141 NEW)
      set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
    endif()
endif()
############################################################################################################
# eds Project Version setup
# The current build number persists between builds in the build_number.txt file.
# The build number is incremented each time the project is built. The build number
# is used to set the project version tweak number. The project version major, minor,
# and patch numbers are set manually in this file.
file(READ build_number.txt BUILD_NUMBER) # build_number.txt is found in the project root
math(EXPR BUILD_NUMBER "${BUILD_NUMBER}+1")
file(WRITE build_number.txt "${BUILD_NUMBER}")
set(PROJECT_VERSION_TWEAK ${BUILD_NUMBER})
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
############################################################################################################
project( eds
   VERSION ${PROJECT_VERSION}
   DESCRIPTION "Event Delegate Subscription"
   HOMEPAGE_URL "https://github.com/JackDMenendez/eds"
   LANGUAGES CXX 
)
############################################################################################################
if(PROJECT_IS_TOP_LEVEL) 
   include(CTest) 
endif()
include(GoogleTest)
include(cmake/edcOptions.cmake)
find_package(Doxygen REQUIRED)
############################################################################################################
set(CMAKE_MESSAGE_LOG_LEVEL "VERBOSE")
enable_testing()
############################################################################################################
message( STATUS "eds version number: ${PROJECT_VERSION}")
message( STATUS "CMAKE_CXX_COMPILER_ID: " ${CMAKE_CXX_COMPILER_ID} )
message( STATUS "CMAKE_CXX_COMPILER_VERSION: " ${CMAKE_CXX_COMPILER_VERSION} )
############################################################################################################
# eds Project info header generation
set(info_file eds_info.hxx)
set(info_path "${eds_SOURCE_DIR}/include/private/${info_file}")
configure_file(eds_info.hxx.in "${eds_SOURCE_DIR}/include/private/eds_info.hxx")
set(eds_public_headers "${eds_SOURCE_DIR}/include/eds.hpp" "${eds_SOURCE_DIR}/include/eds_event.hpp")
set(eds_private_headers 
  "${info_path}" 
  "${eds_SOURCE_DIR}/include/private/eds_concepts.hpp" 
  "${eds_SOURCE_DIR}/include/private/eds_env.hpp" 
  "${eds_SOURCE_DIR}/include/private/eds_util.hpp" 
  "${eds_SOURCE_DIR}/include/private/eds_hash.hpp" 
  "${eds_SOURCE_DIR}/include/private/eds_traits.hpp" 
  "${eds_SOURCE_DIR}/include/private/event/member_call.hpp"
  "${eds_SOURCE_DIR}/include/private/event/resource.hpp"
  "${eds_SOURCE_DIR}/include/private/event/subscriber.hpp"
  "${eds_SOURCE_DIR}/include/private/event/delegate_resource_manager.hpp"
  "${eds_SOURCE_DIR}/include/private/event/call_handler.hpp"
  "${eds_SOURCE_DIR}/include/private/event/delegate.hpp"
  "${eds_SOURCE_DIR}/include/private/event/event.hpp"
)
set(eds_all_headers ${eds_public_headers} ${eds_private_headers})
############################################################################################################
# edsinfo executable
set(edsinfo_headers ${eds_all_headers})
set(edsinfo_sources src/edsinfo.cpp)
add_executable(edsinfo ${edsinfo_sources} ${edsinfo_headers})
set_property(TARGET edsinfo PROPERTY CXX_STANDARD 23)
target_sources(edsinfo PRIVATE ${edsinfo_sources} ${edsinfo_headers})
target_include_directories(edsinfo PRIVATE include)
############################################################################################################
# eds static library
set(eds_lib_sources src/eds/eds.cpp)
set(eds_lib_public_headers ${eds_public_headers})
set(eds_lib_private_headers ${eds_private_headers})
set(eds_lib_headers ${eds_all_headers})
add_library(eds STATIC ${eds_lib_sources} ${eds_lib_headers})
set_property(TARGET eds PROPERTY CXX_STANDARD 23)
target_sources(eds PUBLIC ${eds_sources} ${eds_lib_headers})
target_include_directories(eds PUBLIC include
                           eds PRIVATE include/private)
############################################################################################################
# down load and build Google test and Mach
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
)
############################################################################################################
# eds unit tests
set(eds_test_source 
  "${eds_SOURCE_DIR}/test/src/HashUGTest.cpp"
  "${eds_SOURCE_DIR}/test/src/ToolsUGTest.cpp"
  "${eds_SOURCE_DIR}/test/src/MemberCallUGTest.cpp"
  "${eds_SOURCE_DIR}/test/src/CallHandlerUGTest.cpp"
  "${eds_SOURCE_DIR}/test/src/DelegateUGTest.cpp"
 "test/src/ConceptsUGTest.cpp" "test/src/TraitsUGTest.cpp")
set(eds_test_headers "${eds_SOURCE_DIR}/test/include/custom_gtest.hpp" ${eds_all_headers})
add_executable(edsUGTest ${eds_test_source} ${eds_test_headers})
target_include_directories(
edsUGTest PUBLIC "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/googletest-src/googletest/include>"
edsUGTest PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
edsUGTest PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/include>")
target_compile_features(edsUGTest PUBLIC cxx_std_23)
target_link_libraries(edsUGTest gtest_main eds)
add_test(NAME unit_test COMMAND edsUGTest)
############################################################################################################
# eds documentation
# Override the default doxygen output directory, which is CMAKE_CURRENT_BINARY_DIR. 
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
# Enable HTML documentation generation
set(DOXYGEN_GENERATE_HTML YES)
# Enable MAN page generation
set(DOXYGEN_GENERATE_MAN NO)
# Enable markdown support
set(DOXYGEN_MARKDOWN_SUPPORT YES)
# Enable autolink support
set(DOXYGEN_AUTOLINK_SUPPORT YES)
# Enable dot graph support
set(DOXYGEN_HAVE_DOT YES)
# Include collaboration diagrams in class documentation
set(DOXYGEN_COLLABORATION_GRAPH NO)
# Include class diagrams in class documentation
set(DOXYGEN_CLASS_GRAPH YES)
# Generate UML-like graphs
set(DOXYGEN_UML_LOOK YES)
# Include type and parameter information in UML graphs
set(DOXYGEN_DOT_UML_DETAILS YES)
# Max per-line length for graph content
set(DOXYGEN_DOT_WRAP_THRESHOLD 100)
# Enables drawing call graphs for the functions
set(DOXYGEN_CALL_GRAPH YES)
# Suppress the output messages
set(DOXYGEN_QUIET NO)
doxygen_add_docs(
  eds_generate_docs
  "${PROJECT_SOURCE_DIR}/include"
  ALL
  COMMENT "Generating documentation eds"
)

############################################################################################################
# eds install
#Include INSTALL target to default Visual Studio build.
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
set(EDS_INSTALL_DIR eds_${PROJECT_VERSION})
set(EDS_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/${EDS_INSTALL_DIR})
include(GNUInstallDirs)
# reinstalling same build, clean up old install
if(EXISTS ${EDS_INSTALL_PATH})
   file(REMOVE_RECURSE ${EDS_INSTALL_PATH})
endif()
# Install the HTML documentation to system's default documentation folder 
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs/html/" DESTINATION "${EDS_INSTALL_PATH}/docs/html/" COMPONENT eds_html)

install(TARGETS edsinfo DESTINATION ${EDS_INSTALL_DIR}/bin)
install(TARGETS eds DESTINATION ${EDS_INSTALL_DIR}/lib)
install(FILES ${eds_public_headers} DESTINATION ${EDS_INSTALL_DIR}/lib/include)
install(FILES ${eds_private_headers} DESTINATION ${EDS_INSTALL_DIR}/lib/include/private)
############################################################################################################
include(CMakePackageConfigHelpers)
