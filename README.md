# algo-study

This repository contains implementation of common data-structures in C++. I have been developing this repository with the main goal of studying C++11/14, data structures, debugging, testing and deploymentin C++.

The containers implemented in this library use implicit-sharing. Hence, two containers after an assignment operator has a reference to the same inner data struct. This operation is inexpensive O(1), since it involves only assigning a pointer to the internal container. Deep-copy is possible, however it needs to be implemented. Moreover, comparing two containers involves comparing the internal pointers - complexity O(1). Additionally, if you want to avoid implicit sharing behavior you can use move semantics.

This library relies on STL smart pointers: shared\_pointer and unique\_pointer to implement the containers.

# Containers

  * DataArray
  * Array
  * Vector
  * List
  * Linked List
  * Queue
  * Stack
  * Heap (min-heap or priority queue)
  * Map (red-black tree) 
  * Hash Table (To be implemented)
