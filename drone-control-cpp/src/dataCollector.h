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
  virtual double getSampleRate() const = 0;
  // @brief
  virtual void setSampleRate(const double dSampleRate) = 0;

};

#endif