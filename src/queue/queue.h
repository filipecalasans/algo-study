#ifndef __QUEUE_HH__
#define __QUEUE_HH__

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>


#include "global/assert.h"
#include "list/list.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

template <class T>
class Queue : public List<T> {
  
  public: 
    
    Queue() {}
    Queue(const Queue& other) {
      this->d = other.d;
    }
    
    Queue& operator=(const Queue& other) {
      this->d = other.d;
      return (*this);
    }

    void enqueue(const T& t) {
      List<T>::append(t);
    }

    T dequeu() {
      return List<T>::takeFirst();
    }

    T& head() {
      return (*this)[0];
    }

    const T& head() const {
      return (*this)[0];
    }

    void swap(Queue<T>& other) {
      std::swap(this->d, other.d);
    }
    

};

}

#endif
