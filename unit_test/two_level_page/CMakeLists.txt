set(GMOCK_DIR "../../lib/googletest-release-1.8.0/googlemock/"
    CACHE PATH "The path to the GoogleMock test framework.")

set(GTEST_DIR "../../lib/googletest-release-1.8.0/googletest/"
    CACHE PATH "The path to the GoogleTest test framework.")

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/gtest/include ${GTEST_DIR}/include)

# Test Vector
add_executable(test_two_level_page testtwolevelpage.cpp)
target_link_libraries(test_two_level_page algoTwoLevelPage algoArray gmock_main)
add_test(test_two_level_page test_two_level_page)

