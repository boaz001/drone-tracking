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
CDataMerger::bind(const tReferenceID& refID, const tActualID& actID)
{
  tDroneBindings::iterator itrFound = droneBindings_.find(refID);
  if (itrFound != droneBindings_.end())
  {
    // binding changed!
    itrFound->second = actID;
  }
  else
  {
    // binding created!
    droneBindings_.insert(std::pair<tReferenceID, tActualID>(refID, actID));
  }
}
