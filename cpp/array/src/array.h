#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

// #include "dataarray.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos {

template <class T>
class Array {  
   
public:

      Array() {}
      explicit Array(int _size);
      explicit Array(int size, const T &t);
      
      // T& operator[](int i) { assert(i<_size); return (_data.get())[i]; } //deep copy here.
      // T operator[](int i) const {  assert(i<_size); return (_data.get())[i]; }
      
      int size() const { return 0; }

      Array& operator=(const Array& other) { return (*this); }

   private:

      // std::shared_ptr <DataArray<T> > _data;

};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Array<T>::Array(int size) {
      // _data = std::shared_ptr<T>(new T[_size], std::default_delete<T[]>());
}

template <class T>
Algos::Array<T>::Array(int size, const T &t) : Array(size){
//    for(int i=0; i<_size; i++) {
//       ((T*)_data.get())[i] = t;
// 	}
}

#endif
