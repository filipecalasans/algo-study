cmake_minimum_required(VERSION 2.8)
project(algo_repo C CXX)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-Werror)
add_definitions(-std=c++14)

enable_testing()

set(ALGO_DIR src 
      CACHE_PATH "The path to the Algo Data Struct Library.")

include_directories(SYSTEM ${ALGO_DIR})

add_subdirectory(src)
add_subdirectory(unit_test)
