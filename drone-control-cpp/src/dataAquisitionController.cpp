/**
 * dataAquisitionController.cpp
 */

#include "dataAquisitionController.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDataAquisitionController::CDataAquisitionController()
 : synchronizer()
 , OptiTrackDC()
 , ReferenceDC()
{
  std::cout << "CDataAquisitionController::CDataAquisitionController()" << std::endl;
  synchronizer.registerDataCollector(&OptiTrackDC);
  synchronizer.registerDataCollector(&ReferenceDC);
}

/**
 * @brief Destructor
 */
CDataAquisitionController::~CDataAquisitionController()
{
  std::cout << "CDataAquisitionController::~CDataAquisitionController()" << std::endl;
  // stop synchronizer
  synchronizer.stop();
}

/**
 * @brief start
 */
void
CDataAquisitionController::start()
{
  std::cout << "CDataAquisitionController::start()" << std::endl;
  synchronizer.start();
}

/**
 * @brief stop
 */
void
CDataAquisitionController::stop()
{
  std::cout << "CDataAquisitionController::stop()" << std::endl;
  synchronizer.stop();
}

/**
 * @brief setSampleRate
 */
void
CDataAquisitionController::setSampleRate(const double dSampleRate)
{
  std::cout << "CDataAquisitionController::setSampleRate( " << dSampleRate << " )" << std::endl;
  synchronizer.setSampleRate(1.002);
}
