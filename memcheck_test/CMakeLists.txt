cmake_minimum_required(VERSION 2.8)
project(algo_memcheck C CXX)

set(ALGO_DIR "../src" 
      CACHE_PATH "The path to the Algo Data Struct Library.")

set(BUILD_TESTING ON)
enable_testing()

# add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/gtest/include ${GTEST_DIR}/include)
include_directories(SYSTEM ${ALGO_DIR})

# add_subdirectory(iterator)
# add_subdirectory(array)
# add_subdirectory(vector)
# add_subdirectory(list)
add_subdirectory(linked_list)
