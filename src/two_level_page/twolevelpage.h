
#ifndef TWO_LEVEL_PAGE_H_
#define TWO_LEVEL_PAGE_H_

#include <iostream>
#include <cstdint>
#include <memory>

#include "global/assert.h"
#include "vector/vector.h"

/**
 * This Two Level Page Table implements a 2-level
 * tree for storing up to 4GB values. Keys are used
 * to find the position by decomposing the key into
 * three indexes 
 *
 * [first-level (10-bit) | second-level (10 -bit) | offset (12-bit)]
 */

namespace Algos
{

class TwoLevelPage
{

public:
  
  TwoLevelPage();  
  bool insert(uint32_t key, uint32_t data);
  uint32_t get(uint32_t key);
  uint32_t conains(uint32_t key);
  
  // Allow maximum 2GB capacity.
  inline uint32_t capacity() { return 0xFFFFFFFF / 2; }

private:
  
  static const uint32_t FIRST_LEVEL = 1024;
  static const uint32_t SECOND_LEVEL = 1024;
  static const uint32_t PAGE_SIZE = 4096;
   
  Vector<Vector<uint32_t>> page_tables;

}; // End of TwoLevelPage

} // End of Algos

#endif
