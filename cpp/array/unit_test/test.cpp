
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

// Tests the default c'tor.
TEST(Array, ContructorInitializedData) {
   int array_size = 10;
   Array<int> a(array_size, 20);

   EXPECT_EQ(array_size, a.size());

   for(int i=0; i<a.size(); i++) {
      EXPECT_EQ(a[i], 20);
   }
   
}

