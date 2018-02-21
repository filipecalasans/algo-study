
#include <iostream>

#include "array/array.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(Array, ContructorNotInitializedData) {
   int array_size = 10;
   Array<int> a(array_size);

   EXPECT_EQ(array_size, a.size());
}

// Tests the default c'tor and const []
TEST(Array, ContructorInitializedData) {
   int array_size = 10;
   Array<int> a(array_size, 20);

   EXPECT_EQ(array_size, a.size());

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, 20);
   }   
}

//Tests the c'tor (Array(Array&a)
TEST(Array, ContructorPassingOtherArray) {
   int array_size = 10;
   Array<int> a(array_size, 20);
   Array<int> b(a);

   EXPECT_EQ(array_size, a.size());
   EXPECT_EQ(array_size, b.size());
   EXPECT_EQ(b.dataRefCount(), 2);
   EXPECT_EQ(a.dataRefCount(), 2);
  
   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(a[i], b[i]);
      EXPECT_EQ(20, b[i]);
   }   
}

// Tests the operator [], const and not-const.
TEST(Array, OperatorIndex) {
   int array_size = 10;
   Array<int> a(array_size);
  
   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, i);
   }
}


TEST(Array, First) {
   int array_size = 10;
   Array<int> a(array_size, 0);
  
   a[0] = 55;
   EXPECT_EQ(55, a.first());

}

TEST(Array, Last) {
   int array_size = 10;
   Array<int> a(array_size, 0);
  
   a[array_size-1] = 55;
   EXPECT_EQ(55, a.last());

}
