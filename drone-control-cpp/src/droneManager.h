/**
 * droneManager.h
 */
#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include "droneCollection.h"
#include <deque>

/**
 * @brief Drone Manager class
 * @details [long description]
 */
class CDroneManager
{
public:
  CDroneManager();
  virtual ~CDroneManager();

  // @brief
  void setSize(const size_t size);
  // @brief
  size_t getSize() const;

  // @brief
  void addDroneCollection(const CDroneCollection& droneCollection);

  // @brief
  void calculate();

private:
  size_t size_;
  typedef std::deque<CDroneCollection> tDroneCollections;
  tDroneCollections droneCollections_;
};

#endif
