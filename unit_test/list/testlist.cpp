
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

   bool operator==(const DataTest& other) const {
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

TEST(List, insertMiddle) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[0]);
   l.append(data[2]);

   EXPECT_EQ(l.size(), 2);
   EXPECT_EQ(l.isEmpty(), false);

   l.insert(data[1], 1);

   for(int i=0; i<3; i++) {
      DataTest t = l[i];
      EXPECT_EQ(data[i] == t, true);
   }
}


TEST(List, insertEnd) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[0]);
   l.append(data[1]);

   EXPECT_EQ(l.size(), 2);
   EXPECT_EQ(l.isEmpty(), false);

   l.insert(data[2], 2);

   for(int i=0; i<3; i++) {
      DataTest t = l[i];
      EXPECT_EQ(data[i] == t, true);
   }
}


TEST(List, insertBegin) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[1]);
   l.append(data[2]);

   EXPECT_EQ(l.size(), 2);
   EXPECT_EQ(l.isEmpty(), false);

   l.insert(data[0], 0);

   for(int i=0; i<3; i++) {
      DataTest t = l[i];
      EXPECT_EQ(data[i] == t, true);
   }
}

TEST(List, takeAt) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   for(int i=0; i<3; i++) l.append(data[i]);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   DataTest a = l.takeAt(1);

   EXPECT_EQ(a == data[1], true);
   EXPECT_EQ(l[0] == data[0], true);
   EXPECT_EQ(l[1] == data[2], true);
}

TEST(List, takeFirst) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   for(int i=0; i<3; i++) l.append(data[i]);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   DataTest a = l.takeFirst();

   EXPECT_EQ(a == data[0], true);
   EXPECT_EQ(l[0] == data[1], true);
   EXPECT_EQ(l[1] == data[2], true);
}

TEST(List, takeLast) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   for(int i=0; i<3; i++) l.append(data[i]);

   EXPECT_EQ(l.size(), 3);
   EXPECT_EQ(l.isEmpty(), false);

   DataTest a = l.takeLast();

   EXPECT_EQ(a == data[2], true);
   EXPECT_EQ(l[0] == data[0], true);
   EXPECT_EQ(l[1] == data[1], true);
}

TEST(List, removeOne) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[1]);

   for(int i=0; i<10; i++) l.append(data[0]);
   
   l.append(data[1]);

   for(int i=0; i<10; i++) l.append(data[2]);

   l.append(data[1]);

   EXPECT_EQ(l.size(), 23);
   EXPECT_EQ(l.isEmpty(), false);

   l.removeOne(data[1]);

   for(int i=0; i<10; i++) { 
      EXPECT_EQ(l[i] == data[0], true);
   }

   for(int i=11; i<21; i++) { 
      EXPECT_EQ(l[i] == data[2], true);
   }

   EXPECT_EQ(l[10] == data[1], true);
   EXPECT_EQ(l[l.size()-1] == data[1], true);
}

TEST(List, removeAll) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   l.append(data[1]);

   for(int i=0; i<10; i++) l.append(data[0]);

   l.append(data[1]);

   for(int i=0; i<10; i++) l.append(data[2]);

   l.append(data[1]);

   EXPECT_EQ(l.size(), 23);
   EXPECT_EQ(l.isEmpty(), false);

   l.removeAll(data[1]);

   for(int i=0; i<l.size(); i++) { 
      if(i<l.size()/2){
         EXPECT_EQ(l[i] == data[0], true);
      }
      else {
         EXPECT_EQ(l[i] == data[2], true);
      }
   }
}

TEST(List, apendList) {
   List<DataTest> l, l2;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   for(int i=0; i<3; i++) { 
      l.append(data[i]);
      l2.append(data[i]);
   }

   l.append(l2);

   for(int i=0; i<l.size(); i++) { 
      EXPECT_EQ(l[i] == data[i%3], true);
   }
}

TEST(List, iterator) {
   List<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
   };

   APPEND_ELEMENTS(l, data, 3);

   int i = 0;
   for(auto& elem : l) {
      EXPECT_EQ(elem == data[i++], true);
   }

   i=0;
   for(const auto& elem : l) {
      EXPECT_EQ(elem == data[i++], true);
   }

   for(auto& elem : l) {
      elem.integer++;
   }

   i=0;
   for(const auto& elem : l) {
      EXPECT_EQ(elem.integer, (data[i++].integer+1));
   }
}