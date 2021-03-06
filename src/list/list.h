#ifndef ALGOS_LIST_HH
#define ALGOS_LIST_HH

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>


#include "global/assert.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { //TODO: implement using smart pointers.

  template <typename T>
  struct ListData
  {
    struct Data
    {
      int alloc, begin, end;
      T** array = nullptr;
      bool allow_obj_cleanup = true;
      
      Data()
      {
        array = new T*[1];
        array[0] = nullptr;
        alloc = 1;
        begin = 0;
        end = 0;
      }

      ~Data()
      {
        if(alloc <= 0) { return; }
        if(array == nullptr) { return; }
        if(allow_obj_cleanup)
        {
            for(int i=begin; i<end; i++)
            {
                if(array[i]!=nullptr)
                {
                    delete array[i];
                }
            }
        }
        delete[] array;
      }

      void reallocArray(int alloc)
      {
        delete[] array; //it's still empty.
        array = new T*[alloc ? alloc : 1]; 
        this->alloc = alloc ? alloc : 1;
        for(int i=0; i<this->alloc; i++)
        {
            array[i] = nullptr;
        }
      }

    };

    std::unique_ptr<Data> d;

    ListData() : d(std::make_unique<Data>()) {}

    void realloc(int alloc);
    void reallocAndMove(int new_begin, int alloc);
    void swap(int i, int j);
    
    T** erase(T** xi);
    T** append();
    T** prepend();
    T** insert(int i);
    void remove(int i);
    void remove(int i, int n);
    void move(int from, int to);
    inline size_t size() const { return d->end - d->begin;}
    inline bool isEmpty() const { return d->end == d->begin; }
    inline T** at(int i) const { return d->array + d->begin + i; }
    inline T** begin() const { return d->array + d->begin; }
    inline T** end() const { return d->array + d->end; }
    inline int grow(size_t size) { return size * 2; }
  };

  template <class T>
  class List {  
    
  public:
      
      std::shared_ptr<ListData<T>> d;

      List() : d(std::make_shared<ListData<T>>()) {}
      List(const List& other)
      {
        d = other.d;
      }
      List(List&& other)
      {
          d = other.d;
          other.d = nullptr;
      }

      ~List();

      List<T> &operator=(const List<T>& other)
      {
        d = other.d; 
        return (*this); 
      }

      List<T> &operator=(List<T>&& other)
      {
        d = other.d; 
        other.d = nullptr; //invalidate the other ListData
        return (*this); 
      }

      bool operator==(const List<T>& other) const { d == other.d; }
      inline bool operator!=(const List<T> &other) const { return !(d == other.d); }
      inline size_t size() const { return d->size(); }
      inline bool isEmpty() const { return d->size() == 0; }
      inline void reserve(size_t size) { d->realloc(size); }
      inline void swap(int i, int j) { d->swap(i,j); }

      //Copy based operations.
      void append(const T& t);
      void append(T&& t);
      void append(const List<T>& l);
      void prepend(const T& t); 
      void insert(const T& t, int i); 
      void replace(const T& t, int i);
      void removeAt(int i); 
      int removeAll(const T &t);
      bool removeOne(const T &t);
      T takeAt(int i);
      T takeFirst();
      T takeLast();
      void clear() { while(size()) removeAt(0); }

      //Add move based operations.
      T& operator[](int i) { 
        ALGO_ASSERT(i<size(), "Index out of range");
        return (**(d->at(i)));
      }

      const T& operator[](int i) const { 
        ALGO_ASSERT(i<size(), "Index out of range");
        return (**(d->at(i)));
      }


      class iterator {
        public:
        
            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer_to_obj;
            typedef T** pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;

            iterator(pointer ptr) : _ptr(ptr) {}
            self_type operator++() { _ptr++; return *this; } //PREFIX
            self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
            reference operator*() { return **_ptr; }
            pointer_to_obj  operator->() const { return *_ptr; }
            bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
            bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }
        private:
            pointer _ptr;
      };

      class const_iterator {
        public:
        
            typedef const_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer_to_obj;
            typedef T** pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;

            const_iterator(pointer ptr) : _ptr(ptr) {}
            self_type operator++() { _ptr++; return *this; } //PREFIX
            self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
            const reference operator*() const { return **_ptr; }
            const pointer_to_obj  operator->() const { return *_ptr; }
            bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
        private:
            pointer _ptr;
      };
      

      iterator begin() { return iterator(d->size() ? d->begin() : nullptr); }
      iterator end() { return iterator(d->size() ? d->end() : nullptr); }

      const_iterator cbegin() const { return const_iterator(d->size() ? d->begin() : nullptr); }
      const_iterator cend() const { return const_iterator(d->size() ? d->end() : nullptr); }

  };

}

