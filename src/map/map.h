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
  
  std::shared_ptr<RBTree<K,T> > d;

public:

  Map() { d = std::make_shared<RBTree<K,T>>(); }
  Map(const Map& other) { d = other.d; }
  Map(Map&& other)
  {
    d = other.d;
    other.d.reset(nullptr);
  }
  
  // Constant member functions
  inline size_t size() const { return d->size(); }
  inline bool isEmpty() const { return (size() == 0); }
  T getValue(const K& key) const
  {
    auto node = d->find(key);
    if(!node)
    {
        return T();
    }
    return node->key_value.second;
  }

  bool contains(const K& key) const
  {
      return (d->find(key) != nullptr);
  }
  
  T& operator[](const K& key)
  {
    auto node = d->find(key);
    if(!node)
    {
        insert(key, T());
        return d->find(key)->key_value.second;
    }
    return node->key_value.second;
  }

  const T& operator[](const K& key) const
  {
      return operator[](key);
  }
  
  void insert(const K& k, const T& t)
  {
    d->insertData(k, t);
  }

  void insert(K&& k, T&& t)
  {
    d->insertData(k, t);
  }
  
  List<T> values() const;
  List<K> keys() const;


  class iterator {
    public:

        typedef typename RBTree<K,T>::Node TreeNode;
        typedef iterator self_type;
        typedef Pair<K,T> value_type;
        typedef Pair<K,T>& reference;
        typedef Pair<K,T>* pointer_to_obj;
        typedef TreeNode* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(pointer ptr) : _ptr(ptr) {}
        self_type operator++() { _ptr = _ptr->nextNode(); return *this; } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr = _ptr->nextNode(); return i; } //POSTFIX
        reference operator*() { return _ptr->key_value; }
        pointer_to_obj  operator->() const { return &(_ptr->key_value); }
        bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:

        pointer _ptr;
  };

  class const_iterator {
    public:

        typedef typename RBTree<K,T>::Node TreeNode;
        typedef const_iterator self_type;
        typedef Pair<K,T> value_type;
        typedef Pair<K,T> const& reference;
        typedef Pair<K,T>* pointer_to_obj;
        typedef TreeNode* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        const_iterator(pointer ptr) : _ptr(ptr) {}
        self_type operator++() { _ptr = _ptr->nextNode(); return *this; } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr = _ptr->nextNode(); return i; } //POSTFIX
        reference operator*() const { return _ptr->key_value; }
        const pointer_to_obj  operator->() const { return &(_ptr->key_value); }
        bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }

    private:

        pointer _ptr;
  };


  iterator begin() { return iterator(size() ? d->mostLeftNode : nullptr); }
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(size() ? d->mostLeftNode : nullptr); }
  const_iterator cend() const { return const_iterator(nullptr); }
  
};


template <class K, class T>
List<T> Map<K,T>::values() const
{
  List<T> v;
  v.reserve(size());

  auto it = cbegin();
  while(it != cend())
  {
    v.append((*it).second);
    ++it;
  }
  return v;
}

template <class K, class T>
List<K> Map<K,T>::keys() const
{
  List<K> k;
  k.reserve(size());
  auto it = cbegin();
  while(it != cend())
  {
      k.append((*it).first);
      ++it;
  }
  return k;
}

}

#endif
