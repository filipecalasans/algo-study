#ifndef ALGOS_STACK_HH
#define ALGOS_STACK_HH

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>


#include "global/assert.h"
#include "list/list.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos
{

template <class T>
class Stack : public List<T>
{
  
  public: 
    
    Stack() {}
    Stack(const Stack& other)
    {
      this->d = other.d;
    }
    
    Stack& operator=(const Stack& other)
    {
      this->d = other.d;
      return (*this);
    }
    
    void push(const T& t)
    {
      List<T>::append(t);
    }

    T pop()
    {
      return List<T>::takeLast();
    }

    T& top()
    {
      return (*this)[this->size()-1];
    }

    const T& top() const
    {
      return (*this)[this->size()-1];
    }

    void swap(Stack<T>& other)
    {
      std::swap(this->d, other.d);
    }
};

}

#endif
