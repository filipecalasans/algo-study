
#include <iostream>

#include "list/list.h"
#include "gtest/gtest.h"

#include <string>

using namespace Algos;

struct DataTest {
   int integer;
   bool boolean;
   std::string txt;
   DataTest& operator=(const DataTest& other) {
      integer = other.integer;
      boolean = other.boolean;
      txt = other.txt;
      return (*this);
   }

   bool operator==(const DataTest& other) {
      return (
         integer == other.integer &&
         boolean == other.boolean &&
         txt == other.txt
      );
   }
};

// Tests the default c'tor.
TEST(List, constructor) {
   List<DataTest> l;

   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
}

TEST(List, appendAndAt) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[0]);
   l.append(data[1]);
   l.append(data[2]);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   for(int i=0; i<3; i++) {
      DataTest t = l[i];
      EXPECT_EQ(data[i] == t, true);
   }
}

#define APPEND_ELEMENTS(l, d, n) \
    for(int i=0; i<n; i++) l.append(d[i]);


TEST(List, removeFirst) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   APPEND_ELEMENTS(l, data, 3);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   l.removeAt(0);

   for(int i=0, k=0; i<3; i++) {
      if(i>0) {
         EXPECT_EQ(data[i] == l[k], true);
         k++;
      }
   }
}

TEST(List, removeLast) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   APPEND_ELEMENTS(l, data, 3);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   l.removeAt(2);

   for(int i=0, k=0; i<3; i++) {
      if(i<2) {
         EXPECT_EQ(data[i] == l[k], true);
         k++;
      }
   }
}

TEST(List, removeMiddle) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   APPEND_ELEMENTS(l, data, 3);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   l.removeAt(1);

   for(int i=0, k=0; i<3; i++) {
      if(i!=1) {
         EXPECT_EQ(data[i] == l[k], true);
         k++;
      }
   }
}

TEST(List, prepend) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   for(int i=1; i<3; i++) l.append(data[i]);

   EXPECT_EQ(l.size(), 2);
   EXPECT_EQ(l.isEmpty(), false);

   l.prepend(data[0]);

   for(int i=0; i<3; i++) {
      DataTest t = l[i];
      EXPECT_EQ(data[i] == t, true);
   }
}

TEST(List, replace) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   APPEND_ELEMENTS(l, data, 3);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   l.replace(data[0], 1);
   l.replace(data[0], 2);

   DataTest t = data[0];
   for(int i=0; i<3; i++) {
      EXPECT_EQ(l[i] == t, true);
   }
}