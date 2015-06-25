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
  return 0.0;
}

void
COptiTrackDataCollector::setSampleRate(const double dSampleRate)
{
}
