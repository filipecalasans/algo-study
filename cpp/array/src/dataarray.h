#ifndef __ARRAY_DATA_HH__
#define __ARRAY_DATA_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

namespace Algos {

template <class T>
class DataArray {  
   
public:
	DataArray() :  _size(0) {}
      explicit DataArray(int _size);
      explicit DataArray(int size, const T &t);
      explicit DataArray(const DataArray& data_array) : 
         DataArray(data_array.size()) { 
            this = data_array; 
         }
            
      T& operator[](int i) { assert(i<_size); return _data[i]; } //deep copy here.
      T operator[](int i) const {  assert(i<_size); return _data[i]; }
      
      inline int size() const { return _size; }

      DataArray& operator=(const DataArray& other);

      bool resize(int new_size) { 
         if(new_size>size()) {  return increase(new_size); }
         if(new_size<size()) { return decrease(new_size); }
         return true;
      }

      bool increase(int new_size);
      bool decrease(int new_size);

   private:

      std::unique_ptr <T[]> _data;
      int _size;
      bool allocate(int new_size);
};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::DataArray<T>::DataArray(int size) : _size(size){
   _data = std::make_unique<T[]>(_size);
}

template <class T>
Algos::DataArray<T>::DataArray(int size, const T &t) : DataArray(size){
   for(int i=0; i<_size; i++) {
      _data[i] = t;
	}
}

template <class T>
Algos::DataArray<T>& Algos::DataArray<T>::operator=(const DataArray<T>& other) {
   //add resize here if  _size < other.size ?
   for(int i=0; (i<other.size())&&(i<size()); i++) {
      _data[i] = other[i];
   }
   return (*this);
}

template <class T>
bool Algos::DataArray<T>::increase(int new_size) {   
   if(new_size < 2*size()) { new_size = 2*size(); }

   return allocate(new_size);
}

template <class T>
bool Algos::DataArray<T>::decrease(int new_size) {
	// performance optimization. 
	// Only deallocate if new size is less then half of the current size
   if(new_size > size()/2) { 
      _size = new_size;
      return true;
   }

   return allocate(new_size);
}

template <class T>
bool Algos::DataArray<T>::allocate(int new_size) {
   std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_size);
   if(!new_data) { return false; }

   for(int i=0; (i<size())&&(i<new_size); i++) { new_data[i] = _data[i]; }
   
   _data.swap(new_data);
   _size = new_size;
   return true;
}


#endif
