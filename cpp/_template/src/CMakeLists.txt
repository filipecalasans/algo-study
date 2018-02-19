cmake_minimum_required(VERSION 2.8)

file(GLOB algo_SRC
    "*.h"
    "*.cpp"
)

cmake_minimum_required(VERSION 3.8)
project(algo C CXX)

file(GLOB algo_SRC "*.h" "*.cpp")

add_library(algoCore ${algo_SRC})