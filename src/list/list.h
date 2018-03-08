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
void Algos::ListData<T>::realloc(int alloc) {
  std::unique_ptr<Data, DataDeleter> x(new Data);
  x->array = new T*[alloc ? alloc : 1]; 
  x->alloc = alloc ? alloc : 1;
  if(!alloc) { 
    x->begin = x->end = 0;
  }
  else {
    int min_alloc = d->alloc;
    if(min_alloc < x->alloc) { min_alloc=x->alloc; }
    ::memcpy(x->array, d->array, min_alloc * sizeof(T*)); //can be optimized
    x->begin = d->begin;
    x->end = d->end <= x->alloc ? d->end : x->alloc;
  }
  d = std::move(x);
}

template <typename T>
T** Algos::ListData<T>::erase(){

}

template <typename T>
T** Algos::ListData<T>::append(){
  if(d->end == d->alloc) { 
    int n = d->end - d->begin;
    if(d->begin > d->alloc/3) {
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

}

template <typename T>
T** Algos::ListData<T>::insert(int i){

}



#endif
