#ifndef ALGOS_MAP_HH
#define ALGOS_MAP_HH

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "global/assert.h"
#include "list/list.h"
#include "rbtree.h"

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
  
  std::shared_ptr<RBTree<K,T>> d;

public:

  Map() { d = std::make_shared<RBTree<K,T>>(); }
  Map(const Map& other) { d = other.d; }
  
  // Constant member functions
  inline size_t size() const { return d->size(); }
  inline bool isEmpty() const { return (size() == 0); }
  T getValue(const K& key) const;
  bool contains(const K& key) const;  
  
  T& operator[](const K& key);
  const T& operator[](const K& key) const;
  
  void insert(const T& t, const K& k);
  void insert(T&& t, K&& k);
  
  List<T> values() const;
  List<K> keys() const;
  
};

template <class K, class T>
List<T> Map<K,T>::values() const
{
  List<T> v;
  return v; 
}

template <class K, class T>
List<K> Map<K,T>::keys() const
{
  return List<K>();
}

}

#endif
