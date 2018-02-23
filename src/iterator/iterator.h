#ifndef __ITERATOR_HH__
#define __ITERATOR_HH__

#include <iterator>
#include <memory>

namespace Algos{

   template <typename T>
   class iterator {
      public:
      
         typedef iterator self_type;
         typedef T value_type;
         typedef T& reference;
         typedef std::shared_ptr<T> pointer;
         typedef std::forward_iterator_tag iterator_category;
         typedef int difference_type;

         iterator(pointer ptr) : _ptr(ptr) {}
         self_type operator++() { _ptr++; return *this; } //PREFIX
         self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
         reference operator*() { return *_ptr; }
         pointer  operator->() { return _ptr; }
         bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
         bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }
      private:
         pointer _ptr;
   };

   template <typename T>
   class const_iterator {
      public:
      
         typedef const_iterator self_type;
         typedef T value_type;
         typedef T& reference;
         typedef std::shared_ptr<T> pointer;
         typedef std::forward_iterator_tag iterator_category;
         typedef int difference_type;

         const_iterator(pointer ptr) : _ptr(ptr) {}
         self_type operator++() { _ptr++; return *this; } //PREFIX
         self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } //POSTFIX
         const reference operator*() { return *_ptr; }
         const pointer  operator->() { return _ptr; }
         bool operator==(const self_type& rhs) const { return _ptr == rhs.operator->(); }
         bool operator!=(const self_type& rhs) const { return _ptr != rhs.operator->(); }
      private:
         pointer _ptr;
   };
}

#endif