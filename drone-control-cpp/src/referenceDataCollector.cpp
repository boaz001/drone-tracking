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
 , dSamplePeriod_(1000.0)
{
  std::cout << "CReferenceDataCollector::CReferenceDataCollector()" << std::endl;
}

/**
 * @brief Destructor
 */
CReferenceDataCollector::~CReferenceDataCollector()
{
  std::cout << "CReferenceDataCollector::~CReferenceDataCollector()" << std::endl;
  referenceFileHandle_.close();
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
 * @brief getSamplePeriod
 */
double
CReferenceDataCollector::getSamplePeriod() const
{
  std::cout << "CReferenceDataCollector::getSamplePeriod()" << std::endl;
  return dSamplePeriod_;
}

/**
 * @brief setSamplePeriod
 */
void
CReferenceDataCollector::setSamplePeriod(const double dSamplePeriod)
{
  std::cout << "CReferenceDataCollector::setSamplePeriod( " << dSamplePeriod << " )" << std::endl;
  dSamplePeriod_ = dSamplePeriod;
}

/**
 * @brief loadReferenceFile
 */
bool
CReferenceDataCollector::loadReferenceFile(const std::string& sFilename)
{
  referenceFileHandle_.open(sFilename.c_str(), std::ios_base::in);
  return referenceFileHandle_.is_open();
}

/**
 * @brief jumpTo
 */
bool
CReferenceDataCollector::jumpTo(const long iPosition)
{
  bool bSuccess(false);
  try
  {
    referenceFileHandle_.seekg(iPosition);
    bSuccess = true;
  }
  catch (std::ios_base::failure& e)
  {
    std::cout << "CReferenceDataCollector::jumpTo() failed to jump to position " << iPosition << std::endl;
  }
  return bSuccess;
}
