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

	LinkedListData() : root(nullptr) {}

	//deferr pointers manually to avoid stackoverflow due to 
	//recursion explosion
	static void cleanup(LinkedListData<T> *data) { 
		Node *n = data->last;
		if(n==nullptr) { return; }
		while(n) {
			n->next.release();
			ALGO_ASSERT(n->next.get() == nullptr, "Node reference not deferred");
			n = n->prev;
		}
	} 
};

template <class T>
class LinkedList {

	typedef typename LinkedListData<T>::Node node_type;
	std::shared_ptr<LinkedListData<T> > d;

	public:
		
		LinkedList() : d(new LinkedListData<T>(), LinkedListData<T>::cleanup){}
		inline int size() { return d->size; }
		inline bool isEmpty() { return d->size == 0; }
		inline bool operator==(const LinkedList<T>& other) { return (other.d == d); }
		inline LinkedList<T>& operator=(const LinkedList<T>& other) {
			if(other.d != d){ d = other.d; }
			return (*this);
		}

		void append(const T &t);
   	void prepend(const T &t);
   	T takeFirst();
   	T takeLast();
   	int removeAll(const T &t);
   	bool removeOne(const T &t);
   	bool contains(const T &t) const;
   	int count(const T &t) const;


	class iterator {
		public:
			typedef iterator self_type;
			typedef T value_type;
			typedef T& reference;
			typedef typename LinkedListData<T>::Node* pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef int difference_type;

			iterator(pointer ptr) : _ptr(ptr) {}
			self_type operator++() { _ptr=_ptr->next.get(); return *this; } //PREFIX
			self_type operator++(int junk) { self_type i = *this;  ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->next; return i; } //POSTFIX
			self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			self_type operator--(int junk) { self_type i = *this; ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->prev; return i; } //POSTFIX
			
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
			self_type operator++() { _ptr=_ptr->next.get(); return *this; } //PREFIX
			self_type operator++(int junk) { self_type i = *this; ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->next; return i; } //POSTFIX
			self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			self_type operator--(int junk) { self_type i = *this; ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->prev; return i; } //POSTFIX
			
			reference operator*() const { return *_ptr; }
			pointer  operator->() const { return _ptr; }
			bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
			bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
		private:
			pointer _ptr;
		};
		
		iterator begin(){ return iterator(d->root.get()); }
		iterator end(){ return iterator(d->last); }

};

template <class T>
void LinkedList<T>::append(const T& t) {
	if(size() == 0) {
		d->root = std::make_unique<node_type>();
		d->root->prev = nullptr;
		d->root->next = nullptr;
		d->root->data = t;
		d->last = d->root.get();
		d->size++;
		return;
	}

	ALGO_ASSERT(d->last->next.get() == nullptr, "This is not the last element.");

	d->last->next = std::make_unique<node_type>(); //ownership definition
	d->last->next->prev = d->last;
	d->last = d->last->next.get();//update the last element reference
	d->last->next = nullptr;
	d->last->data = t;
	d->size++;
}

template <class T>
void LinkedList<T>::prepend(const T& t) {
	if(size()==0) {
		d->root = std::make_unique<node_type>();
		d->root->prev = nullptr;
		d->root->next = nullptr;
		d->root->data = t;
		d->last = d->root.get();
		d->size++;
		return;
	}

	ALGO_ASSERT(d->root->prev == nullptr, "This isn't the first element.");
	
	std::unique_ptr<node_type> new_root = std::make_unique<node_type>();
	d->root->prev = new_root.get();;
	new_root->next = std::move(d->root);
	d->root = std::move(new_root);
	d->root->prev = nullptr;
	d->root->data = t;
	d->size++;
}

template <class T>
T LinkedList<T>::takeFirst() {

}

template <class T>
T LinkedList<T>::takeLast() {

}

template <class T>
int LinkedList<T>::removeAll(const T &t) {

}

template <class T>
bool LinkedList<T>::removeOne(const T &t) {

}

template <class T>
bool LinkedList<T>::contains(const T &t) const {

}

template <class T>
int LinkedList<T>::count(const T &t) const{

}

}

#endif
