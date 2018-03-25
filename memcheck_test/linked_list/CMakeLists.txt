
# Test LinkedList<T>
add_executable(insert_destruct insert_destruct_test.cpp)
target_link_libraries(insert_destruct algoLinkedlist gmock_main)
add_test(insert_destruct insert_destruct)

add_executable(insert_remove insert_delete_rounds.cpp)
target_link_libraries(insert_remove algoLinkedlist gmock_main)
add_test(insert_remove insert_remove)