template <typename T> 
void Algos::ListData<T>::reallocAndMove(int new_begin, int alloc)
{
  ALGO_ASSERT(alloc > 0, "Allocation size can't be lessor or equal to 0.");
  
  std::unique_ptr<Data> x = std::make_unique<Data>();  
  x->reallocArray(alloc);  

  if(!alloc)
  {
    x->begin = x->end = 0;
  }
  else
  {
    int cpy_size = d->end - d->begin;
    if(d->begin > x->alloc) { cpy_size = 0; } //error, must never happen
    else if(d->end > x->alloc ) { cpy_size = x->alloc-d->begin; }
    ::memcpy(x->array+new_begin, d->array+d->begin, cpy_size * sizeof(T*));
    x->begin = new_begin;
    x->end = new_begin + cpy_size;
  }
  d->allow_obj_cleanup = false;
  d = std::move(x);
  d->allow_obj_cleanup = true;
}

template <typename T>
void Algos::ListData<T>::realloc(int alloc)
{
  reallocAndMove(d->begin, alloc);
}

template <typename T>
void Algos::ListData<T>::swap(int i, int j)
{
  ALGO_ASSERT(d->begin + i < d->end, "Swap index i out of range");
  ALGO_ASSERT(d->begin + j < d->end, "Swap index j out of range");

  T** j_pos = at(j);
  T** i_pos = at(i);
  T* tmp = *i_pos;
  *i_pos = *j_pos;
  *j_pos = tmp;
}

template <typename T>
void Algos::ListData<T>::remove(int i)
{
  i += d->begin;
  int n = (d->end - d->begin);
  int middle_idx = d->begin + n/2;
  if(i > middle_idx)
  { //move the right section to <-
    if(int slice_size = (d->end - i -1))
    {
      ::memmove(d->array+i, d->array+i+1, slice_size * sizeof(T*));
    }
    d->end--;
  }
  else
  { //move the left section to ->
    if(int slice_size = i - d->begin)
    {
      ::memmove(d->array+d->begin+1, d->array+d->begin, slice_size*sizeof(T*));
    }
    d->begin++;
  }
  
}

template <typename T>
void Algos::ListData<T>::remove(int i, int n)
{
  int middle = d->begin + i + n/2;
  if(d->end - middle > middle - d->begin)
  {
    ::memmove(d->array+d->begin+n, d->array+d->begin, i*sizeof(T*));
    d->begin += n;
  }
  else
  {
    int offset = d->end - (d->begin+i+n);
    ::memmove(d->array+d->begin+i, d->array+d->begin+i+n, offset*sizeof(T*));    
    d->end -= n;
  }
}

template <typename T>
T** Algos::ListData<T>::erase(T** xi)
{
  int i = xi - (d->array + d->begin);
  remove(i);
  return d->array + d->begin + i; //return the element in the possition.
}

template <typename T>
void Algos::ListData<T>::move(int from, int to)
{

}

template <typename T>
T** Algos::ListData<T>::append()
{
  if(d->end == d->alloc)
  {
    int n = d->end - d->begin;
    if(d->begin > 2*d->alloc/3) {
      ::memcpy(d->array+n, d->array+n, n*sizeof(T*));
      d->begin = n;
      d->end = d->begin+n;
    } 
    else
    {
      realloc(grow(d->alloc + 1));
    }
  }
  return d->array + d->end++;
}

