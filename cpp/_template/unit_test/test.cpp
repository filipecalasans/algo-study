
#include <iostream>
#include "array.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(Array, DefaultConstructor) {
   const Array a;

   EXPECT_EQ(0u, 0);
}

// Tests the default c'tor.
TEST(Array, Contructor2) {
   const Array a;

   EXPECT_EQ(0u, 1);
}

