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
    
  class iterator {
    public:
    
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(pointer ptr) : _ptr(ptr) {}
        // iterator(self_type& it) : _ptr(it._ptr) { }
        self_type operator++() { _ptr++; return *this; } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
        reference operator*() const { return *_ptr; }
        pointer  operator->() const { return _ptr; }
        bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
    private:
        pointer _ptr;
  };

  class const_iterator {
    public:
    
        typedef const_iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        const_iterator(pointer ptr) : _ptr(ptr) {}
        // const_iterator(self_type& it) : _ptr(it._ptr) { }
        self_type operator++() { _ptr++; return *this; } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
        const reference operator*() const { return *_ptr; }
        const pointer  operator->() const { return _ptr; }
        bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
    private:
        pointer _ptr;
  };
      

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
      
      iterator begin() { return iterator(_data.get()); }
      iterator end() { 
        T* ptr_end = &(_data.get()[size()?size()-1:0]);
        ptr_end++;
        return iterator(ptr_end); 
      }
      
      const_iterator cbegin() { return const_iterator(_data.get()); }
      const_iterator cend() { 
        T* ptr_end = &(_data.get()[size()?size()-1:0]);
        ptr_end++;
        return const_iterator(ptr_end); 
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
