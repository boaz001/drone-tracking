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
 , bSendCommand_(false)
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
      boost::unique_lock<boost::mutex> lock(mtxSendCommand_);
      if (bSendCommand_ == false)
      {
        // this wait is blocking
        std::cout << "CDroneCommander::run() waiting for data..." << std::endl;
        varSendCommandChanged_.wait(lock);
        std::cout << "CDroneCommander::run() continue..." << std::endl;
        sendCommand();
        bSendCommand_ = false;
      }
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
    boost::unique_lock<boost::mutex> lock(mtxSendCommand_);
    bSendCommand_ = true;
  }
  varSendCommandChanged_.notify_all();
}

/**
 * @brief sendCommand
 */
void
CDroneCommander::sendCommand()
{
  std::cout << "CDroneCommander::sendCommand()" << std::endl;
  // send Command
}

/**
 * @brief setSamplePeriod
 */
void
CDroneCommander::setSamplePeriod(const double dSamplePeriod)
{
}

/**
 * @brief setNextCommand
 */
void
CDroneCommander::setNextCommand(const CCommand& command)
{
  nextCommand_ = command;
}
