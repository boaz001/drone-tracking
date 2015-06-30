/**
 * droneCommander.cpp
 */

#include "droneCommander.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDroneCommander::CDroneCommander()
 : ISynchronizedComponent()
 , bGetData_(false)
{
  std::cout << "CDroneCommander::CDroneCommander()" << std::endl;
}

/**
 * @brief Destructor
 */
CDroneCommander::~CDroneCommander()
{
  std::cout << "CDroneCommander::~CDroneCommander()" << std::endl;
}

/**
 * @brief run
 */
void
CDroneCommander::run()
{
  std::cout << "CDroneCommander::run()" << std::endl;
  // try/catch for exception safety
  try
  {
    // forever run
    while (true)
    {
      boost::unique_lock<boost::mutex> lock(mtxGetData_);
      while (bGetData_ == false)
      {
        // this wait is blocking
        std::cout << "CDroneCommander::run() waiting for data..." << std::endl;
        varGetDataChanged_.wait(lock);
        bGetData_ = false;
        std::cout << "CDroneCommander::run() continue..." << std::endl;
      }
      sendCommand();
    }
  }
  catch (boost::thread_interrupted& interruption)
  {
    std::cout << "CDroneCommander::run() thread interrupted" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << "CDroneCommander::run() caught exception" << std::endl;
  }
}

/**
 * @brief tick
 */
void
CDroneCommander::tick()
{
  std::cout << "CDroneCommander::tick()" << std::endl;
  {
    boost::unique_lock<boost::mutex> lock(mtxGetData_);
    bGetData_ = true;
  }
  varGetDataChanged_.notify_all();
}

/**
 * @brief sendCommand
 */
void
CDroneCommander::sendCommand()
{
}

/**
 * @brief setSamplePeriod
 */
void
CDroneCommander::setSamplePeriod(const double dSamplePeriod)
{
}
