/**
 * dataMerger.cpp
 */

#include "dataMerger.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDataMerger::CDataMerger()
{
  std::cout << "CDataMerger::CDataMerger()" << std::endl;
}

/**
 * @brief Destructor
 */
CDataMerger::~CDataMerger()
{
  std::cout << "CDataMerger::~CDataMerger()" << std::endl;
}

/**
 * @brief Destructor
 */
CDroneCollection
CDataMerger::merge(const std::vector<CSample>& samples)
{
  std::cout << "CDataMerger::merge()" << std::endl;
  CDroneCollection droneCollection;

  // merge the sample data into a drone collection
  // handle possible duplicates or
  return droneCollection;
}
