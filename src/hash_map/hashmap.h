#ifndef ALGOS_HASH_MAP_HH
#define ALGOS_HASH_MAP_HH

#include "linked_list/linkedlist.h"
#include "vector/vector.h"
#include "pair/pair.h"

namespace Algos
{

/* Buckets
 * [B0] -> [Linked_list]
 * [B1] -> [Linked_list]
 * [B2] -> [Linked_list]
 * [B3] -> [Linked_list]
 * [B4] -> [Linked_list]
 * [B5] -> [Linked_list]
 * [B6] -> [Linked_list]
 * [B7] -> [Linked_list]
 * [B8] -> [Linked_list]
 * [B9] -> [Linked_list]
 *
 * accessing an element is Buckets[hash(Key) % sizeof(Buckets)].get(Key)
 * we are not using consistent hash here
 *
 * When we reach a threshold load factor we 
 * can increase the  number of buckets and
 * rehash the content.
 */

template <class K,
          class V,
          class Hash = std::hash<K>,
          class Pred = std::equal_to<K>>
class HashMap
{
private:

    //std::shared_ptr<HashData<K,T>> d;
    
    static constexpr int PRIMES_SIZE = 20;

    /* Prime numbers used to generate the number of buckets */
    static constexpr unsigned int PRIMES[PRIMES_SIZE] = {
            547, 1019, 1223, 6131, 9967,
            11621, 17377, 23291, 29401,
            35671, 42013, 55001, 88651, 102161,
            209569, 422057, 812731, 1670269,
            2671093, 3999971 };

    static const unsigned int DEFAULT_BUCKETS_SIZE = PRIMES[0];

    struct HashData
    {
        Algos::Vector<Algos::LinkedList<Pair<K,V>>> data;
    };


public:

};

}

#endif
