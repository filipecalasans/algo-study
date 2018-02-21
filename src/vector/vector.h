#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

#include "array.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos {

template<class T> class Array;

template <class T>
class Vector : public Array<T> {  
   
public:

      Vector() : Array<T>() {}
      explicit Vector(int _size);
      explicit Vector(int size, const T &t);
		  Vector(Vector<T>& a) {  _data = a.data();  }

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
  _data->reserve(1024);
}

template <class T>
Algos::Vector<T>::Vector(int size, const T &t) {
    
}

#endif
