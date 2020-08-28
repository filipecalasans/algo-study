#include "hash_map/hashmap.h"
#include "gtest/gtest.h"

using namespace Algos;

struct DataTest {
   int integer;
   bool boolean;
   std::string txt;
  
   //DataTest() {}

   //DataTest(const DataTest& other) {
   // *this = other;
   //}

   DataTest& operator=(const DataTest& other) {
      integer = other.integer;
      boolean = other.boolean;
      txt = other.txt;
      return (*this);
   }

   bool operator==(const DataTest& other) const {
      return (
         integer == other.integer &&
         boolean == other.boolean &&
         txt == other.txt
      );
   }
};

#define TEST_SIZE 100

void initDataTest(DataTest *t, int n) {
  for(int i=0; i<n; i++) {
    t[i].integer = i;
    t[i].boolean = (i%2 == 0);
    t[i].txt = "abc";
  }
}


TEST(Hash_table, init)
{

}
