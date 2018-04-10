cmake_minimum_required(VERSION 3.8)
project(map_proj C CXX)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++14)
add_definitions(-Werror)

include_directories("../")

file(GLOB algo_SRC "*.h" "*.cpp")

add_library(algoMap ${algo_SRC})
target_link_libraries(algoMap algoGlobal)

