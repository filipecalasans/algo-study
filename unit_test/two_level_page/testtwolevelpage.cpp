
#include <iostream>

#include "two_level_page/twolevelpage.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(TwoLevelPage, IdentityMap) {

  TwoLevelPage directory;
  
  for(uint32_t i=0; i<=directory.capacity(); i+=4096) {
    directory.insert(i, i);
  }

  for(uint32_t i=0; i<=directory.capacity(); i+=4096) {
    uint32_t expected =  i;
    EXPECT_EQ(directory.get(i), expected);
  }
}


