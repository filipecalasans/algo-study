
#include "twolevelpage.h"
#include "global/assert.h"

using namespace Algos;

#define ERROR 0xFFFFFFFF

TwoLevelPage::TwoLevelPage() :
  page_tables(TwoLevelPage::FIRST_LEVEL, Vector<uint32_t>())
{
  
}

bool TwoLevelPage::insert(uint32_t key, uint32_t data)
{
  uint32_t address = key / TwoLevelPage::PAGE_SIZE;
  uint32_t first_level = address / TwoLevelPage::FIRST_LEVEL;
  uint32_t second_level = address % TwoLevelPage::FIRST_LEVEL;
  
  data &= 0xFFFFF000;
  if(this->page_tables[first_level].size() 
      < TwoLevelPage::SECOND_LEVEL) {
    this->page_tables[first_level] = 
      Vector<uint32_t>(TwoLevelPage::SECOND_LEVEL, ERROR);
  }

  this->page_tables[first_level][second_level] = data;
}

uint32_t TwoLevelPage::get(uint32_t key)
{  
  uint32_t mask = TwoLevelPage::PAGE_SIZE - 1;
  uint32_t address = key / TwoLevelPage::PAGE_SIZE;
  uint32_t first_level = address / TwoLevelPage::FIRST_LEVEL;
  uint32_t second_level = address % TwoLevelPage::FIRST_LEVEL;

  if(this->page_tables[first_level].size() 
      < TwoLevelPage::SECOND_LEVEL) {
    return ERROR;
  }
  
  uint32_t data = this->page_tables[first_level][second_level];
  return data | (key & mask); 
}

bool TwoLevelPage::conains(uint32_t key)
{  
  uint32_t address = key / TwoLevelPage::PAGE_SIZE;
  uint32_t first_level = address / TwoLevelPage::FIRST_LEVEL;
  uint32_t second_level = address % TwoLevelPage::FIRST_LEVEL;
  
  if(this->page_tables[first_level].size() 
      < TwoLevelPage::SECOND_LEVEL) {
    return false;
  }

  return this->page_tables[first_level][second_level] == ERROR;
}
