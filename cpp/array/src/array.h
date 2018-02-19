#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

#include "dataarray.h"

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
		  Array(Array& a) { _data = a.data();  }

		  const T& operator[](int i) const { 
			  assert(i<size()); 
			  return (*_data.get())[i]; 
		  } 
		
		  T& operator[](int i) { 
			  assert(i<size()); 
			  return (*_data.get())[i];
		  } 
      
      int size() const { return _data->size(); }

      Array& operator=(const Array& other) { 
        _data = other.data();          
        return *this;
      }

		  const std::shared_ptr<DataArray<T> >& data() const { return _data; }
      
      int dataRefCount() const { return _data.use_count(); }
      
      const T& first() {
        assert(_data->size()>0);
        return (*this)[0];
      }

      const T& last() {
        assert(_data->size()>0);
        return (*this)[_data->size()-1];
      }


   private:
      std::shared_ptr <DataArray<T> > _data;

};

}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Array<T>::Array(int size) {
	_data = std::shared_ptr<DataArray<T> >(new DataArray<T>(size));
}

template <class T>
Algos::Array<T>::Array(int size, const T &t) {
	_data = std::shared_ptr<DataArray<T> >(new DataArray<T>(size, t));
}

#endif
