set(GMOCK_DIR "../../../lib/googletest-release-1.8.0/googlemock/"
    CACHE PATH "The path to the GoogleMock test framework.")

set(GTEST_DIR "../../../lib/googletest-release-1.8.0/googletest/"
    CACHE PATH "The path to the GoogleTest test framework.")

enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # force this option to ON so that Google Test will use /MD instead of /MT
  # /MD is now the default for Visual Studio, so it should be our default, too
  option(gtest_force_shared_crt
  "Use shared (DLL) run-time lib even when Google Test is built as static lib."
  ON)
elseif (APPLE)
  add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/gtest/include ${GTEST_DIR}/include)

add_executable(test_project test.cpp)
target_link_libraries(test_project algoCore gmock_main)

add_test(TestProject test_project)
