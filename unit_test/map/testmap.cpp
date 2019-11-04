
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

std::ostream& operator<< (std::ostream& os, const DataTest& d)
{
  os << "{" << d.integer << "," << d.boolean << "," << d.txt << "}";
  return os;
}

#define TEST_SIZE 10

void initDataTest(DataTest *t, int n) {
  for(int i=0; i<n; i++)
  {
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
      std::cout << "=============================" << std::endl;
      l.root->print();
      std::cout << "=============================" << std::endl;
    }

   EXPECT_EQ(l.size(), 9);
   //EXPECT_EQ(l.mostLeftNode->key_value.second, data[1]);
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
  
  RBTree<int, DataTest>::Node *n = l.mostLeftNode;
  
  int i=0;
  while(n!=nullptr) {
    EXPECT_EQ(seq[i++], n->key_value.second.integer);
    n = n->nextNode();
    if(i>=9) { break; }
  }
  
  i = 9;
  n = l.getRightMostNode();
  while(n!=nullptr) {
    EXPECT_EQ(seq[--i], n->key_value.second.integer);
    n = n->previousNode();
    if(i<0) { break; }
  }

}

TEST(RBTree, remove_random)
{
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
    
  for(int i=0; i<size; i++)
  {
    l.insertData(data[i].integer, data[i]);
  }
  
  std::cout << "============Before deleting=============" << std::endl;
  l.root->print();
  std::cout << "=============================" << std::endl;

  l.deleteNode(23);
  l.root->print();
  std::cout << "=============================" << std::endl;

  l.deleteNode(6);
  l.root->print();
  std::cout << "=============================" << std::endl;

  l.deleteNode(9);
  l.root->print();
  std::cout << "=============================" << std::endl;

  EXPECT_EQ(l.mostLeftNode->key_value.second, data[1]);
  EXPECT_EQ(l.size(), 6);
}

TEST(Map, iterator)
{
    Map<int, DataTest> l;
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

    for(int i=0; i<size; i++)
    {
      l.insert(data[i].integer, data[i]);
    }

    auto it = l.begin();
    int prev = it->first;
    it++;

    while(it != l.end())
    {
       EXPECT_LE(prev, it->first);
       prev = it->first;
       it++;
    }
}

TEST(Map, map_methods)
{
    Map<int, DataTest> l;
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

    for(int i=0; i<size; i++)
    {
      l.insert(data[i].integer, data[i]);
    }

    EXPECT_EQ(l.contains(10), true);
    EXPECT_EQ(l.contains(3), true);
    EXPECT_EQ(l.contains(27), true);
    EXPECT_EQ(l.contains(56), false);
    EXPECT_EQ(l.size(), size);
    EXPECT_EQ(l.getValue(3).integer, 3);
    EXPECT_EQ(l.getValue(10).integer, 10);
    EXPECT_EQ(l.getValue(27).integer, 27);

}
