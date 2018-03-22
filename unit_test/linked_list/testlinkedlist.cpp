
#include <iostream>

#include "linked_list/linkedlist.h"
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
TEST(LinkedList, constructor) {
   LinkedList<DataTest> l;

   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
}

TEST(LinkedList, append) {
   LinkedList<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
    };
     
   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);

	l.append(data[0]);
	l.append(data[1]);
	l.append(data[2]);

	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.isEmpty(), false);
	
	int i=0;
	for(LinkedList<DataTest>::iterator it=l.begin(); it!=l.end(); ++it) {
		*it = data[i++]; 
	}

}

TEST(LinkedList, prepend) {
   LinkedList<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
    };
     
   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);

	l.prepend(data[2]);
	l.prepend(data[1]);
	l.prepend(data[0]);

	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.isEmpty(), false);
	
	int i=0;
	for(LinkedList<DataTest>::iterator it=l.begin(); it!=l.end(); ++it) {
		*it = data[i++]; 
	}

}

