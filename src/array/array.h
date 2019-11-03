#ifndef ALGOS_ARRAY_HH
#define ALGOS_ARRAY_HH

#include <iostream>
#include <cstdint>
#include <memory>

#include "global/assert.h"
#include "dataarray.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos
{

template <class T>
class Array
{

public:

  class iterator
  {
    public:
         
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(const typename DataArray<value_type>::iterator& ptr) : _ptr(ptr) {}
        iterator(const self_type& other) : _ptr(nullptr){ *this = other; }

        self_type operator++() { _ptr++; return (*this); } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
        reference operator*() const { return *_ptr; }
        pointer  operator->() const { return _ptr.operator->(); }
        bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
        self_type& operator=(const self_type& other)
        {
          if(this != &other)
          {
            _ptr = other._ptr;
          }
          return *this;
        }

    private:

        typename DataArray<value_type>::iterator _ptr;
  };

  class const_iterator
  {
    public:
    
        typedef const_iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        const_iterator(const typename DataArray<value_type>::const_iterator& ptr) : _ptr(ptr) {}
        const_iterator(const self_type &other) : _ptr(nullptr){ *this = other; }

        self_type operator++() { _ptr++; return *this; } //PREFIX
        self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
        const reference operator*() const { return *_ptr; }
        const pointer  operator->() const { return _ptr.operator->(); }
        bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
        self_type& operator=(const self_type& other)
        {
          if(this != &other)
          {
            _ptr = other._ptr;
          }
          return (*this);
        }

      private:

        typename DataArray<value_type>::const_iterator _ptr;
  };
  
public:

      Array()
      {
          _data = std::shared_ptr<DataArray<T>>(new DataArray<T>());
      }

      explicit Array(int _size);
      explicit Array(int size, const T &t);
      Array(Array& a) { _data = a.data();  }

      const T& operator[](int i) const
      {
          ALGO_ASSERT(i < size(), "Index out of bounds.");
          return (*_data.get())[i];
      }

      T& operator[](int i)
      {
          ALGO_ASSERT(i < size(), "Index out of bounds.");
          return (*_data.get())[i];
      }
      
      size_t size() const { return _data->size(); }
       
      Array& operator=(const Array& other)
      {
        _data = other.data();          
        return *this;
      }

      const std::shared_ptr<DataArray<T>>& data() const { return _data; }
    
      int dataRefCount() const { return _data.use_count(); }
      
      const T& first()
      {
        ALGO_ASSERT(_data->size()>0, "Index out of range: array empty."); 
        return (*this)[0];
      }

      const T& last()
      {
        ALGO_ASSERT(_data->size()>0, "Index out of range: array empty."); 
        return (*this)[_data->size()-1];
      }
    
      bool empty() { return (_data->size() == 0); }

      iterator begin()
      {
        iterator it = _data->begin();
        return it; 
      }

      iterator end()
      {
        iterator it = _data->end();
        return it; 
      }

      const_iterator cbegin()
      {
        const_iterator it = _data->cbegin();
        return it; 
      }

      const_iterator cend()
      {
        const_iterator it = _data->cend();
        return it; 
      }

   protected:

      std::shared_ptr <DataArray<T>> _data;

    };
    
}

// ######################### Template Implementation  ##############################
template <class T>
Algos::Array<T>::Array(int size)
{
	_data = std::shared_ptr<DataArray<T> >(new DataArray<T>(size));
}

template <class T>
Algos::Array<T>::Array(int size, const T &t)
{
	_data = std::shared_ptr<DataArray<T> >(new DataArray<T>(size, t));
}

#endif
