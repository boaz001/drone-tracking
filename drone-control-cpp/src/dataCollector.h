/**
 * dataCollector.h
 */
#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

class CSample;

/**
 * @brief DataCollector class
 * @details [long description]
 */
class IDataCollector
{
public:
  IDataCollector() {};
  virtual ~IDataCollector() {};

  // @brief
  virtual CSample getSample() const = 0;
  // @brief
  virtual double getSamplePeriod() const = 0;
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod) = 0;

};

#endif