template <typename T>
T** Algos::ListData<T>::prepend()
{
  if(d->begin == 0)
  {
    int n = d->end - d->begin;
    int new_begin = d->begin;
    int new_alloc = grow(d->alloc+1);
    if(d->end < new_alloc/3)
    {
      new_begin = new_alloc - 2*n;
    }
    else
    {
      new_begin = new_alloc-n;
    }
    reallocAndMove(new_begin, new_alloc);
  }
  return d->array + --d->begin;
}

template <typename T>
T** Algos::ListData<T>::insert(int i)
{
  if(i<=0) { return prepend(); }

  int list_size = size();
  if(i>=list_size) { return append(); }

  if(list_size >= d->alloc)
  {
    realloc(grow(d->alloc+1));
  }

  bool leftToRight= true;

  if(d->begin == 0)
  {
    leftToRight=true;
  }
  else if (d->end == 0)
  {
    leftToRight=false;
  }
  else {
    int middle_idx = d->begin + list_size/2;
    leftToRight = (i+d->begin < middle_idx);
  }

  if(leftToRight)
  {
    ::memmove(d->array+d->begin+i+1, d->array+d->begin+i, (list_size-i)*sizeof(T*));
    d->end++;
  }
  else
  {
    ::memmove(d->array+d->begin-1, d->array+d->begin, (i)*sizeof(T*));
    d->begin--;
  }
  return d->array+d->begin+i;
}

/* List<T> implementation */

template <class T>
Algos::List<T>::~List()
{
  /*while(size()) { 
    removeAt(0);
  }*/
}

template <class T>
void Algos::List<T>::append(const T& t)
{
  T* elem = new T();
  *elem = t;
  T** slot = d->append();
  *slot = elem;
}

template<class T>
void Algos::List<T>::append(T&& t)
{
    T* elem = new T(t);
    T** slot = d->append();
    *slot = elem;
}

template <class T>
void Algos::List<T>::append(const List<T>& l)
{
  for(int i=0; i<l.size(); i++)
  {
    append(l[i]);
  }
}

template <class T>
void Algos::List<T>::prepend(const T& t)
{
  T* elem = new T();
  *elem = t;
  T** slot = d->prepend();
  *slot = elem;
}

template <class T>
void Algos::List<T>::insert(const T& t, int i)
{
  T* elem = new T();
  *elem = t;
  T** slot = d->insert(i);
  *slot = elem;
}

template <class T>
void Algos::List<T>::replace(const T& t, int i)
{
  ALGO_ASSERT(i<size(), "Index out of range");
  T** old = d->at(i);
  T* elem = new T();
  *elem = t;
  delete (*old);
  *old = elem;
}

template <class T>
void Algos::List<T>::removeAt(int i)
{
  ALGO_ASSERT(i < size(), "Index out of range");
  T** old = d->at(i);
  delete (*old);
  *old = nullptr;
  d->remove(i);
}

template <class T>
int Algos::List<T>::removeAll(const T &t)
{
  int i=0;
  int count=0;
  while(i < size())
  {
    T** elem = d->at(i);
    if(**elem == t)
    {
      removeAt(i);
      count++;
    }
    else
    {
      i++;
    }
  }
  return count;
}

template <class T>
bool Algos::List<T>::removeOne(const T &t)
{
  for(int i=0; i<size(); i++)
  {
    T** elem = d->at(i);
    if(**elem == t)
    {
      removeAt(i);
      return true;
    }
  }
  return false;
}

template <class T>
T Algos::List<T>::takeAt(int i)
{
  ALGO_ASSERT(i < size(), "Index out of range");
  T** old = d->at(i);
  T t = **old;
  removeAt(i);
  return t;
}

template <class T>
T Algos::List<T>::takeFirst()
{
  return takeAt(0);
}

template <class T>
T Algos::List<T>::takeLast()
{
  return takeAt(size()-1);
}

#endif
