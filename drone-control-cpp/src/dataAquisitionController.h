/**
 * dataAquisitionController.h
 */
#ifndef DATAAQUISITIONCONTROLLER_H
#define DATAAQUISITIONCONTROLLER_H

#include "synchronizedComponent.h"
#include "OptiTrackDataCollector.h"
#include "referenceDataCollector.h"
#include "dataMerger.h"
#include <boost/thread.hpp>

class CDroneManager;

/**
 * @brief Data Aquisition Controller class
 * @details [long description]
 */
class CDataAquisitionController: public ISynchronizedComponent
{
public:
  CDataAquisitionController();
  virtual ~CDataAquisitionController();

  // @brief
  virtual void tick();
  // @brief
  virtual void setSamplePeriod(const double dSamplePeriod);
  // @brief
  void registerDroneManager(CDroneManager* const droneManager);

private:
  // @brief
  void run();
  // @brief
  void collectData();

  // private data members
  // @brief the thread the DataAquisitionController runs in
  boost::thread thread_;

  // @brief
  // mutexes to guard private data members thread-safe
  bool bGetData_;
  boost::condition_variable varGetDataChanged_;
  boost::mutex mtxGetData_;

  // @brief the DataCollectors
  // TODO: use some sort of factory/configuration method to create DataCollectors
  COptiTrackDataCollector OptiTrackDC_;
  CReferenceDataCollector ReferenceDC_;

  // @brief dataMerger
  CDataMerger dataMerger_;

  CDroneManager* pDroneManager_;
};

#endif
