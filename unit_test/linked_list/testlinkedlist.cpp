
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

#define VERIFY_ON_FORWARD_REVERSE_ORDER(l, d, n) \
{ \
	int i=0; \
	for(LinkedList<DataTest>::iterator it=l.begin(); it!=l.end(); ++it) \
		EXPECT_EQ(*it == d[i++], true);\
	int j=n; \
	for(LinkedList<DataTest>::iterator it=l.rend(); it!=l.rbegin(); --it)\
		EXPECT_EQ(*it == d[--j], true); \
} \
{ \
	int i=0; \
	for(LinkedList<DataTest>::const_iterator it=l.cbegin(); it!=l.cend(); ++it) \
		EXPECT_EQ(*it == d[i++], true);\
	int j=n; \
	for(LinkedList<DataTest>::const_iterator it=l.crend(); it!=l.crbegin(); --it)\
		EXPECT_EQ(*it == d[--j], true); \
} \

TEST(LinkedList, append) {
   LinkedList<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
    };
     
   EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.isEmpty(), true);
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data,3);

	l.append(data[0]);
	l.append(data[1]);
	l.append(data[2]);

	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.isEmpty(), false);
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data,3);

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
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data,3);

	l.prepend(data[2]);
	l.prepend(data[1]);
	l.prepend(data[0]);

	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.isEmpty(), false);
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data,3);

}

