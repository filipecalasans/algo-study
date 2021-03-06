
#include <iostream>
#include "array/dataarray.h"
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

   b.copyFrom(a);

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
   b.copyFrom(a);
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
   b.copyFrom(a);

   for(int i=0; i<b.size(); i++) {
      EXPECT_EQ(a[i], b[i]);
   }
}

// Tests the incriesing operation.
TEST(DataArray, IncrieseSizeX10) {
   int array_size = 100;
   DataArray<int> a(array_size, 10);

   bool ret = a.resize(100);
   EXPECT_EQ(ret, true);
   EXPECT_EQ(a.size(), 100);
   
   //data reamins the same after increasing
   for(int i=0; i<10; i++) {
      EXPECT_EQ(a[i], 10);
   }
   //new data block is accessiable
   for(int i=0; i<a.size(); i++) {
      a[i] = i+100;
      EXPECT_EQ(a[i], i+100);
   }
}

// Tests the incriesing +2.
TEST(DataArray, IncrieseSizePlus2) {
   int array_size = 10;
   DataArray<int> a(array_size, 10);

   bool ret = a.resize(12);
   EXPECT_EQ(ret, true);
   EXPECT_EQ(a.size(), 12);
   EXPECT_EQ(a.allocatedSize(), 256);
   
   //data reamins the same after increasing
   for(int i=0; i<10; i++) {
      EXPECT_EQ(a[i], 10);
   }
   //new data block is accessiable
   for(int i=0; i<a.size(); i++) {
      a[i] = i+100;
      EXPECT_EQ(a[i], i+100);
   }
}

// Tests decrease / 10.
TEST(DataArray, DecreaseBy10Times) {
   int array_size = 1000;
   DataArray<int> a(array_size, 10);

   EXPECT_EQ(a.size(), array_size);
   bool ret = a.resize(10);
   EXPECT_EQ(ret, true);
   EXPECT_EQ(a.size(), 10);
   EXPECT_EQ(a.allocatedSize(), 20); 

   //data reamins the same after increasing
   for(int i=0; i<10; i++) {
      EXPECT_EQ(a[i], 10);
   }
   //new data block is accessiable
   for(int i=0; i<a.size(); i++) {
      a[i] = i+100;
      EXPECT_EQ(a[i], i+100);
   }
}

// Tests decrease -5.
TEST(DataArray, DecreaseByMinus5) {
   int array_size = 100;
   DataArray<int> a(array_size, 10);

   EXPECT_EQ(a.size(), array_size);
   bool ret = a.resize(array_size-5);
   EXPECT_EQ(ret, true);
   EXPECT_EQ(a.size(), array_size-5);
   EXPECT_EQ(a.allocatedSize(), a.size()*2);

   //data reamins the same after increasing
   for(int i=0; i<array_size-5; i++) {
      EXPECT_EQ(a[i], 10);
   }
   //new data block is accessiable
   for(int i=0; i<a.size(); i++) {
      a[i] = i+100;
      EXPECT_EQ(a[i], i+100);
   }
}

//Test Iterator
TEST(DataArray, iterator) {

   int array_size = 100;
   DataArray<int> a(array_size, 10);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }

   int j=0;
   for(Algos::DataArray<int>::iterator it = a.begin(); 
      it != a.end(); it++) {
         EXPECT_EQ(a[j++], *it);
      }       
}
   //Test Iterator
TEST(DataArray, const_iterator) {

   int array_size = 100;
   DataArray<int> a(array_size, 10);

   for(int i=0; i<a.size(); i++) {
      a[i] = i;
   }

   int j=0;
   for(Algos::DataArray<int>::const_iterator it = a.cbegin(); 
      it != a.cend(); it++) {
         EXPECT_EQ(a[j++], *it);
      }     
}
   


