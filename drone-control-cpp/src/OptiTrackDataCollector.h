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
  virtual double getSamplePeriod() const;
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod);

private:
  double dSamplePeriod_;
};

#endif
