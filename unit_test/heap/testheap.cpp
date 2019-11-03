
#include <iostream>

#include "heap/heap.h"
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
};

#define TEST_SIZE 100

void initDataTest(DataTest *t, int n) {
  for(int i=0; i<n; i++) {
    t[i].integer = i;
    t[i].boolean = (i%2 == 0);
    t[i].txt = "abc";
  }
}

// Tests the default c'tor.
TEST(Heap, constructor) {
   Heap<int,DataTest> l;

   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
}

TEST(Heap, insert_contains) {
  
  Heap<int,DataTest> l;
  DataTest d[8] = {
    {10, true, "abc"},
    {6, true, "abc"},
    {0, true, "abc"},
    {2, true, "abc"},
    {10, true, "abc"},
    {3, true, "abc"},
    {7, true, "abc"},
    {9, true, "abc"},
  };
  
  int heap[8] = {0,2,3,9,10,6,7,10};
  
  EXPECT_EQ(l.contains(10), false);
  EXPECT_EQ(l.contains(7), false);
  EXPECT_EQ(l.contains(100), false);
  EXPECT_EQ(l.contains(-1), false);


  for(int i=0; i<8; i++) {
    l.insert(d[i].integer, d[i]);
  }
  
  EXPECT_EQ(l.contains(10), true);
  EXPECT_EQ(l.contains(7), true);
  EXPECT_EQ(l.contains(100), false);
  EXPECT_EQ(l.contains(-1), false);
  
  int idx = 0;
  for(const auto& elem : l) {
    EXPECT_EQ(elem.second.integer, heap[idx++]);
  }
}


TEST(Heap, pull_peek) {
  
  Heap<int,DataTest> l;
  DataTest d[8] = {
    {10, true, "abc"},
    {6, true, "abc"},
    {0, true, "abc"},
    {2, true, "abc"},
    {10, true, "abc"},
    {3, true, "abc"},
    {7, true, "abc"},
    {9, true, "abc"},
  };
  
  int heap[8] = {0,2,3,9,10,6,7,10};
  
  for(int i=0; i<8; i++) {
    l.insert(d[i].integer, d[i]);
  }
  
  for(int i=0; i<8; i++) {
    EXPECT_EQ(l[i].integer, heap[i]);
  }
  int lastPeek = -1;
  while(l.size()) {
    int top = l.peek().integer;
    EXPECT_LE(lastPeek, top);
    lastPeek = top;
  }

}



TEST(Heap, swap) {
  
  Heap<int,DataTest> l1, l2; 
  DataTest d1[TEST_SIZE];
  DataTest d2[TEST_SIZE/2];
  
  initDataTest(d1, TEST_SIZE);
  initDataTest(d2, TEST_SIZE/2);
  
  for(int i=0; i<TEST_SIZE; i++) {
    l1.insert(d1[i].integer, d1[i]);
  }
  
  for(int i=0; i<TEST_SIZE/2; i++) {
    l2.insert(d2[i].integer, d2[i]);
  }

  l1.swap(l2);
  
  for(int i=0; i<TEST_SIZE/2; i++) {
    EXPECT_EQ(d2[i], l1[i]);
  }
  
  for(int i=0; i<TEST_SIZE; i++) {
    EXPECT_EQ(d1[i], l2[i]);
  }

}
