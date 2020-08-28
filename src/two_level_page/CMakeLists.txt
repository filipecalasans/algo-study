cmake_minimum_required(VERSION 2.8)
project(two_level_page C CXX)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++14)
add_definitions(-Werror)


file(GLOB algo_SRC "*.h" "*.cpp")

add_library(algoTwoLevelPage ${algo_SRC})
target_link_libraries(algoTwoLevelPage algoVector algoGlobal)
