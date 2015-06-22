/**
 * drone.h
 */
#ifndef DRONE_H
#define DRONE_H

#include "position.h"

/**
 * @brief Drone class
 * @details [long description]
 */
class CDrone
{
public:
  CDrone();
  virtual ~CDrone();

private:
  int id_;
  CPosition actPosition_;
  CPosition refPosition_;
};

#endif
