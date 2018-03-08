
#include <iostream>

#include "list/list.h"
#include "gtest/gtest.h"

using namespace Algos;

// Tests the default c'tor.
TEST(ListData, constructor) {
   ListData<int> data;
   int x = 10;
   EXPECT_EQ(data.d->begin, 0);
   EXPECT_EQ(data.d->end, 0);
   EXPECT_EQ(data.d->alloc, 1);
   data.d->array[0] = &x;
   EXPECT_EQ(*(data.d->array[0]), 10);
}

// Tests the default c'tor.
TEST(ListData, realloc) {
   ListData<int> data;
   int x = 10;
   
   data.realloc(100);

   EXPECT_EQ(data.d->alloc, 100);
   data.d->array[99] = &x;
   EXPECT_EQ(*(data.d->array[99]), 10);

   data.realloc(200);
   EXPECT_EQ(data.d->alloc, 200);
}

TEST(ListData, append) {
   ListData<int> data;
   int x = 10;
   // std::cout << data.d->begin << " " << data.d->end << std::endl;

   int **nxt = data.append();
   *nxt = &x;
   EXPECT_EQ(**(data.d->array+data.d->begin), 10);
   EXPECT_EQ(data.d->alloc, 1);
   // std::cout << data.d->begin << " " << data.d->end << std::endl;

   int **nxt2 = data.append();
   int y = 11;
   *nxt2 = &y;
   // std::cout << data.d->begin << " " << data.d->end << std::endl;

   EXPECT_EQ(data.d->alloc, 4);
   EXPECT_EQ(data.d->begin, 0);
   EXPECT_EQ(**(data.d->array+data.d->begin), x);
   EXPECT_EQ(**(data.d->array+data.d->begin+1), y);
}

TEST(ListData, prepend) {
   ListData<int> data;
   int x = 10;

   int **nxt = data.prepend();
   EXPECT_EQ(data.size(), 1);
   EXPECT_EQ(data.d->alloc, 4);
   EXPECT_EQ(data.d->begin, 3);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);

   nxt = data.prepend();
   EXPECT_EQ(data.size(), 2);
   EXPECT_EQ(data.d->begin, 2);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);

   nxt = data.prepend();
   EXPECT_EQ(data.size(), 3);
   EXPECT_EQ(data.d->begin, 1);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);

   nxt = data.prepend();
   EXPECT_EQ(data.size(), 4);
   EXPECT_EQ(data.d->begin, 0);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);

   nxt = data.prepend();
   EXPECT_EQ(data.size(), 5);
   EXPECT_EQ(data.d->alloc, 10);
   EXPECT_EQ(data.d->begin, 5);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);
}

TEST(ListData, prependSparse) {

   ListData<int> data;
   data.realloc(100);

   int **nxt = data.prepend();
   EXPECT_EQ(data.size(), 1);
   EXPECT_EQ(data.d->alloc, 202);
   EXPECT_EQ(data.d->begin, 201);
   EXPECT_EQ(data.d->begin+data.size(), data.d->end);

}

void insertElements(ListData<int> *data, int *samples, int n) {
   
   data->realloc(100);

   //init the data array to be inserted in the list.
   for(int i=0; i<n; i++) {
      samples[i] = i;
   }

   //append 100 elements
   for(int i=0; i<n; i++) {
      int **nxt = data->append();
      *nxt = &samples[i];   
   }

   //verify consistency
   EXPECT_EQ(data->size(), n);
   for(int i=0; i<n; i++) {
      EXPECT_EQ(**(data->d->array+data->d->begin+i), samples[i]);
   }
}

TEST(ListData, removeFromTheFront) {

   int samples[100] = {};
   ListData<int> data;

   insertElements(&data, samples, 100);

      for(int i=0; i<100; i++) {
      data.remove(0);
      for(int j=i+1,k=0; j<100; j++,k++) {
         EXPECT_EQ(**(data.d->array+data.d->begin+k), samples[j]);
      }
   }
}

TEST(ListData, removeFromTheBack) {

   int samples[100] = {};
   ListData<int> data;

   insertElements(&data, samples, 100);

   for(int i=0; i<100; i++) {
      data.remove(data.size()-1);
      for(int j=0; j<data.size(); j++) {
         EXPECT_EQ(**(data.d->array+data.d->begin+j), samples[j]);
      }
   }
}

TEST(ListData, removeFromTheMiddle) {

   int samples[100] = {};
   ListData<int> data;

   insertElements(&data, samples, 100);

   
   data.remove(data.size()/2);

   for(int j=0, k=0; j<data.size(); j++,k++) {
      if(j == 50) {
         k++;  
      }
      EXPECT_EQ(**(data.d->array+data.d->begin+j), samples[k]);
   }
   
}

