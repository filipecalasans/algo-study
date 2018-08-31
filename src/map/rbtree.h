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
#include "stack/stack.h"

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

    Node *grandParent() {
      if(parent == nullptr) { return nullptr; }
      if(parent->parent == nullptr) { return nullptr; }
      return parent->parent;
    }

    Node *uncle() {
      Node *p = parent;
      Node *g = grandParent();
      if(g == nullptr) { return nullptr; }
      if(g->leftChild.get() == p) {
        return g->rightChild.get();
      }
      return g->leftChild.get();
    }
    
    Node* createNode(const K& k, const T& t, bool onLeftChild) {
      if(onLeftChild) {
        leftChild = std::make_unique<Node>(k, t);
        leftChild->parent = this;
        return leftChild.get();
      }
      else {
        rightChild = std::make_unique<Node>(k, t);
        rightChild->parent = this;
        return rightChild.get();
      }
    }

    const Node *previousNode() const; 
    const Node *nextNode() const; 

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
 
  const Node* getRightMostNode() const;
  void verifyRepairTree(Node *n);

  void cleanup();
  
  void assert_inorder();

};
//
//                                      20
//                                     /  \
//          20                        10   40                 
//       /     \                    /   \
/n->  (8)    40                 (8)    11  
//    /   \                      /  \        
//   5    10 <-nnew =>          5   9                            
//  / \  / \                    / \         
// 2   6 9  11                 2   6          
//
template <class K, class T>
void RBTree<K,T>::rotateLeft(Node *n) {
  ALGO_ASSERT(n->rightChild != nullptr, "Cannot rotateRight leaf nodes.");
  std::unique_ptr<Node> nnew = std::move(n->rightChild); //get the ownership
  n->rightChild = std::move(nnew->leftChild);
  if(n->rightChild != nullptr) {
    n->rightChild->parent = n;
  }

  nnew->parent = n->parent;
  n->parent = nnew.get();
  if(root.get() == n) {
    nnew->leftChild = std::move(root);
    root = std::move(nnew);
  } 
  else {
    //n is a left node of its parent (at this point parents are already switched)
    if(nnew->parent->leftChild.get() == n) {
        nnew->leftChild = std::move(nnew->parent->leftChild);
        nnew->parent->leftChild = std::move(nnew);
    }
    else { //n is a right node of its parent
      nnew->leftChild = std::move(nnew->parent->rightChild);
      nnew->parent->rightChild = std::move(nnew);
    }
  }

}


//            20
//           /  \                             
//    n->   10   40        20                
//         /   \         /   \                               
//        /    11      (8)     40       
// nnew (8)           /   \                       
//     /  \           5    10                                         
//     5   9         / \  / \                     
//    / \           2   6 9  11                     
//   2   6      
template <class K, class T>
void RBTree<K,T>::rotateRight(Node *n) {
  ALGO_ASSERT(n->leftChild != nullptr, "Cannot rotateLeft leaf nodes.");
  std::unique_ptr<Node> nnew = std::move(n->leftChild);
  n->leftChild = std::move(nnew->rightChild);
  if(n->leftChild != nullptr) {
    n->leftChild->parent = n;
  }
  
  nnew->parent = n->parent;
  n->parent = nnew.get();
  if(root.get() == n) {
    nnew->leftChild = std::move(root);
    root = std::move(nnew);
  }
  else {
    if(nnew->parent->leftChild.get() == n) {//n is a left node of its parent
        nnew->rightChild = std::move(nnew->parent->leftChild);
        nnew->parent->leftChild = std::move(nnew);
    }
    else { //n is a right node of its parent
      nnew->rightChild = std::move(nnew->parent->rightChild);
      nnew->parent->rightChild = std::move(nnew);
    }
  }

}

template <class K, class T>
void RBTree<K,T>::insertData(const K& k, const T& t) {
  
  Node *n = insertNode(k, t);

  verifyRepairTree(n);

}

