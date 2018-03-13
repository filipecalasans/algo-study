
#include <iostream>

#include "list/list.h"
#include "gtest/gtest.h"

#include <string>

using namespace Algos;

struct DataTest {
   int integer;
   bool boolean;
   std::string txt;
   DataTest& operator=(DataTest&& other) {
      integer = std::move(other.integer);
      boolean = std::move(other.boolean);
      txt = std::move(other.txt);
      return (*this);
   }
};

// Tests the default c'tor.
TEST(List, constructor) {
   List<DataTest> l;
   
   
}
