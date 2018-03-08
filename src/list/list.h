#ifndef __LIST_HH__
#define __LIST_HH__

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <assert.h>

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos {

  template <typename T>
  struct ListData{
    struct Data {
      int alloc, begin, end;
      T** array;
    };

    struct DataDeleter { 
      void operator()(Data* d) { 
        /* std::cout << "Data Deleter" << std::endl;*/ 
        delete[] d->array; 
      }
    };

    std::unique_ptr<Data, DataDeleter> d;

    ListData() : d(new Data) {
      d->array = new T*[1];
      d->alloc = 1;
      d->begin = 0;
      d->end = 0;
    }

    void realloc(int alloc);
    void reallocAndMove(int new_begin, int alloc);

    T** erase();
    T** append();
    T** prepend();
    T** insert(int i);
    void remove(int i);
    void move(int from, int to);
    inline int size() const { return d->end - d->begin;}
    inline bool isEmpty() const { return d->end == d->begin; }
    inline T** at(int i) const { return d->array + d->begin + i; }
    inline T** begin() const { return d->array + d->begin; }
    inline T**end() const { return d->array + d->end; }
    inline int grow(int size) { return size * 2; }
  };

  template <class T>
  class List {  

  };

}

template <typename T> 
void Algos::ListData<T>::reallocAndMove(int new_begin, int alloc) {
  std::unique_ptr<Data, DataDeleter> x(new Data);
  x->array = new T*[alloc ? alloc : 1]; 
  x->alloc = alloc ? alloc : 1;
  if(!alloc) { 
    x->begin = x->end = 0;
  }
  else {
    int cpy_size = d->end-d->begin;
    if(d->begin > x->alloc) { cpy_size = 0; } //error, must never happen
    else if(d->end > x->alloc ) { cpy_size = x->alloc-d->begin; }
    // std::cout << "alloc " << x->alloc << " cpy_size " << cpy_size << std::endl;
    ::memcpy(x->array+new_begin, d->array+d->begin, cpy_size * sizeof(T*));
    x->begin = new_begin;
    x->end = new_begin + cpy_size;
  }
  d = std::move(x);
}

template <typename T>
void Algos::ListData<T>::realloc(int alloc) {
  reallocAndMove(d->begin, alloc);
}

template <typename T>
T** Algos::ListData<T>::erase(){

}

template <typename T>
T** Algos::ListData<T>::append(){
  if(d->end == d->alloc) { 
    int n = d->end - d->begin;
    if(d->begin > 2*d->alloc/3) {
      ::memcpy(d->array+n, d->array+n, n*sizeof(T*));
      d->begin = n;
      d->end = d->begin+n;
    } 
    else {
      realloc(grow(d->alloc + 1));
    }
  }
  return d->array + d->end++;
}

template <typename T>
T** Algos::ListData<T>::prepend(){
  if(d->begin == 0) {
    int n = d->end - d->begin;
    int new_begin = d->begin;
    int new_alloc = grow(d->alloc+1);
    if(d->end < new_alloc/3) {
      new_begin = new_alloc - 2*n;
    }
    else {
      new_begin = new_alloc-n;
    }
    reallocAndMove(new_begin, new_alloc);
  }
  return d->array + --d->begin;
}

template <typename T>
T** Algos::ListData<T>::insert(int i){

}



#endif
