cmake_minimum_required(VERSION 2.8)
project(algo_test C CXX)

set(GMOCK_DIR "lib/googletest-release-1.8.0/googlemock/"
    CACHE PATH "The path to the GoogleMock test framework.")

set(GTEST_DIR "lib/googletest-release-1.8.0/googletest/"
    CACHE PATH "The path to the GoogleTest test framework.")

enable_testing()

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/gtest/include ${GTEST_DIR}/include)

add_subdirectory(src)
add_subdirectory(unit_test)
