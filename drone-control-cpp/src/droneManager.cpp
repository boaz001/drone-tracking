/**
 * droneManager.cpp
 */

#include "droneManager.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDroneManager::CDroneManager()
 : size_(5)
{
  std::cout << "CDroneManager::CDroneManager()" << std::endl;
}

/**
 * @brief Destructor
 */
CDroneManager::~CDroneManager()
{
  std::cout << "CDroneManager::~CDroneManager()" << std::endl;
}

/**
 * @brief set size
 */
void
CDroneManager::setSize(const size_t size)
{
  size_ = size;
  resize();
}

/**
 * @brief getSize
 */
size_t
CDroneManager::getSize() const
{
  return size_;
}

/**
 * @brief resize
 */
void
CDroneManager::resize()
{
  while (droneCollections_.size() > size_)
  {
    droneCollections_.pop_front();
  }
}

/**
 * @brief addDroneCollection
 */
void
CDroneManager::addDroneCollection(const CDroneCollection& droneCollection)
{
  std::cout << "CDroneManager::addDroneCollection()" << std::endl;
  droneCollections_.push_back(droneCollection);
  if (droneCollections_.size() > size_)
  {
    droneCollections_.pop_front();
  }
}

/**
 * @brief calculate
 */
void
CDroneManager::calculate()
{}
