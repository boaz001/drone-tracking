/**
 * referenceDataCollector.cpp
 */
#include "referenceDataCollector.h"
#include <iostream>

/**
 * @brief Constructor
 */
CReferenceDataCollector::CReferenceDataCollector()
 : IDataCollector()
{
  std::cout << "CReferenceDataCollector::CReferenceDataCollector()" << std::endl;
}

/**
 * @brief Destructor
 */
CReferenceDataCollector::~CReferenceDataCollector()
{
  std::cout << "CReferenceDataCollector::~CReferenceDataCollector()" << std::endl;
}

/**
 * @brief getSample
 */
CSample
CReferenceDataCollector::getSample() const
{
  std::cout << "CReferenceDataCollector::getSample()" << std::endl;
  CSample sample;
  return sample;
}

/**
 * @brief getSampleRate
 */
double
CReferenceDataCollector::getSampleRate() const
{
  std::cout << "CReferenceDataCollector::getSampleRate()" << std::endl;
  return dSampleRate_;
}

/**
 * @brief setSampleRate
 */
void
CReferenceDataCollector::setSampleRate(const double dSampleRate)
{
  std::cout << "CReferenceDataCollector::setSampleRate( " << dSampleRate << " )" << std::endl;
  dSampleRate_ = dSampleRate;
}
