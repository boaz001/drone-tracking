/**
 * OptiTrackDataCollector.h
 */
#ifndef OPTITRACKDATACOLLECTOR_H
#define OPTITRACKDATACOLLECTOR_H

#include "dataCollector.h"
#include "sample.h"

/**
 * @brief OptiTrack DataCollector class
 * @details [long description]
 */
class COptiTrackDataCollector: public IDataCollector
{
public:
  COptiTrackDataCollector();
  virtual ~COptiTrackDataCollector();

  // inherited methods from IDataCollector
  // @brief
  virtual CSample getSample() const;
  // @brief
  virtual double getSampleRate() const;
  // @brief
  virtual void setSampleRate(const double dSampleRate);

};

#endif
