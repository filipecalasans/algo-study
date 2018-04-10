#ifndef __MAP_HH__   
#define __MAP_HH__ 

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "global/assert.h"
/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

/*
 * Map implementation using Red-blak Tree (RBT), which confers
 * in-order insertion by key.
 */
template <class K, class T>
class Map {
  
  Map() { }
  Map(const Map& other) { }
  
  // Constant member functions
  bool isEmpty() const;
  size_t size() const;
  size_t height() const;
  T getValue(const K& k) const;
  

};

}

#endif
