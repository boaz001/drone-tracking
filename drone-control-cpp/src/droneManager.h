/**
 * droneManager.h
 */
#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include "droneCollection.h"
#include "droneCommander.h"
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

  // @brief
  void registerDroneCommander(CDroneCommander* const droneCommander);

private:
  // @brief
  void resize();

  size_t size_;
  typedef std::deque<CDroneCollection> tDroneCollections;
  tDroneCollections droneCollections_;
  // @brief the registered drone commander
  CDroneCommander* pDroneCommander_;
};

#endif
