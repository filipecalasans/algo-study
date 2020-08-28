
#include <iostream>

#include "two_level_page/twolevelpage.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(TwoLevelPage, IdentityMap)
{
  TwoLevelPage directory;
  
  for(uint32_t i=0; i<=directory.capacity(); i+=4096) {
    directory.insert(i, i);
  }

  for(uint32_t i=0; i<=directory.capacity(); i+=4096) {
    uint32_t expected =  i;
    EXPECT_EQ(directory.get(i), expected);
  }
}


TEST(TwoLevelPage, MapMultiplePagesToSamePhsyicalAddress)
{  
  TwoLevelPage directory;
  
  directory.insert(0, 0x1000);
  directory.insert(0x4000, 0x1000);
  directory.insert(0x8000, 0x1000);
  directory.insert(0x9000, 0x1000);

  EXPECT_EQ(directory.get(0), 0x1000);
  EXPECT_EQ(directory.get(0x4000), 0x1000);
  EXPECT_EQ(directory.get(0x4001), 0x1001);
  EXPECT_EQ(directory.get(0x8000), 0x1000);
  EXPECT_EQ(directory.get(0x8010), 0x1010);
  EXPECT_EQ(directory.get(0x9000), 0x1000);
  EXPECT_EQ(directory.get(0x9100), 0x1100);
}


