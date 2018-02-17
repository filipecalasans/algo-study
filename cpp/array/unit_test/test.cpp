
#include <iostream>
#include "array.h"
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

// Tests the operator [], const and not-const.
TEST(Array, OperatorIndex) {
   int array_size = 10;
   Array<int> a(array_size);

   for(int i=0; i<a.size(); i++) {
      // a[i] = i;
   }

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, i);
   }
   
}