template <class K, class T>
typename RBTree<K,T>::Node* 
RBTree<K,T>::insertNode(const K& k, const T& t) {
  
  if(root.get() == nullptr) {
    root = std::make_unique<Node>();
    root->key = k;
    root->value = t;
    ++_size;
    mostLeftNode = root.get();
    return root.get();
  }
  
  Node *n = root.get();
  while(n!=nullptr) { //
    if(k < n->key) {
      if(n->leftChild.get() == nullptr) {
        _size++;
        Node *nn = n->createNode(k, t, true);
        if(nn == mostLeftNode->leftChild.get()) {
          mostLeftNode = nn;
        }
        return nn;
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
  bool done = false;
  //user stack  
  Stack<Node *> s;
  s.reserve(size());
  
  Node *n = root.get();
  
  if(n == nullptr) { return; }

  while (!done) {
    if(n!=nullptr) {
      s.push(n);
      n = n->leftChild.get();
    }
    else {
      if(!s.isEmpty()) {
        n = s.pop();
        std::cout << n->value.toString() << std::endl;
        n = n->rightChild.get();
      }
      else { done = true; }
    }
  }
}

template <class K, class T>
const typename RBTree<K,T>::Node *
RBTree<K,T>::Node::previousNode() const {
  
  const Node *n = this;
  if(n->leftChild.get()) {
    n = n->leftChild.get();
    while(n->rightChild.get()) {
      n = n->rightChild.get();
    }
  }
  else {
    const Node* y = n->parent;
    while(y && n == y->leftChild.get()) {
      n = y;
      y = n->parent;
    }
    n = y;
  }
  return n;
}

template <class K, class T>
const typename RBTree<K,T>::Node *
RBTree<K,T>::Node::nextNode() const {
  
  const Node *n = this;
  if(n->rightChild.get()) {
    n = n->rightChild.get();
    while(n->leftChild.get()) {
      n = n->leftChild.get();
    }
  }
  else {
    const Node* y = n->parent;
    while(y && n == y->rightChild.get()) {
      n = y;
      y = n->parent;
    }
    n = y;
  }
  return n;
}


template <class K, class T>
const typename RBTree<K,T>::Node *
RBTree<K,T>::getRightMostNode() const {
  if(_size == 0) { return nullptr; }
 
  Node *n = root.get();
  while(n->rightChild.get()) {
    n = n->rightChild.get();
  }
  return n;
}


template <class K, class T>
void RBTree<K,T>::verifyRepairTree(Node *n) {
  
  if(n->parent == nullptr) { //n is root. root is always black.
    n->red = false; 
  } 
  else if(n->parent->red == false) { //n's parent is black
    return; 
  } 
  else if(n->uncle() && n->uncle()->red) { //n's parent and uncle are red
    n->parent->red = false;
    n->uncle()->red = false;
    n->parent->parent->red = true;
    verifyRepairTree(n->parent->parent); //verify if n's grandparent violates any property (root is black and a red node has 2 black children).
  } 
  else {
    //   g-> |B|
    //      /   \
    // p-> R     B
    //      \   / \
    //      (R)
    //       n
    // Rotate (R)->parent to the left, then |B| to the right.
  

    Node *g = n->parent->parent;
    Node *p = n->parent;
    
    if(g->leftChild && n == g->leftChild->rightChild.get()) {
      rotateLeft(p);    
      n->red = false; //two rotations. N will be at g's position after the 2 rotations (root always black)
    }
    //       |B| <-g
    //      /   \
    //     B     R <-p
    //    / \   /
    //        (R)
    //         n
    // Rotate (R)->parent to the right, then |B| to the left.
    else if(g->rightChild &&  n == g->rightChild->leftChild.get()) {
      rotateRight(p);    
      n->red = false; //two rotations. N will be at g's position after the 2 rotations (root always black)
    }
    else {
      n->parent->red = false; //only one rotation. N's parent will be at g's position after nxt rotation
    }

    if(n == n->parent->leftChild.get()) {
      rotateRight(g);
    }
    else {
      rotateLeft(g);
    }
    g->red = true;
  }

}

}

#endif
