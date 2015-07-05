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
 * @brief merge
 */
CDroneCollection
CDataMerger::merge(const std::vector<CSample>& samples)
{
  std::cout << "CDataMerger::merge()" << std::endl;
  CDroneCollection droneCollection;

  // convert Samples into Drones

  // merge the sample data into a drone collection
  // handle possible duplicates or
  return droneCollection;
}

/**
 * @brief bind
 */
void
CDataMerger::bind(const std::string& str, const int id)
{
  droneBindings_[str] = id;
}
