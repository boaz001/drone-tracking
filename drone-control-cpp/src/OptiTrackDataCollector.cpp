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
 , dSampleRate_(1.0)
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

CSample
COptiTrackDataCollector::getSample() const
{
  std::cout << "COptiTrackDataCollector::getSample()" << std::endl;
  CSample sample;
  return sample;
}

double
COptiTrackDataCollector::getSampleRate() const
{
  std::cout << "COptiTrackDataCollector::getSampleRate()" << std::endl;
  return dSampleRate_;
}

void
COptiTrackDataCollector::setSampleRate(const double dSampleRate)
{
  std::cout << "COptiTrackDataCollector::setSampleRate( " << dSampleRate << " )" << std::endl;
  dSampleRate_ = dSampleRate;
}
