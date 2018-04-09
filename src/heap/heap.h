#ifndef __HEAP_HH__   
#define __HEAP_HH__ 

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "global/assert.h"
#include "pair/pair.h"
#include "list/list.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

template <class K, class T>
class Heap : protected List<Pair<K,T>> {
  
  private:

    int heap_order = 2;

  public: 
    
    Heap() { }

    Heap(const Heap<K,T>& other) : List<T>(other) {
      heap_order = other.heap_order;
    }

    void swap(Heap<K,T>& other) {
      std::swap(this->d, other.d);
      std::swap<int>(heap_order, other.heap_order);
    }

    
    Heap<K,T> &operator=(const Heap<K,T>& other) { 
      List<Pair<K,T>>::operator=(other); 
      return (*this); 
    }

    Heap<K,T> &operator=(Heap<K,T>&& other) { 
      List<Pair<K,T>>::operator=(other); 
      heap_order = other.heap_order;
      return (*this); 
    }

    bool operator==(const Heap<K,T>& other) const { return (this->d==other.d) && 
      (heap_order==other.heap_order); }
    inline bool operator!=(const Heap<K,T> &other) const { return (this->d != other.d) || 
      (heap_order!=other.heap_order); }
    inline size_t size() const { return List<Pair<K,T>>::size(); }
    inline bool isEmpty() const { return List<Pair<K,T>>::isEmpty(); }
    inline void reserve(int size) { List<Pair<K,T>>::reserve(size); }


    T& operator[](int i) {  
      return List<Pair<K,T>>::operator[](i).second;
    }

    const T& operator[](int i) const { 
      return List<Pair<K,T>>::operator[](i).second;
    }
    
    typename List<Pair<K,T>>::iterator begin() { return List<Algos::Pair<K,T>>::begin(); }
    typename List<Pair<K,T>>::iterator end() { return List<Algos::Pair<K,T>>::end(); }

    typename List<Pair<K,T>>::const_iterator cbegin() const { return List<Algos::Pair<K,T>>::cbegin(); }
    typename List<Pair<K,T>>::const_iterator cend() const { return List<Algos::Pair<K,T>>::cend(); }
    
    void insert(const K& k, const T& t);
    void remove(const K& k);
    bool contains(const K& k);
    const T& top() const;
    T peak();
      
protected:

    void heapup(int i);
    void heapdown();
    int search(const K& k); 
    inline const K& getKey(int i) { return List<Pair<K,T>>::operator[](i).first; }
    inline bool validIdx(int i) { return i<size(); }
};

template <class K, class T>
void Heap<K,T>::insert(const K& k, const T& t) {
  this->append(Pair<K,T>(k,t));
  heapup(size()-1);  
}

template <class K, class T>
void Heap<K,T>::remove(const K& k) {

}

template <class K, class T>
bool Heap<K,T>::contains(const K& k) {
  for(const auto& d : *this) {
    if(d.first == k) {
      return true;
    }
  }
  return false;
}

template <class K, class T>
const T& Heap<K,T>::top() const {
  ALGO_ASSERT(size() > 0, "Heap is empty");
  return (*this)[0];
}

template <class K, class T>
T Heap<K,T>::peak() {
  ALGO_ASSERT(size() > 0, "Heap is Empty"); 
  if(size() >= 2) {
    List<Pair<K,T>>::swap(0,size()-1);
  }
  T t = List<Pair<K,T>>::takeLast().second;
  heapdown();
  return t;
}

template <class K, class T>
void Heap<K,T>::heapup(int i) {
  
  i+=1;
  while(i>1) {
    int parent = i/2;
    int parent_value = getKey(parent-1);
    int i_value = getKey(i-1);
    if(parent_value > i_value) {
      List<Pair<K,T>>::swap(i-1,parent-1);
    }
    i=parent;
  }
}

template <class K, class T>
void Heap<K,T>::heapdown(){
  int parent=1; //start from the root.
  while(parent-1<size()) {
    int leftIdx = parent*2;
    int rightIdx = parent*2 + 1;
    bool vLeftIdx = leftIdx-1 < size();
    bool vRightIdx = rightIdx-1 < size();
    
    if(vLeftIdx || vRightIdx) {
      int idx=0;
      if(vLeftIdx && vRightIdx) {
        idx = List<Pair<K,T>>::operator[](leftIdx-1).first < 
        List<Pair<K,T>>::operator[](rightIdx-1).first ? leftIdx : rightIdx;
      }
      else {
        idx = vLeftIdx ? leftIdx : rightIdx;
      }

      K currentKey = List<Pair<K,T>>::operator[](idx-1).first;
      K parentKey = List<Pair<K,T>>::operator[](parent-1).first; 
      if(currentKey < parentKey) { 
        List<Pair<K,T>>::swap(idx-1, parent-1); 
        parent = idx;
      }
      else { 
        return; //heap property achieved 
      }
    }
    else { 
      return; //no child
    }
  }
}

}

#endif
