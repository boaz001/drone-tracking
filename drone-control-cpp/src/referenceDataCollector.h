/**
 * referenceDataCollector.h
 */
#ifndef REFERENCEDATACOLLECTOR_H
#define REFERENCEDATACOLLECTOR_H

#include "dataCollector.h"
#include "sample.h"

/**
 * @brief reference DataCollector class
 * @details [long description]
 */
class CReferenceDataCollector: public IDataCollector
{
public:
  CReferenceDataCollector();
  virtual ~CReferenceDataCollector();

  // inherited methods from IDataCollector
  // @brief
  virtual CSample getSample() const;
  // @brief
  virtual double getSampleRate() const;
  // @brief
  virtual void setSampleRate(const double dSampleRate);

private:
  double dSampleRate_;
};

#endif
