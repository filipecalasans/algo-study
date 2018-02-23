# algo-study

This repository contains the implementation of common data-structures in C++. It was implemented with the propose of personal study on C++11/14 and data structures topics. Therefore, the library was implemented from the scratch using only standard libraries provided by the language. 

The containers implemented in this library use implicit-sharing similar to Python, therefore internal data structures are passed as reference on attributions. As result, the attribution between two containers do not involve copying the data from one container to the other, but only sharing the reference for the internal data structure. The library rely on std smart pointers: shared\_pointer and unique\_pointer to implement the containers. 

There is some sort of inspiration on the containers implemented in Qt Framework, in the sense that we try to optimize some of the memory allocation operations as they do in Qt. However, unlike it we don't use copy-on-write paradigm.

# Containers

  * DataArray
  * Array
  * Vector

