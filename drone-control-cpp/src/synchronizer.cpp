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
 : bPaused_(false)
 , bStop_(false)
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
  stop();
  thread_.interrupt();
  thread_.join();
}

/*
  some timing code...

boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());
const boost::posix_time::ptime t2(boost::posix_time::microsec_clock::local_time());
const boost::posix_time::time_duration td = t2 - t1;
t1 = t2;
// print elapsed milli seconds
std::cout << "msecs between calls: " << td.total_milliseconds() << std::endl;
*/

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
    // forever run
    while (true)
    {
      { // if it should stop, break!
        boost::lock_guard<boost::mutex> guard(mtxStop_);
        if (bStop_ == true)
        {
          break;
        }
      }

      { // if it should pause, wait!
        boost::unique_lock<boost::mutex> lock(mtxPause_);
        while (bPaused_ == true)
        {
          std::cout << "CSynchronizer::run() pause..." << std::endl;
          // this wait is blocking
          varPauseChanged_.wait(lock);
          std::cout << "CSynchronizer::run() continue..." << std::endl;
        }
      }

      { // else, run Forrest run!
        std::cout << "CSynchronizer::run() running..." << std::endl;
        // wait for sample period
        boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>(1000.0/dSampleRate_)));

        // get samples from DataCollectors
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
  catch (boost::thread_interrupted& interruption)
  {
    std::cout << "CSynchronizer::run() thread interrupted" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << "CSynchronizer::run() caught exception" << std::endl;
  }
}

/**
 * @brief stop
 */
void
CSynchronizer::stop()
{
  std::cout << "CSynchronizer::stop()" << std::endl;
  boost::lock_guard<boost::mutex> guard(mtxStop_);
  bStop_ = true;
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
  dSampleRate_ = dSampleRate;
  for (tDataCollectors::const_iterator itr = dataCollectors_.begin()
                                     ; itr != dataCollectors_.end()
                                     ; itr++)
  {
    (*itr)->setSampleRate(dSampleRate);
  }
}

/**
 * @brief setPause
 */
void
CSynchronizer::setPaused(const bool bPaused)
{
  std::cout << "CSynchronizer::setPaused( " << bPaused << " )" << std::endl;
  {
    boost::unique_lock<boost::mutex> lock(mtxPause_);
    bPaused_ = bPaused;
  }
  varPauseChanged_.notify_all();
}
