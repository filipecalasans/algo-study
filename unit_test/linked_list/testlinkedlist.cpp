
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
		EXPECT_EQ(*it, d[i++]);\
	int j=n; \
	for(LinkedList<DataTest>::iterator it=l.rend(); it!=l.rbegin(); --it)\
		EXPECT_EQ(*it, d[--j]); \
} \
{ \
	int i=0; \
	for(LinkedList<DataTest>::const_iterator it=l.cbegin(); it!=l.cend(); ++it) \
		EXPECT_EQ(*it, d[i++]);\
	int j=n; \
	for(LinkedList<DataTest>::const_iterator it=l.crend(); it!=l.crbegin(); --it)\
		EXPECT_EQ(*it, d[--j]); \
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

TEST(LinkedList, insert) {
   LinkedList<DataTest> l;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
    };
     
   EXPECT_EQ(l.size(), 0);
   EXPECT_EQ(l.isEmpty(), true);
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data,3);

	l.append(data[2]);
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.isEmpty(), false);

	//Test iterator end, begin, rend, rbegin
	EXPECT_EQ(*(l.begin()), data[2]);
	EXPECT_EQ(*(--l.end()), data[2]); 
	EXPECT_EQ(*(++l.rbegin()), data[2]);
	EXPECT_EQ(*(l.rend()), data[2]); 

	LinkedList<DataTest>::iterator it = l.begin();
	it = l.insert(it, data[1]);
	EXPECT_EQ(*it, data[1]);
	EXPECT_EQ(l.size(), 2);
	EXPECT_EQ(l.isEmpty(), false);

	it = l.insert(++it, data[0]);
	EXPECT_EQ(*it, data[0]);
	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.isEmpty(), false);
	
	 DataTest data2[3] = { //data in the order inserted.
      {1, false, "cba"},
	   {0, true, "abc"},
		{2, true, "bca"},
	};
	
	VERIFY_ON_FORWARD_REVERSE_ORDER(l,data2,3);
}

TEST(LinkedList, operatorEqual) {
   LinkedList<DataTest> l1, l2;
   DataTest data[3] = {
      {0, true, "abc"},
      {1, false, "cba"},
      {2, true, "bca"},
	};
	
	for(int i=0; i<3; i++) {
		l1.append(data[i]);
	}

	l2 = l1;

	VERIFY_ON_FORWARD_REVERSE_ORDER(l1,data,3);
	VERIFY_ON_FORWARD_REVERSE_ORDER(l2,data,3);
}
