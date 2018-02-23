set(GMOCK_DIR "../../lib/googletest-release-1.8.0/googlemock/"
    CACHE PATH "The path to the GoogleMock test framework.")

set(GTEST_DIR "../../lib/googletest-release-1.8.0/googletest/"
    CACHE PATH "The path to the GoogleTest test framework.")

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/gtest/include ${GTEST_DIR}/include)

# Test Vector
add_executable(test_iterator testiterator.cpp)
target_link_libraries(test_iterator algoIterator gmock_main)
add_test(test_iterator test_iterator)

