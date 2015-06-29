/**
 * OptiTrackDataCollector.cpp
 */

#include "OptiTrackDataCollector.h"
#include <iostream>

/**
 * @brief Constructor
 */
COptiTrackDataCollector::COptiTrackDataCollector()
 : IDataCollector()
 , dSamplePeriod_(1000.0)
{
  std::cout << "COptiTrackDataCollector::COptiTrackDataCollector()" << std::endl;
}

/**
 * @brief Destructor
 */
COptiTrackDataCollector::~COptiTrackDataCollector()
{
  std::cout << "COptiTrackDataCollector::~COptiTrackDataCollector()" << std::endl;
}

/**
 * @brief getSample
 */
CSample
COptiTrackDataCollector::getSample() const
{
  std::cout << "COptiTrackDataCollector::getSample()" << std::endl;
  CSample sample;
  return sample;
}

/**
 * @brief getSamplePeriod
 */
double
COptiTrackDataCollector::getSamplePeriod() const
{
  std::cout << "COptiTrackDataCollector::getSamplePeriod()" << std::endl;
  return dSamplePeriod_;
}

/**
 * @brief setSamplePeriod
 */
void
COptiTrackDataCollector::setSamplePeriod(const double dSamplePeriod)
{
  std::cout << "COptiTrackDataCollector::setSamplePeriod( " << dSamplePeriod << " )" << std::endl;
  dSamplePeriod_ = dSamplePeriod;
}
