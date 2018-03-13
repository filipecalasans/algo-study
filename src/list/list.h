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

    T** erase(T** xi);
    T** append();
    T** prepend();
    T** insert(int i);
    void remove(int i);
    void remove(int i, int n);
    void move(int from, int to);
    inline int size() const { return d->end - d->begin;}
    inline bool isEmpty() const { return d->end == d->begin; }
    inline T** at(int i) const { return d->array + d->begin + i; }
    inline T** begin() const { return d->array + d->begin; }
    inline T** end() const { return d->array + d->end; }
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
void Algos::ListData<T>::remove(int i) {
  i += d->begin;
  int n = (d->end - d->begin);
  int middle_idx = d->begin + n/2;
  if(i > middle_idx) { //move the right section to <-
    if(int slice_size = (d->end - i -1)) {
      ::memmove(d->array+i, d->array+i+1, slice_size * sizeof(T*));
    }
    d->end--;
  }
  else { //move the left section to ->
    if(int slice_size = i - d->begin) {
      ::memmove(d->array+d->begin+1, d->array+d->begin, slice_size*sizeof(T*));
    }
    d->begin++;
  }
}

template <typename T>
void Algos::ListData<T>::remove(int i, int n) {
  int middle = d->begin + i + n/2;
  if(d->end - middle > middle - d->begin) { 
    ::memmove(d->array+d->begin+n, d->array+d->begin, i*sizeof(T*));
    d->begin += n;
  }
  else {
    int offset = d->end - (d->begin+i+n);
    ::memmove(d->array+d->begin+i, d->array+d->begin+i+n, offset*sizeof(T*));    
    d->end -= n;
  }
}

template <typename T>
T** Algos::ListData<T>::erase(T** xi){
  int i = xi - (d->array + d->begin);
  remove(i);
  return d->array + d->begin + i; //return the element in the possition.
}

template <typename T>
void Algos::ListData<T>::move(int from, int to) {

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

  if(i<=0) { return prepend(); }

  int list_size = size();
  if(i>=list_size) { return append(); }

  if(list_size >= d->alloc) {
    realloc(grow(d->alloc+1));
  }

  bool leftToRight= true;

  if(d->begin == 0) {
    leftToRight=true;
  }
  else if (d->end == 0) {
    leftToRight=false;
  }
  else {
    int middle_idx = d->begin + list_size/2;
    leftToRight = (i+d->begin < middle_idx);
  }

  if(leftToRight) {
    ::memmove(d->array+d->begin+i+1, d->array+d->begin+i, (list_size-i)*sizeof(T*));
    d->end++;
  }
  else {
    ::memmove(d->array+d->begin-1, d->array+d->begin, (i)*sizeof(T*));
    d->begin--;
  }
  return d->array+d->begin+i;
}


#endif
