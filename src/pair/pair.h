#ifndef __QUEUE_HH__
#define __QUEUE_HH__

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>


#include "global/assert.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

template <class F, class S>
struct Pair {
  
  F first;
  S second;
  
  Pair() {}
  Pair(const F& one, const S& two) { first=one; second=two; }
  Pair(const Pair& other) { first=other.first; second = other.second; }
  Pair(Pair&& other) { first=std::move(other.first); second=std::move(other.second); }
  
  bool operator==(const Pair& o) { return (o.first==first)&&(o.second==second); }

  Pair& operator=(const Pair& p) {
    first = p.first;
    second = p.second;
    return (*this);
  }

  Pair& operator=(Pair&& p) {
    first = std::move(p.first);
    second = std::move(p.second);
    return (*this);
  }
  
  void swap(Pair& other) {
    std::swap<Pair>(other, *this);
  }
};


}

#endif
