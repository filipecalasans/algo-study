
# Test LinkedList<T>
add_executable(insert_destruct insert_destruct_test.cpp)
target_link_libraries(insert_destruct algoLinkedlist gmock_main)
add_test(insert_destruct insert_destruct)


