
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