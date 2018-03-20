#ifndef __LINKED_LIST_HH__
#define __LINKED_LIST_HH__

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
namespace Algos {

  template <typename T>
  struct LinkedListData{
		struct Node {
      	std::unique_ptr<Node> next;
      	Node *prev = nullptr;
      	T data;
    	};

   	std::unique_ptr<Node> root;
    	Node *last = nullptr;
	 	int size = 0;

	};

  template <class T>
  class LinkedList {

	std::shared_ptr<LinkedListData<T>> d;
	//iterate backwards defer nodes. Avoid stack overflow due to recursion explosion.
	void cleanup(LinkedListData<T> *data);  
	
public:
	
		LinkedList() {
			d = std::shared_ptr<LinkedListData<T>> (new LinkedListData<T>(), cleanup);
		}

		inline int size() { return d->size; }
		bool operator==(const LinkedList<T>& other) { return (other.d == d); }

	class iterator {
		public:
		
			typedef iterator self_type;
			typedef T value_type;
			typedef T& reference;
			typedef typename LinkedListData<T>::Node* pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef int difference_type;

			iterator(pointer ptr) : _ptr(ptr) {}
			self_type operator++() { _ptr=_ptr->next; return *this; } //PREFIX
			self_type operator++(int junk) { self_type i = *this; _ptr=_ptr->next; return i; } //POSTFIX
			self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			self_type operator--(int junk) { self_type i = *this; _ptr=_ptr->prev; return i; } //POSTFIX
			
			reference operator*() const { return _ptr->data; }
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
			typedef const T& reference;
			typedef const typename LinkedListData<T>::Node* pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef int difference_type;

			const_iterator(pointer ptr) : _ptr(ptr) {}
			self_type operator++() { _ptr=_ptr->next; return *this; } //PREFIX
			self_type operator++(int junk) { self_type i = *this; _ptr=_ptr->next; return i; } //POSTFIX
			self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			self_type operator--(int junk) { self_type i = *this; _ptr=_ptr->prev; return i; } //POSTFIX
			
			reference operator*() const { return *_ptr; }
			pointer  operator->() const { return _ptr; }
			bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
			bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
		private:
			pointer _ptr;
	};
  
    };

}

#endif
