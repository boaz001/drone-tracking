/**
 * dataAquisitionController.h
 */
#ifndef DATAAQUISITIONCONTROLLER_H
#define DATAAQUISITIONCONTROLLER_H

#include "synchronizer.h"
#include "OptiTrackDataCollector.h"
#include "referenceDataCollector.h"

class IDataCollectors;

/**
 * @brief Data Aquisition Controller class
 * @details [long description]
 */
class CDataAquisitionController
{
public:
  CDataAquisitionController();
  virtual ~CDataAquisitionController();

  // @brief
  void setPaused(const bool bPaused);
  // @brief
  void setSampleRate(const double dSampleRate);

private:
  // private data members
  // @brief synchronizer
  CSynchronizer synchronizer_;

  // @brief the DataCollectors
  // TODO: use some sort of factory/configuration method to create DataCollectors
  COptiTrackDataCollector OptiTrackDC_;
  CReferenceDataCollector ReferenceDC_;
};

#endif
