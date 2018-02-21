#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

#include "array/array.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos {

template <class T>
class Vector : public Array<T> {  
   
public:

      Vector() {}
      explicit Vector(int _size);
      explicit Vector(int size, const T &t);
		  Vector(Vector<T>& a) {  this->_data = a.data();  }

		  void append(const T& value);
      void insert(int index, const T& t);
      void push(const T& t);
      const T& pop();
      void clean();

};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Vector<T>::Vector(int size) : Array<T>(){
  this->_data->reserve(1024);
}

template <class T>
Algos::Vector<T>::Vector(int size, const T &t) {
    
}

#endif
