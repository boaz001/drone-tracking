/**
 * dataAquisitionController.cpp
 */

#include "dataAquisitionController.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDataAquisitionController::CDataAquisitionController()
 : synchronizer_()
 , OptiTrackDC_()
 , ReferenceDC_()
{
  std::cout << "CDataAquisitionController::CDataAquisitionController()" << std::endl;
  synchronizer_.registerDataCollector(&OptiTrackDC_);
  synchronizer_.registerDataCollector(&ReferenceDC_);
}

/**
 * @brief Destructor
 */
CDataAquisitionController::~CDataAquisitionController()
{
  std::cout << "CDataAquisitionController::~CDataAquisitionController()" << std::endl;
}

/**
 * @brief setPaused
 */
void
CDataAquisitionController::setPaused(const bool bPaused)
{
  synchronizer_.setPaused(bPaused);
}

/**
 * @brief setSampleRate
 */
void
CDataAquisitionController::setSampleRate(const double dSampleRate)
{
  std::cout << "CDataAquisitionController::setSampleRate( " << dSampleRate << " )" << std::endl;
  synchronizer_.setSampleRate(dSampleRate);
}
