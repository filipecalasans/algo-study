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

      Vector() : Array<T>() { }
      explicit Vector(int _size);
      explicit Vector(int size, const T &t);
		  Vector(Vector<T>& a) { this->_data = a.data(); }

		  void append(const T& value);
      void insert(int index, const T& t);
      void removeLast();
      void clear();
      bool resize(int new_size);
};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Vector<T>::Vector(int size) : Array<T>(size){ }

template <class T>
Algos::Vector<T>::Vector(int size, const T& t) : Array<T>(size, t){ }

template <class T>
void Algos::Vector<T>::append(const T& value) {
  if(!Array<T>::_data->resize(Array<T>::size()+1)) { return; }
  (*Array<T>::_data)[Array<T>::size()-1] = value;
}

template <class T>
void Algos::Vector<T>::insert(int index, const T& t) {
  if(index >= Array<T>::size()) { return; }
  (*Array<T>::_data)[index] = t;
}

template <class T>
void Algos::Vector<T>::removeLast() {
  if(Array<T>::size() <= 0) { return; }
  (Array<T>::_data)->resize(Array<T>::size()-1);
}

template <class T>
void Algos::Vector<T>::clear() {
  (Array<T>::_data)->resize(0);
}

template <class T>
bool Algos::Vector<T>::resize(int new_size) {
  return (Array<T>::_data->resize(new_size));
}





#endif
