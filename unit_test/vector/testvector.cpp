
#include <iostream>

#include "vector/vector.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(Vector, ContructorNotInitializedData) {
   int array_size = 300;
   Vector<int> a(array_size);

   EXPECT_EQ(array_size, a.size());
}

// Tests the default c'tor and const []
TEST(Vector, ContructorInitializedData) {
   int array_size = 100;
   Vector<int> a(array_size, 20);

   for(int i=0; i<a.size(); i++) {
    EXPECT_EQ(a[i], 20);
   }
}

// Tests the default c'tor and const []
TEST(Vector, AppendOnInitializedArray) {
   int array_size = 10;
   int insert_size = 400;
   Vector<int> a(array_size, 20);
  
   for(int i=0; i<insert_size; i++) {
      a.append(i+array_size);
   }
  
   EXPECT_EQ(a.size(), insert_size+array_size);

   for(int i=0; i<array_size; i++) {
      EXPECT_EQ(a[i], 20);
   }
   for(int i=array_size; i<a.size(); i++) {
      EXPECT_EQ(a[i], i);
   }
}

// Apend values on a empty array.
TEST(Vector, AppendOnEmptyArray) {
   int array_size = 10;
   int insert_size = 400;
   Vector<int> a;
  
   for(int i=0; i<insert_size; i++) {
      a.append(i);
   }
  
   EXPECT_EQ(a.size(), insert_size);

   for(int i=0; i<a.size(); i++) {
      EXPECT_EQ(a[i], i);
   }
}

//
TEST(Vector, AssignmenAfterInsertion) {
   int array_size = 10;
   int insert_size = 400;
   Vector<int> a;
  
   for(int i=0; i<insert_size; i++) {
      a.append(i);
   }
  
   EXPECT_EQ(a.size(), insert_size);

   for(int i=0; i<a.size(); i++) {
      EXPECT_EQ(a[i], i);
   }

   Vector<int> b;

   b = a;
  
  EXPECT_EQ(b.size(), a.size());

   for(int i=0; i<a.size(); i++) {
      EXPECT_EQ(a[i], b[i]);
   }


}


TEST(Vector, InsertOnAInitializedVector) {
   int array_size = 300;
   Vector<int> a(array_size, 0);
  
   a.insert(0, 100);
   a.insert(10, 200);
   a.insert(250, 300);
   a.insert(299, 400);
  
  
   EXPECT_EQ(a[0], 100);
   EXPECT_EQ(a[10], 200);
   EXPECT_EQ(a[250], 300);
   EXPECT_EQ(a[299], 400);
}

TEST(Vector, InsertOnAIncreasedVector) {
   int array_size = 300;
   Vector<int> a(array_size);

   a.insert(0, 100);
   a.insert(10, 200);
   a.insert(250, 300);
   a.insert(299, 400);
   a.insert(300, 500); //Cant break. 
   
   EXPECT_EQ(a[0], 100);
   EXPECT_EQ(a[10], 200);
   EXPECT_EQ(a[250], 300);
   EXPECT_EQ(a[299], 400);
   
   { 
      Vector<int>b(a);
   
      EXPECT_EQ(b.dataRefCount(), 2);
      EXPECT_EQ(a.dataRefCount(), 2);
      
      EXPECT_EQ(a[0], 100);
      EXPECT_EQ(a[10], 200);
      EXPECT_EQ(a[250], 300);
      EXPECT_EQ(a[299], 400);

      EXPECT_EQ(b[0], 100);
      EXPECT_EQ(b[10], 200);
      EXPECT_EQ(b[250], 300);
      EXPECT_EQ(b[299], 400);
   }

   EXPECT_EQ(a.dataRefCount(), 1);
   EXPECT_EQ(a[0], 100);
   EXPECT_EQ(a[10], 200);
   EXPECT_EQ(a[250], 300);
   EXPECT_EQ(a[299], 400);
}

TEST(Vector, ResizeVectorSize) {
   int array_size = 300;
   Vector<int> a;
   
   EXPECT_EQ(a.resize(20), true);
  
   a.insert(0, 10);
   a.insert(10, 20);
   
   EXPECT_EQ(a[0], 10);
   EXPECT_EQ(a[10], 20);
   
   EXPECT_EQ(a.resize(array_size), true);

   a.insert(0, 100);
   a.insert(10, 200);
   a.insert(250, 300);
   a.insert(299, 400);
   a.insert(300, 500); //Cant break. 
   
   EXPECT_EQ(a[0], 100);
   EXPECT_EQ(a[10], 200);
   EXPECT_EQ(a[250], 300);
   EXPECT_EQ(a[299], 400);

   EXPECT_EQ(a.size(), array_size);
  
}

TEST(Vector, ClearVector) {
   int array_size = 256;
   Vector<int> a(array_size, 0);
    

   EXPECT_EQ(array_size, a.size());
   a.clear();
   EXPECT_EQ(0, a.size());
   EXPECT_EQ(true, a.empty());

}

TEST(Vector, Empty) {
   Vector<int> a;
  
   EXPECT_EQ(0, a.size());
   EXPECT_EQ(true, a.empty());
  
}
