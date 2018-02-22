
#include <iostream>

#include "vector/vector.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(Vector, ContructorNotInitializedData) {
   int array_size = 10;
   Vector<int> a(array_size);

   EXPECT_EQ(0, a.size());
}

// Tests the default c'tor and const []
TEST(Vector, ContructorInitializedData) {
   int array_size = 10;
   //Vector<int> a(array_size, 20);
}

//Tests the c'tor (Vector(Vector&a)
TEST(Vector, ContructorPassingOtherVector) {
   /*int array_size = 10;
   Vector<int> a(array_size, 20);
   Vector<int> b(a);

   EXPECT_EQ(array_size, a.size());
   EXPECT_EQ(array_size, b.size());
   EXPECT_EQ(b.dataRefCount(), 2);
   EXPECT_EQ(a.dataRefCount(), 2);
  
   for(int i=0; i<a.size(); i++) {
      const int tmp = a[i]; 
      EXPECT_EQ(a[i], b[i]);
      EXPECT_EQ(20, b[i]);
   }*/  
}


TEST(Vector, First) {
   int array_size = 10;
//   Vector<int> a(array_size, 0);
  
//   a[0] = 55;
//   EXPECT_EQ(55, a.first());

}

TEST(Vector, Last) {
   int array_size = 10;
  // Vector<int> a(array_size, 0);
  
  // a[array_size-1] = 55;
  //  EXPECT_EQ(55, a.last());

}

TEST(Vector, Empty) {
   //Vector<int> a;
  
   //EXPECT_EQ(0, a.size());
   //EXPECT_EQ(true, a.empty());
  
}
