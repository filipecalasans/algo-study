
#include <iostream>
#include <string>
#include "map/rbtree.h"
#include "map/map.h"
#include "gtest/gtest.h"

#include <string>

using namespace Algos;

struct DataTest {
   int integer;
   bool boolean;
   std::string txt;
  
   //DataTest() {}

   //DataTest(const DataTest& other) {
   // *this = other;
   //}

   DataTest& operator=(const DataTest& other) {
      integer = other.integer;
      boolean = other.boolean;
      txt = other.txt;
      return (*this);
   }

   bool operator==(const DataTest& other) const {
      return (
         integer == other.integer &&
         boolean == other.boolean &&
         txt == other.txt
      );
   }

   std::string toString() const {
      return std::to_string(integer);
   }
};

#define TEST_SIZE 10

void initDataTest(DataTest *t, int n) {
  for(int i=0; i<n; i++) {
    t[i].integer = i;
    t[i].boolean = (i%2 == 0);
    t[i].txt = "abc";
  }
}

// Tests the default c'tor.
TEST(Map, constructor) {
   Map<int,DataTest> l;

   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
}

TEST(RBTree, constructor) {
   RBTree<int,DataTest> l;

   EXPECT_EQ(l.size(), 0);
}


TEST(RBTree, insert) {
   RBTree<int,DataTest> l;
    
   EXPECT_EQ(l.size(), 0);
   
   DataTest data[2] = {
        { 10, true, "abc" },
        { 30, false,"cca" },
      };
   
   l.insertData(data[0].integer, data[0]);
   
   EXPECT_EQ(l.size(), 1);
  
   l.insertData(data[1].integer, data[1]);
  
   EXPECT_EQ(l.size(), 2);

}

TEST(RBTree, insert_random) {
   RBTree<int,DataTest> l;
   const int size = 9;
    
   EXPECT_EQ(l.size(), 0);

   DataTest data[size] = {
        { 10, true, "abc" },
        { 0, true, "abc" },
        { 9, true, "abc" },
        { 3, true, "abc" },
        { 1, true, "abc" },
        { 23, true, "abc" },
        { 27, true, "abc" },
        { 13, true, "abc" },
        { 6, false,"cca" },
      };
    
    for(int i=0; i<size; i++) {
      l.insertData(data[i].integer, data[i]);
    }

   EXPECT_EQ(l.size(), 9);
   EXPECT_EQ(l.mostLeftNode->value, data[1]);
}

TEST(RBTree, next_node) {
   RBTree<int,DataTest> l;
   const int size = 9;
    
   EXPECT_EQ(l.size(), 0);

   DataTest data[size] = {
        { 10, true, "abc" },
        { 0, true, "abc" },
        { 9, true, "abc" },
        { 3, true, "abc" },
        { 1, true, "abc" },
        { 23, true, "abc" },
        { 27, true, "abc" },
        { 13, true, "abc" },
        { 6, false,"cca" },
      };
    
  int seq[size] = {0, 1, 3, 6, 9, 10, 13, 23, 27};

  for(int i=0; i<size; i++) {
    l.insertData(data[i].integer, data[i]);
  }

  EXPECT_EQ(l.size(), 9);
  
  const RBTree<int, DataTest>::Node *n = l.mostLeftNode;
  
  int i=0;
  while(n!=nullptr) {
    EXPECT_EQ(seq[i++], n->value.integer);
    n = n->nextNode();
    if(i>=9) { break; }
  }
  
  i = 9;
  n = l.getRightMostNode();
  while(n!=nullptr) {
    EXPECT_EQ(seq[--i], n->value.integer);
    n = n->previousNode();
    if(i<0) { break; }
  }

}
