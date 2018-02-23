#ifndef __ARRAY_DATA_HH__
#define __ARRAY_DATA_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

namespace Algos {

template <class T>
class DataArray {  
   
      static const int DEFAULT_ALLOCATION = 256;

public:
	    DataArray() : _size(0), _allocated_size(DEFAULT_ALLOCATION) {
        _data = std::make_unique<T[]>(_allocated_size);
      }

      explicit DataArray(int _size);
      explicit DataArray(int size, const T &t);
      explicit DataArray(const DataArray& data_array) : 
         DataArray(data_array.size()) { 
            this->copyFrom(data_array); 
         }
            
      T& operator[](int i) { assert(i<_size); return _data[i]; }
      const T& operator[](int i) const {  assert(i<_size); return _data[i]; }
      
      inline int size() const { return _size; }

      void copyFrom(const DataArray<T>& other);

      bool resize(int new_size) { 
         if(new_size == 0) { _size = new_size; return true; }
         if(new_size>size()) {  return increase(new_size); }
         if(new_size<size()) { return decrease(new_size); }
         return true;
      }

      bool increase(int new_size);
      bool decrease(int new_size);

	    int allocatedSize() { return _allocated_size; }
      bool reserve(int reserve_size) {
        if(reserve_size < _allocated_size) { return true; }
        allocate(reserve_size, _size);
      }
  
  protected:

      bool allocate(int allocate_intent, int new_size);
   
   private:
      std::unique_ptr <T[]> _data;
		  int _size;
		  int _allocated_size;
      
};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::DataArray<T>::DataArray(int size) : _size(size), _allocated_size(DEFAULT_ALLOCATION) {
  if(_size > _allocated_size) {
    _allocated_size = 2*_size;
  }

  _data = std::make_unique<T[]>(_allocated_size);
}

template <class T>
Algos::DataArray<T>::DataArray(int size, const T &t) : DataArray(size){
   for(int i=0; i<_size; i++) {
      _data[i] = t;
	}
}

template <class T>
void Algos::DataArray<T>::copyFrom(const DataArray<T>& other) {
   //add resize here if  _size < other.size ?
   for(int i=0; (i<other.size())&&(i<size()); i++) {
      _data[i] = other[i];
   }
}

template <class T>
bool Algos::DataArray<T>::increase(int new_size) {
	if(new_size <= size()) { return false; }
  if(new_size <= _allocated_size) {
		_size = new_size;
		return true;
	}

	int allocate_intent = 2*new_size;
  return allocate(allocate_intent, new_size);
}

template <class T>
bool Algos::DataArray<T>::decrease(int new_size) {
  if(new_size >= _size) { return false; }
	// Only deallocate if new size is less then half of the current size
   if(new_size > _allocated_size/2) { 
      _size = new_size;
      return true;
   }

   return allocate(new_size*2, new_size);
}

template <class T>
bool Algos::DataArray<T>::allocate(int allocate_intent, int new_size) {
   std::unique_ptr<T[]> new_data = std::make_unique<T[]>(allocate_intent);
   if(!new_data) { return false; }

   for(int i=0; (i<size())&&(i<allocate_intent); i++) { new_data[i] = _data[i]; }
   
   _data.swap(new_data);
	_size = new_size;
	_allocated_size = allocate_intent;
	return true;
}


#endif
