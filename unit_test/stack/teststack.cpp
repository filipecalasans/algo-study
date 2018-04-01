
#include <iostream>

#include "stack/stack.h"
#include "gtest/gtest.h"

#include <string>

using namespace Algos;

struct DataTest {
   int integer;
   bool boolean;
   std::string txt;
  
   DataTest() {}

   DataTest(const DataTest& other) {
    *this = other;
   }

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
TEST(Stack, constructor) {
   Stack<DataTest> l;

   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
}

TEST(Stack, push) {
  
  Stack<DataTest> l;
  DataTest d[TEST_SIZE];
  
  initDataTest(d, TEST_SIZE);
  
  for(int i=0; i<TEST_SIZE; i++) {
    l.push(d[i]);
  }
    
  EXPECT_EQ(TEST_SIZE, l.size());
  EXPECT_EQ(l.isEmpty(), false);

  int count = 0;
  for(const auto &i : l) {
    EXPECT_EQ(i == d[count++], true);
  }

}


TEST(Stack, pop_top) {
  
  Stack<DataTest> l;
  DataTest d[TEST_SIZE];
  
  initDataTest(d, TEST_SIZE);
  
  for(int i=0; i<TEST_SIZE; i++) {
    l.push(d[i]);
  }
    
  EXPECT_EQ(TEST_SIZE, l.size());
  EXPECT_EQ(l.isEmpty(), false);

  int count = l.size();
  int threshold = l.size()/2;
  int idx = count-1;

  while((count--)>threshold) {
    EXPECT_EQ(d[idx] == l.top(), true);
    DataTest t = l.pop();
    EXPECT_EQ(d[idx--] == t, true); 
  }

  idx = 0;
  for(const auto &i : l) {
    EXPECT_EQ(i == d[idx], true);
    idx++;
  }

}



TEST(Stack, swap) {
  
  Stack<DataTest> l1, l2; 
  DataTest d1[TEST_SIZE];
  DataTest d2[TEST_SIZE];
  
  initDataTest(d1, TEST_SIZE);
  initDataTest(d2, TEST_SIZE/2);
  
  for(int i=0; i<TEST_SIZE; i++) {
    l1.push(d1[i]);
  }
    
  for(int i=0; i<TEST_SIZE; i++) {
    l2.push(d2[i]);
  }

  EXPECT_EQ(TEST_SIZE, l1.size());
  EXPECT_EQ(TEST_SIZE, l2.size());
  EXPECT_EQ(l1.isEmpty(), false);
  EXPECT_EQ(l2.isEmpty(), false);
  
  l1.swap(l2);
  
  int idx=0;
  for(const auto& i : l1)
      EXPECT_EQ(i == d2[idx++], true);

  idx=0;
  for(const auto& i : l2)
      EXPECT_EQ(i == d1[idx++], true);

}
