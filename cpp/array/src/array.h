#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

namespace Algos {

template <class T>
class Array {  
   
   public:
      explicit Array(int _size);
      explicit Array(int size, const T &t);
      
      T& operator[](int i) { assert(i<_size); return _data[i]; }
      T operator[](int i) const {  assert(i<_size); return _data[i]; }
      
      int size() const { return _size; }

      int resize(int new_size) {
         if (new_size > size) { return increase(new_size); }
         if(new_size < size) { return decrease(new_size); }
         return size();
      }

   protected:

      int increase(int new_size);
      int decrease(int new_size);

   private:

      std::unique_ptr <T[]> _data;
      int _size;
      bool _resizeable;
};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Array<T>::Array(int size) : _size(size), _resizeable(true){
   _data = std::make_unique<T[]>(_size);
}

template <class T>
Algos::Array<T>::Array(int size, const T &t) : Array(size){
   for(int i=0; i<_size; i++) {
      _data[i] = t;
   }
}

template <class T>
int Algos::Array<T>::increase(int new_size){
   return _size;
}

template <class T>
int Algos::Array<T>::decrease(int new_size){
   return _size;
}

#endif
