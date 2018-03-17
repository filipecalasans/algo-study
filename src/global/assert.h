#ifndef __ALGO_ASSERT_HH_
#define __ALGO_ASSERT_HH_

#include <iostream>

#ifndef NDEBUG
#   define ALGO_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


#endif