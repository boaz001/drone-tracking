/**
 * synchronizer.cpp
 */

#include "synchronizer.h"
#include "dataCollector.h"
#include "sample.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

/**
 * @brief Constructor
 */
CSynchronizer::CSynchronizer()
 : bStopped_(true)
{
  std::cout << "CSynchronizer::CSynchronizer()" << std::endl;
  thread_ = boost::thread(&CSynchronizer::run, this);
}

/**
 * @brief Destructor
 */
CSynchronizer::~CSynchronizer()
{
  std::cout << "CSynchronizer::~CSynchronizer()" << std::endl;
  thread_.interrupt();
  thread_.join();
}

/**
 * @brief run
 */
void
CSynchronizer::run()
{
  std::cout << "CSynchronizer::run()" << std::endl;

  // try/catch for exception safety
  try
  {
    start();
  }
  catch (boost::thread_interrupted& interruption)
  {
    std::cout << "CSynchronizer::run() thread interrupted" << std::endl;
    stop();
  }
  catch (std::exception& e)
  {
    std::cout << "CSynchronizer::run() caught exception" << std::endl;
    stop();
  }
}

/**
 * @brief isStopped
 */
bool
CSynchronizer::isStopped()
{
  boost::lock_guard<boost::mutex> guard(mtxStopped_);
  return bStopped_;
}

/**
 * @brief Start
 */
void
CSynchronizer::start()
{
  std::cout << "CSynchronizer::start()" << std::endl;
  if (isStopped())
  {
    { // scoped guard
      boost::lock_guard<boost::mutex> guard(mtxStopped_);
      bStopped_ = false;
    }

    boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());

    while (isStopped() == false)
    {
      boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>(1000.0/dSampleRate_)));

      const boost::posix_time::ptime t2(boost::posix_time::microsec_clock::local_time());
      const boost::posix_time::time_duration td = t2 - t1;
      t1 = t2;

      // print elapsed milli seconds
      std::cout << "msecs between calls: " << td.total_milliseconds() << std::endl;

      boost::lock_guard<boost::mutex> guard(mtxDataCollectors_);
      for (tDataCollectors::const_iterator itr = dataCollectors_.begin()
                                         ; itr != dataCollectors_.end()
                                         ; itr++)
      {
        CSample sample = (*itr)->getSample();
      }
    }
  }
}

/**
 * @brief stop
 */
void
CSynchronizer::stop()
{
  std::cout << "CSynchronizer::stop()" << std::endl;
  boost::lock_guard<boost::mutex> guard(mtxStopped_);
  bStopped_ = true;
}

/**
 * @brief register dataCollector
 */
void
CSynchronizer::registerDataCollector(IDataCollector* const dataCollector)
{
  std::cout << "CSynchronizer::registerDataCollector( " << (void*)dataCollector << " )" << std::endl;
  boost::lock_guard<boost::mutex> guard(mtxDataCollectors_);
  dataCollectors_.insert(dataCollector);
}

/**
 * @brief setSampleRate
 */
void
CSynchronizer::setSampleRate(const double dSampleRate)
{
  std::cout << "CSynchronizer::setSampleRate( " << dSampleRate << " )" << std::endl;
  const bool bIsRunning = !isStopped();
  if (bIsRunning)
  {
    stop();
  }
  dSampleRate_ = dSampleRate;
  for (tDataCollectors::const_iterator itr = dataCollectors_.begin()
                                     ; itr != dataCollectors_.end()
                                     ; itr++)
  {
    (*itr)->setSampleRate(dSampleRate);
  }
  if (bIsRunning)
  {
    start();
  }
}
