/**
 * OptiTrackDataCollector.h
 */
#ifndef OPTITRACKDATACOLLECTOR_H
#define OPTITRACKDATACOLLECTOR_H

#include "dataCollector.h"
#include "sample.h"
#include <NatNetClient.h>

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

  // @brief
  bool isConnected() const;

private:
  // @brief
  void connect();
  // @brief
  void disconnect();

  double dSamplePeriod_;
  NatNetClient* pNatNetClient_;
  bool bIsConnected_;
};

#endif
