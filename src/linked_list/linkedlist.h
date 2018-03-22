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

	LinkedListData() {
		root = std::make_unique<Node>();
		root->prev = nullptr; //last virtual element
		root->next = std::make_unique<Node>();
		last = root->next.get();
		last->prev = root.get();
		last->next = nullptr;
	}

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

	class iterator {
		public:
			typedef iterator self_type;
			typedef T value_type;
			typedef T& reference;
			typedef typename LinkedListData<T>::Node* pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef int difference_type;

			iterator(pointer ptr) : _ptr(ptr) {}
			inline self_type operator++() { _ptr=_ptr->next.get(); return *this; } //PREFIX
			inline self_type operator++(int junk) { self_type i = *this;  
				ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->next.get(); return i; } //POSTFIX
			inline self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			inline self_type operator--(int junk) { self_type i = *this;  
				ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->prev; return i; } //POSTFIX
			inline reference operator*() const { return _ptr->data; }
			inline pointer  operator->() const { return _ptr; }
			inline bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
			inline bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }

			inline self_type operator+(int j) const
        	{ pointer n = _ptr; if (j > 0) while (j--) n = n->next.get(); else while (j++) n = n->prev; return n; }
        	inline self_type operator-(int j) const { return operator+(-j); }
        	inline self_type &operator+=(int j) { return *this = *this + j; }
        	inline self_type &operator-=(int j) { return *this = *this - j; }
		private:
			pointer _ptr;
	};

	class const_iterator {
		public:
		
			typedef const_iterator self_type;
			typedef T value_type;
			typedef const T& reference;
			typedef typename LinkedListData<T>::Node* pointer;
			typedef const typename LinkedListData<T>::Node* const_pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef int difference_type;

			const_iterator(pointer ptr) : _ptr(ptr) {}
			self_type operator++() { _ptr=_ptr->next.get(); return *this; } //PREFIX
			self_type operator++(int) { self_type i = *this; 
				ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->next.get(); return i; } //POSTFIX
			self_type operator--() { _ptr=_ptr->prev; return *this; } //PREFIX
			self_type operator--(int) { self_type i = *this;  
				ALGO_ASSERT(_ptr, "Iterator isn't valid."); _ptr=_ptr->prev; return i; } //POSTFIX
			reference operator*() const { return _ptr->data; }
			const_pointer  operator->() const { return _ptr; }
			bool operator==(const self_type& rhs) const { return _ptr == rhs._ptr; }
			bool operator!=(const self_type& rhs) const { return _ptr != rhs._ptr; }
			inline self_type operator+(int j) const
        	{ pointer n = _ptr; if (j > 0) while (j--) n = n->next.get(); else while (j++) n = n->prev; return n; }
        	inline self_type operator-(int j) const { return operator+(-j); }
        	inline self_type &operator+=(int j) { return *this = *this + j; }
        	inline self_type &operator-=(int j) { return *this = *this - j; }
			
		private:
			pointer _ptr;
		};

		iterator begin(){ return iterator(d->root->next.get()); }
		iterator rbegin(){ return iterator(d->root.get()); }
		//works as the last element points to a virtual element, 
		//i.e. (d->last->next == nullptr) is always true.
		iterator end(){ return iterator(d->last); }
		iterator rend(){ return iterator(d->last->prev); }
		
		const_iterator cbegin() const { return const_iterator(d->root->next.get()); }
		const_iterator crbegin() const { return const_iterator(d->root.get()); }
		//works as the last element points to a virtual element, 
		//i.e. (d->last->next == nullptr) is always true.
		const_iterator cend() const { return const_iterator(d->last); }
		const_iterator crend() const { return const_iterator(d->last->prev); }

		iterator insert(iterator before, const T &t) {
			std::unique_ptr<node_type> new_elem = std::make_unique<node_type>();
			new_elem->data = t;
			new_elem->prev = before->prev;
			before->prev = new_elem.get();
			new_elem->next = std::move(new_elem->prev->next); //transferring ownership
			new_elem->prev->next = std::move(new_elem); //transferring ownership
			d->size++;
			return --before;	
		}

		iterator erase(iterator pos) {
			ALGO_ASSERT(pos != rbegin(), "Can't remove the begin virtual node.");
			ALGO_ASSERT(pos != end(), "Can't remove the end virtual node.");
			
			pos->next->prev = pos->prev;
			iterator it = iterator(pos->next.get());
			//after the following line nobody owns the node pointed by pos.
			//Therefore, the node will be deallocated. (don't use pos after this line !!!)
			pos->prev->next = std::move(pos->next);
			d->size--;
			return it;
		}

		iterator erase(iterator first, iterator last) {
			ALGO_ASSERT(first != rbegin(), "Can't remove the begin virtual node.");
			ALGO_ASSERT(first != end(), "Can't remove the end virtual node.");
			ALGO_ASSERT(last != rbegin(), "Can't remove the begin virtual node.");
			while(first != last) 
				erase(first++);
			return last; 
		}

		inline T& last() { return *(--end()); }
		inline const T& last() const { return *(--cend()); }
		inline T& first()  { return *(begin()); }
		inline const T& first() const { return *(cbegin()); }	

		void append(const T &t);
   	void prepend(const T &t);
   	T takeFirst();
   	T takeLast();
   	int removeAll(const T &t);
   	bool removeOne(const T &t);
   	bool contains(const T &t) const;
		int count(const T &t) const;
		
		inline void removeFirst() { ALGO_ASSERT(size(), "Empty List."); erase(begin()); }
    	inline void removeLast() { ALGO_ASSERT(size(), "Empty List."); erase(--end()); }
		
};

template <class T>
void LinkedList<T>::append(const T& t) {
	std::unique_ptr<node_type> new_last = std::make_unique<node_type>();
	new_last->data = t;
	new_last->prev = d->last->prev;
	d->last->prev = new_last.get();
	new_last->next = std::move(new_last->prev->next);
	new_last->prev->next = std::move(new_last);
	d->size++;
}

template <class T>
void LinkedList<T>::prepend(const T& t) {
	std::unique_ptr<node_type> new_first = std::make_unique<node_type>();
	new_first->data = t;
	new_first->prev = d->root.get();
	d->root->next->prev = new_first.get();
	new_first->next = std::move(d->root->next);
	d->root->next = std::move(new_first);
	d->size++;
}

template <class T>
T LinkedList<T>::takeFirst() {
	ALGO_ASSERT(size()>0, "Empty list (No first element)");
	iterator it = begin();
	T t = *it;
	erase(it);
	return t;
}

template <class T>
T LinkedList<T>::takeLast() {
	ALGO_ASSERT(size()>0, "Empty list (No last element)");
	iterator it = --cend();
	T t = *it;
	erase(it);
	return t;
}

template <class T>
int LinkedList<T>::removeAll(const T &t) {
	int count=0;
	for(iterator it=begin(); it!=end(); ) {
		if(*it == t) { 
			it = erase(it); 
			count++;
		}
		else {
			++it;
		}
	}
	return count;
}

template <class T>
bool LinkedList<T>::removeOne(const T &t) {
	for(iterator it=begin(); it!=end(); ++it) {
		if(*it == t) { 
			erase(it); 
			return true;
		}
	}
	return false;
}

template <class T>
bool LinkedList<T>::contains(const T &t) const {
	for(iterator it=begin(); it!=end(); ++it) {
		if(*it == t) { 
			return true;
		}
	}
	return false;
}

template <class T>
int LinkedList<T>::count(const T &t) const{
	int count=0;
	for(iterator it=begin(); it!=end(); ++it) {
		if(*it == t) 
			count++;
	}
	return count;
}

}

#endif
