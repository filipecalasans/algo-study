#ifndef __RBTREE_HH__   
#define __RBTREE_HH__ 

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "global/assert.h"
#include "list/list.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

//typedef typename RBTree<K,T>::Node Node;

template <class K, class T>
struct RBTree {
  
  struct Node {  
    
    bool red;
    K key;
    T value;
    
    Node *parent;
    std::unique_ptr<Node> leftChild, rightChild;  
    
    Node() : red(true), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {} 
    Node(const K& k, const T& t) : Node() { key=k; value=t; }

    Node *grandparent() {
      if(parent == nullptr) { return nullptr; }
      return parent->parent;
    }
    
    Node* createNode(const K& k, const T& t, bool onLeftChild) {
      if(onLeftChild) {
        leftChild = std::make_unique<Node>(k, t);
        return leftChild.get();
      }
      else {
        rightChild = std::make_unique<Node>(k, t);
        return rightChild.get();
      }
    }

    const Node *previousNode(Node *n) const; //TODO
    const Node *nextNode(Node *n) const; //TODO
    
 };
  
  
  typedef typename RBTree<K,T>::Node Node;
  
  RBTree() : _size(0), root(nullptr), mostLeftNode(nullptr) { }
  size_t _size;
  std::unique_ptr<Node> root;
  Node *mostLeftNode;
  
  inline size_t size() { return _size; }
  inline bool isRed(Node *n) { return n!=nullptr ? false : n->red;  }
  void rotateLeft(Node *n);
  void rotateRight(Node *n);
  
  void insertData(const K& k, const T& t);
  Node* insertNode(const K& k, const T& t);
  
  void cleanup();
  void assert_inorder();

};

template <class K, class T>
void RBTree<K,T>::rotateLeft(Node *n) {
  ALGO_ASSERT(n->right != nullptr, "Cannot rotateRight leaf nodes.");
  std::unique_ptr<Node> nnew = std::move(n->rightChild); //get the ownership
  n->rightChild = std::move(nnew->leftChild);
  n->rightChild->parent = n;
  nnew->parent = n->parent;
  n->parent = nnew.get();
  if(root.get() == n) {
    root = std::move(nnew);
  }
  else if(nnew->parent->lefChild.get() == n) { //update the sub-tree ownership
    nnew->parent->leftChild = std::move(nnew);
  }
  else { 
    nnew->parent->rightChild = std::move(nnew);
  }
}

template <class K, class T>
void RBTree<K,T>::rotateRight(Node *n) {
  ALGO_ASSERT(n->left != nullptr, "Cannot rotateLeft leaf nodes.");
  std::unique_ptr<Node> nnew = std::move(n->leftChild);
  n->leftChild = std::move(nnew->rightChild);
  n->leftChild->parent = n;
  nnew->parent = n->parent;
  n->parent = nnew.get();
  if(root.get() == n) {
    root = std::move(nnew);
  }
  else if(nnew->parent->leftChild.get() == n) { //update the sub-tree ownership
    nnew->parent->leftChild = std::move(nnew);
  }
  else { 
    nnew->parent->rightChild = std::move(nnew);
  }
}

template <class K, class T>
void RBTree<K,T>::insertData(const K& k, const T& t) {
  
  Node *n = insertNode(k, t);

  if(size() == 1) { return; } 
  
  //do rbtree proprty check

}

template <class K, class T>
typename RBTree<K,T>::Node* 
RBTree<K,T>::insertNode(const K& k, const T& t) {
  
  if(root.get() == nullptr) {
    root = std::make_unique<Node>();
    root->key - k;
    root->value = t;
    ++_size;
    return root.get();
  }
  
  Node *n = root.get();
  while(n!=nullptr) { //
    if(n->key < k) {
      if(n->leftChild.get() == nullptr) {
        _size++;
        return n->createNode(k, t, true);
      }
      n = n->leftChild.get();
    }
    else {
      if(n->rightChild.get() == nullptr) {
        _size++;
        return n->createNode(k, t, false);
      }
      n = n->rightChild.get();
    }
  }

  ALGO_ASSERT(false, "Error trying to insert a new node");
  return nullptr;
}

template <class K, class T>
void RBTree<K,T>::assert_inorder() {
  //user stack  
}

}

#endif
