/**
 * droneCommander.h
 */
#ifndef DRONECOMMANDER_H
#define DRONECOMMANDER_H

#include "command.h"
#include "synchronizedComponent.h"
#include <boost/thread.hpp>
#include <deque>

/**
 * @brief Drone Commander class
 * @details [long description]
 */
class CDroneCommander: public ISynchronizedComponent
{
public:
  CDroneCommander();
  virtual ~CDroneCommander();

  // inherited from ISynchronizedComponent
  // @brief
  virtual void tick();
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod);

private:
  // @brief
  void run();
  // @brief
  void sendCommand();

  // private data members
  // @brief the thread the DataAquisitionController runs in
  boost::thread thread_;

  // @brief
  // mutexes to guard private data members thread-safe
  bool bGetData_;
  boost::condition_variable varGetDataChanged_;
  boost::mutex mtxGetData_;
};

#endif
