#include <iostream>
#include <string>
#include <unistd.h>

#define DEBUG_TXT

#include "global/assert.h"

#include "linked_list/linkedlist.h"

#define TEST_SIZE 5000
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

struct Data {
	DataTest data[TEST_SIZE];
	const int n = TEST_SIZE;

	static void initDataSample(Data &d) {
		for(int i=0; i<d.n; i++) {
			d.data[i].integer = i;
			d.data[i].boolean = (i%2 == 0);
			d.data[i].txt = "abc";
		}
	}
};

void appendElements(Algos::LinkedList<DataTest> &l, const Data& d){
	for(int i=0; i<d.n; i++) {
		l.append(d.data[i]);
	}
}

int main(int argv, char* argc[]) {

   Data d;	
	Data::initDataSample(d);

	{	
		Algos::LinkedList<DataTest> l1;
		{
			Algos::LinkedList<DataTest> l2;
			l1 = l2;
		}

		sleep(2);

		appendElements(l1, d);
		
	}











   return 0;
}