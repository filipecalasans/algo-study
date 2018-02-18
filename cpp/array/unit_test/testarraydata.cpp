
#include <iostream>
#include "arraydata.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(DataArray, ConstructorDefault) {
   int array_size = 10;
   DataArray<int> a(array_size);

   EXPECT_EQ(array_size, a.size());
}

// Tests the default c'tor and const []
TEST(DataArray, ContructorInitializedData) {
   int array_size = 10;
   DataArray<int> a(array_size, 20);

   EXPECT_EQ(array_size, a.size());

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, 20);
   }
   
}

// Tests the operator [], const and not-const.
TEST(DataArray, OperatorIndex) {
   int array_size = 10;
   DataArray<int> a(array_size);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, i);
   }
   
}

// Tests the operator [], 2 equal size arrays.
TEST(DataArray, OperatorEqual) {
   int array_size = 10;
   DataArray<int> a(array_size);
   DataArray<int> b(array_size);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }

   b = a;

   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(tmp, b[i]);
      EXPECT_EQ(a[i], b[i]);
   }
}

// Tests the operator [], 2 equal size arrays.
TEST(DataArray, OperatorEqAssignedToGreaterArray) {
   int array_size = 10;
   DataArray<int> a(array_size);
   DataArray<int> b(20);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }
   b = a;
   for(int i=0; i<a.size(); i++) {
      EXPECT_EQ(a[i], b[i]);
   }
}

// Tests the operator [], 2 equal size arrays.
TEST(DataArray, OperatorEqAssignedToSmallerArray) {
   int array_size = 10;
   DataArray<int> a(array_size);
   DataArray<int> b(5);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }
   b = a; 
   for(int i=0; i<b.size(); i++) {
      EXPECT_EQ(a[i], b[i]);
   }
}



