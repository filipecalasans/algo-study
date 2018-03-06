
#include <iostream>

#include "iterator/iterator.h"
#include "gtest/gtest.h"

#include <memory>

using namespace Algos;

TEST(iterator, smartPointerSimpleType) {
   std::shared_ptr<int> var = std::make_shared<int>();
   *var = 10;

   EXPECT_EQ(10, *var);

   Algos::iterator<int> it_a(var.get());
   Algos::iterator<int> it_a_aux(it_a);

   EXPECT_EQ(it_a == var.get(), true);
   EXPECT_EQ(it_a != var.get(), false);

   std::shared_ptr<int> b_ptr = std::make_shared<int>();
   Algos::iterator<int> it_b = b_ptr.get();

   EXPECT_EQ(it_a == it_b, false);
   EXPECT_EQ(it_a != it_b, true);
}

TEST(iterator, smartPointerSimpleTypeArray) {

   int array[20];

   for(int i=0; i<20; i++) {
      array[i] = i;
   }
   
   Algos::iterator<int> it(array);
   
   // Test postfix ++ operator
   for(int i=0; i<10; i++) { 
      EXPECT_EQ(*it, i);
      EXPECT_EQ(*(it++), array[i]);
   }

   // Test prefix ++ operator
   Algos::iterator<int> it2(array);
   EXPECT_EQ((++it2).operator->(), &array[1]);

}

TEST(iterator, smartPointerSimpleTypeArrayConst) {

   int array[20];

   for(int i=0; i<20; i++) {
      array[i] = i;
   }
   
   Algos::const_iterator<int> it(array);
   
   // Test postfix ++ operator
   for(int i=0; i<10; i++) { 
      EXPECT_EQ(*it, i);
      EXPECT_EQ(*(it++), array[i]);
   }

   // Test prefix ++ operator
   Algos::const_iterator<int> it2(array);
   EXPECT_EQ((++it2).operator->(), &array[1]);
   
}