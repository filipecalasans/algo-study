cmake_minimum_required(VERSION 3.8)
project(array_proj C CXX)

enable_testing()

add_definitions(-std=c++11)
add_definitions(-Werror)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" -D_GLIBCXX_DEBUG)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(unit_test)

