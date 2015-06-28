/**
 * droneCollection.h
 */
#ifndef DRONECOLLECTION_H
#define DRONECOLLECTION_H

#include "drone.h"
#include <vector>

/**
 * @brief Drone Collection class
 * @details [long description]
 */
class CDroneCollection
{
public:
  CDroneCollection();
  virtual ~CDroneCollection();

private:
  std::vector<CDrone> drones_;
};

#endif
