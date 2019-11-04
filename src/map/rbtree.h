#ifndef ALGOS_RBTREE_HH
#define ALGOS_RBTREE_HH

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "global/assert.h"
#include "list/list.h"
#include "stack/stack.h"
#include "pair/pair.h"

/* 
 * Algos Implementation is implicit-sharing.
 *
 */
namespace Algos { 

template <class K, class T>
struct RBTree
{
  
  struct Node
  {
    bool red;
    //K key;
    //T value;
    Pair<K,T> key_value;
    
    Node *parent;
    std::unique_ptr<Node> leftChild, rightChild;  
    
    Node() : red(true), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {} 
    Node(const K& k, const T& t) : Node() { key_value = Pair<K,T>(k,t); }

    Node *grandparent()
    {
      if(parent == nullptr) { return nullptr; }
      return parent->parent;
    }

    Node *grandParent()
    {
      if(parent == nullptr) { return nullptr; }
      if(parent->parent == nullptr) { return nullptr; }
      return parent->parent;
    }

    Node *uncle()
    {
      Node *p = parent;
      Node *g = grandParent();
      if(g == nullptr) { return nullptr; }
      if(g->leftChild.get() == p) {
        return g->rightChild.get();
      }
      return g->leftChild.get();
    }
    
    Node* createNode(const K& k, const T& t, bool onLeftChild)
    {
      if(onLeftChild)
      {
        leftChild = std::make_unique<Node>(k, t);
        leftChild->parent = this;
        return leftChild.get();
      }
      else
      {
        rightChild = std::make_unique<Node>(k, t);
        rightChild->parent = this;
        return rightChild.get();
      }
    }

    Node *previousNode(); 
    Node *nextNode();

    inline bool isLeaf() { return leftChild == nullptr && rightChild == nullptr; } 
   
    void print(){ print("", true); }
    
    protected:

      //https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram
      void print(std::string prefix, bool isTail) {
        std::cout << prefix + (isTail ? "└── " : "├── ") << key_value.first << "[" << (red ? "R" : "B") << "]" << std::endl;
        if(leftChild) {
          leftChild->print(prefix + (isTail ? "    " : "|   "), false);
        }
        if(rightChild) {
          rightChild->print(prefix + (isTail ? "    " : "|   "), true);
        }  
      }
 };
  
  typedef typename RBTree<K,T>::Node Node;
  
  RBTree() : _size(0), root(nullptr), mostLeftNode(nullptr), mostRightNode(nullptr) { }
  size_t _size;
  std::unique_ptr<Node> root;
  Node *mostLeftNode;
  Node *mostRightNode;
  
  inline size_t size() { return _size; }
  inline bool isRed(Node *n) { return n == nullptr ? false : n->red;  }
  void rotateLeft(Node *n);
  void rotateRight(Node *n);
  
  void insertData(const K& k, const T& t);
  Node* insertNode(const K& k, const T& t);

  void insertData(K&& k, T&& t);
  Node* insertNode(K&& k, T&& t);
  
  Node *find(const K& k);

  void deleteNode(const K& k);
  void deleteNode(Node *n);

  Node* getRightMostNode();
  Node* getLeftMostNode();
  
  void verifyRepairTree(Node *n);

  void cleanup();
  
  void assert_inorder();

  void print_in_order() { print_in_order_rec(root.get()); }

