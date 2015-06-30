/**
 * dataAquisitionController.cpp
 */

#include "dataAquisitionController.h"
#include "droneManager.h"
#include <iostream>

/**
 * @brief Constructor
 */
CDataAquisitionController::CDataAquisitionController()
 : ISynchronizedComponent()
 , bGetData_(false)
 , OptiTrackDC_()
 , ReferenceDC_()
 , dataMerger_()
 , pDroneManager_(NULL)
{
  std::cout << "CDataAquisitionController::CDataAquisitionController()" << std::endl;
  thread_ = boost::thread(&CDataAquisitionController::run, this);
}

/**
 * @brief Destructor
 */
CDataAquisitionController::~CDataAquisitionController()
{
  std::cout << "CDataAquisitionController::~CDataAquisitionController()" << std::endl;
  pDroneManager_ = NULL;
  thread_.interrupt();
  thread_.join();
}

/**
 * @brief run
 */
void
CDataAquisitionController::run()
{
  std::cout << "CDataAquisitionController::run()" << std::endl;
  // try/catch for exception safety
  try
  {
    // forever run
    while (true)
    {
      boost::unique_lock<boost::mutex> lock(mtxGetData_);
      if (bGetData_ == false)
      {
        // this wait is blocking
        std::cout << "CDataAquisitionController::run() waiting for data..." << std::endl;
        varGetDataChanged_.wait(lock);
        std::cout << "CDataAquisitionController::run() continue..." << std::endl;
        collectData();
        bGetData_ = false;
      }
    }
  }
  catch (boost::thread_interrupted& interruption)
  {
    std::cout << "CDataAquisitionController::run() thread interrupted" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << "CDataAquisitionController::run() caught exception" << std::endl;
  }
}

/**
 * @brief tick
 */
void
CDataAquisitionController::tick()
{
  std::cout << "CDataAquisitionController::tick()" << std::endl;
  {
    boost::unique_lock<boost::mutex> lock(mtxGetData_);
    bGetData_ = true;
  }
  varGetDataChanged_.notify_all();
}

/**
 * @brief register DroneManager
 */
void
CDataAquisitionController::registerDroneManager(CDroneManager* const droneManager)
{
  std::cout << "CDataAquisitionController::registerDroneManager( " << (void*)droneManager << " )" << std::endl;
  pDroneManager_ = droneManager;
}

/**
 * @brief collect data
 */
void
CDataAquisitionController::collectData()
{
  std::cout << "CDataAquisitionController::collectData()" << std::endl;
  std::vector<CSample> samples;
  samples.push_back(OptiTrackDC_.getSample());
  samples.push_back(ReferenceDC_.getSample());
  const CDroneCollection droneCollection(dataMerger_.merge(samples));
  // forward droneCollection
  if (pDroneManager_ != NULL)
  {
    pDroneManager_->addDroneCollection(droneCollection);
  }
}

/**
 * @brief setSamplePeriod
 */
void
CDataAquisitionController::setSamplePeriod(const double dSamplePeriod)
{
  // OptiTrackDC_.setSamplePeriod(dSamplePeriod);
  // ReferenceDC_.setSamplePeriod(dSamplePeriod);
}
