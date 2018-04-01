cmake_minimum_required(VERSION 2.8)
project(algo C CXX)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(global)
add_subdirectory(iterator)
add_subdirectory(array)
add_subdirectory(vector)
add_subdirectory(list)
add_subdirectory(linked_list)
add_subdirectory(queue)