  void print_in_order_rec(Node *n);

};

template <class K, class T>
void RBTree<K,T>::print_in_order_rec(Node *n) {

  if(n == nullptr) { return; }

  print_in_order_rec(n->leftChild.get());
  std::cout << n->key_value.second << ", ";
  print_in_order_rec(n->rightChild.get());
}
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
void RBTree<K,T>::rotateLeft(Node *n)
{
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
    nnew->rightChild = std::move(root);
    root = std::move(nnew); 
  }
  else {
    //else/if pair to change ownership
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
void RBTree<K,T>::insertData(K&& k, T&& t)
{
    Node* node = insertNode(k, t);
    verifyRepairTree(k, t);
}

template <class K, class T>
typename RBTree<K,T>::Node*
RBTree<K,T>::insertNode(K&& k, T&& t)
{
    if(root.get() == nullptr) {
      root = std::make_unique<Node>();
//      root->key = k;
//      root->value = t;
      root->key_value = Pair<K,T>(k, t);
      ++_size;
      mostLeftNode = root.get();
      return root.get();
    }

    Node *n = root.get();
    while(n!=nullptr) { //
      if(k < n->key_value.first/*n->key*/) {
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
void RBTree<K,T>::insertData(const K& k, const T& t) {
  
  Node *n = insertNode(k, t);
  verifyRepairTree(n);
}

template <class K, class T>
typename RBTree<K,T>::Node* 
RBTree<K,T>::insertNode(const K& k, const T& t)
{
    K newK = k;
    T newT = t;
    return insertNode(std::move(newK), std::move(newT));
}

template <class K, class T>
void RBTree<K,T>::assert_inorder()
{
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
        std::cout << n->key_value.scond.toString() << std::endl;
        n = n->rightChild.get();
      }
      else { done = true; }
    }
  }
}

template <class K, class T>
typename RBTree<K,T>::Node *
RBTree<K,T>::Node::previousNode()
{
  
  Node *n = this;
  if(n->leftChild.get()) {
    n = n->leftChild.get();
    while(n->rightChild.get()) {
      n = n->rightChild.get();
    }
  }
  else {
    Node* y = n->parent;
    while(y && n == y->leftChild.get()) {
      n = y;
      y = n->parent;
    }
    n = y;
  }
  return n;
}


template <class K, class T>
typename RBTree<K,T>::Node *
RBTree<K,T>::Node::nextNode()
{
  Node *n = this;
  if(n->rightChild.get()) {
    n = n->rightChild.get();
    while(n->leftChild.get()) {
      n = n->leftChild.get();
    }
  }
  else {
    Node* y = n->parent;
    while(y && n == y->rightChild.get()) {
      n = y;
      y = n->parent;
    }
    n = y;
  }
  return n;
}


template <class K, class T>
typename RBTree<K,T>::Node *
RBTree<K,T>::getRightMostNode()
{
  if(_size == 0) { return nullptr; }
 
  Node *n = root.get();
  while(n->rightChild) {
    n = n->rightChild.get();
  }
  return n;
}

template <class K, class T>
typename RBTree<K,T>::Node *
RBTree<K,T>::getLeftMostNode()
{
  if(_size == 0) { return nullptr; }
 
  Node *n = root.get();
  while(n->leftChild) {
    n = n->rightChild.get();
  }
  return n;
}

template <class K, class T>
void RBTree<K,T>::verifyRepairTree(Node *n) {
  
  if(n->parent == nullptr) { //n is root. root is always black.
    n->red = false; 
  } 
  else if(isRed(n->parent) == false) { //n's parent is black
    return; 
  } 
  else if(n->uncle() && isRed(n->uncle())) { //n's parent and uncle are red
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
    // n -> (R)
    //       
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
    //        (R) <- n
    //         
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

template <class K, class T>
typename RBTree<K,T>::Node* 
RBTree<K,T>::find(const K& k)
{
  Node *n = root.get();
  while(n != nullptr)
  {
    if(n->key_value.first /*n->key*/ == k) { return n; }
    if(n->key_value.first /*n->key*/ < k)
    {
      n = n->rightChild.get();
    }
    else {
      n = n->leftChild.get();
    }
  }
  return n;
}

template <class K, class T>
void RBTree<K,T>::deleteNode(const K& k){ 
  deleteNode(find(k));
}

template <class K, class T>
void RBTree<K,T>::deleteNode(Node *n)
{
  if(n == nullptr) { return; } 
  // update left most node if n is it.
  bool updateLeftMost = n->key_value.first/*n->key*/ == mostLeftNode->key_value.first;

  if(n->isLeaf()) { //properties persist
    if(root.get() == n) {
      root.reset();
    }
    else if(n->parent->rightChild.get() == n) {
      n->parent->rightChild.reset();
    }
    else {
      n->parent->leftChild.reset();
    }
    --_size;
  }
  else if(n->leftChild && n->rightChild) { //we have to verify if the properties persist.
    Node *successor = n->nextNode();
    n->key_value.first = successor->key_value.first;
    n->key_value.second = successor->key_value.second;
    deleteNode(successor);
  }
  else if(n->leftChild) { //we have to verify if the properties persist
    Node *newNode = n->leftChild.get();
    if(root.get() == n) {
      root = std::move(n->leftChild); 
    }
    else {
      Node *parent = n->parent;
      bool isRight = parent->rightChild.get() == n;
      n->leftChild->parent = parent;
      if(isRight) {
        parent->rightChild = std::move(n->leftChild); 
      }
      else {
        parent->leftChild = std::move(n->leftChild);
      }
    }
    --_size;
  }
  else if(n->rightChild){ //we have to verify if the properties persist
    Node *newNode = n->rightChild.get();
    if(root.get() == n) {
      root = std::move(n->rightChild); 
    }
    else {
      Node *parent = n->parent;
      bool isRight = parent->rightChild.get() == n;
      n->rightChild->parent = parent;
      if(isRight) {
        parent->rightChild = std::move(n->rightChild);
      }
      else {
        parent->leftChild = std::move(n->rightChild);
      } 
    }
    --_size;
  }

  if(updateLeftMost) {
    mostLeftNode = getLeftMostNode();    
  }
}

}

#endif
