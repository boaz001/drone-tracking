/**
 * referenceDataCollector.h
 */
#ifndef REFERENCEDATACOLLECTOR_H
#define REFERENCEDATACOLLECTOR_H

#include "dataCollector.h"
#include "sample.h"
#include <string>
#include <fstream>

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
  virtual double getSamplePeriod() const;
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod);

  // @brief
  bool loadReferenceFile(const std::string& sFilename);
  // @brief
  bool jumpTo(const long iPosition);

private:
  double dSamplePeriod_;
  std::ifstream referenceFileHandle_;
};

#endif
