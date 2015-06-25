/**
 * synchronizer.cpp
 */

#include "synchronizer.h"
#include "dataCollector.h"
#include "sample.h"

#include <unistd.h> // sleep()

/**
 * @brief Constructor
 */
CSynchronizer::CSynchronizer()
 : bStopped_(true)
{
  std::cout << "CSynchronizer::CSynchronizer()" << std::endl;
  internalThread_ = boost::thread(&CSynchronizer::run, this);
}

/**
 * @brief Destructor
 */
CSynchronizer::~CSynchronizer()
{
  std::cout << "CSynchronizer::~CSynchronizer()" << std::endl;
  internalThread_.interrupt();
  internalThread_.join();
}

/**
 * @brief run
 */
void
CSynchronizer::run()
{
  std::cout << "CSynchronizer::run()" << std::endl;

  try
  {
    /* add whatever code you want the thread to execute here. */
    start();
  }
  catch (boost::thread_interrupted& interruption)
  {
    // thread was interrupted, this is expected.
    stop();
  }
  catch (std::exception& e)
  {
    // an unhandled exception reached this point, this constitutes an error
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
    mtxStopped_.lock();
    bStopped_ = false;
    mtxStopped_.unlock();
    boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());

    while (isStopped() == false)
    {
      usleep(1000000); // sleep 1 sec

      if (dataCollectors_.size() == 0)
      {
        std::cout << "no registered DataCollector" << std::endl;
      }

      boost::posix_time::ptime t2(boost::posix_time::microsec_clock::local_time());
      boost::posix_time::time_duration td = t2 - t1;
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
