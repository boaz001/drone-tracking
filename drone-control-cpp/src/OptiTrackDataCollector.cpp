/**
 * OptiTrackDataCollector.cpp
 */
#include "OptiTrackDataCollector.h"

/**
 * @brief Constructor
 */
COptiTrackDataCollector::COptiTrackDataCollector()
 : IDataCollector()
{}

/**
 * @brief Destructor
 */
COptiTrackDataCollector::~COptiTrackDataCollector()
{}

CSample
COptiTrackDataCollector::getSample() const
{
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
