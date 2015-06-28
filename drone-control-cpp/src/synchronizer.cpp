/**
 * synchronizer.cpp
 */

#include "synchronizer.h"
#include "synchronizedComponent.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>

/**
 * @brief Constructor
 */
CSynchronizer::CSynchronizer()
 : bPaused_(true)
 , bStop_(false)
 , dSamplePeriod_(1000.0)
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
    // construct once outside loop
    boost::asio::io_service io_svc;
    boost::posix_time::ptime t1(boost::posix_time::microsec_clock::local_time());

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

        const boost::posix_time::ptime t2(boost::posix_time::microsec_clock::local_time());
        const boost::posix_time::time_duration td = t2 - t1;
        t1 = t2;

        // wait for sample period
        boost::asio::deadline_timer timer(io_svc, boost::posix_time::microseconds(1000 * dSamplePeriod_));
        timer.wait();
        io_svc.run();

        // print elapsed milli seconds
        std::cout << "CSynchronizer::run() milliseconds since last call: " << static_cast<double>(td.total_microseconds()) / 1000.0 << std::endl;

        // send tick to SynchronizedComponents
        boost::lock_guard<boost::mutex> guard(mtxSynchronizedComponents_);
        for (tSynchronizedComponents::const_iterator itr = synchronizedComponents_.begin()
                                                   ; itr != synchronizedComponents_.end()
                                                   ; itr++)
        {
          (*itr)->tick();
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
 * @brief register synchronizedComponent
 */
void
CSynchronizer::registerSynchronizedComponent(ISynchronizedComponent* const synchronizedComponent)
{
  std::cout << "CSynchronizer::registerSynchronizedComponent( " << (void*)synchronizedComponent << " )" << std::endl;
  boost::lock_guard<boost::mutex> guard(mtxSynchronizedComponents_);
  synchronizedComponents_.insert(synchronizedComponent);
}

/**
 * @brief unregister synchronizedComponent
 */
void
CSynchronizer::unregisterSynchronizedComponent(ISynchronizedComponent* const synchronizedComponent)
{
  std::cout << "CSynchronizer::unregisterSynchronizedComponent( " << (void*)synchronizedComponent << " )" << std::endl;
  boost::lock_guard<boost::mutex> guard(mtxSynchronizedComponents_);
  synchronizedComponents_.erase(synchronizedComponent);
}

/**
 * @brief setSamplePeriod
 */
void
CSynchronizer::setSamplePeriod(const double dSamplePeriod)
{
  std::cout << "CSynchronizer::setSamplePeriod( " << dSamplePeriod << " )" << std::endl;
  dSamplePeriod_ = dSamplePeriod;
  boost::lock_guard<boost::mutex> guard(mtxSynchronizedComponents_);
  for (tSynchronizedComponents::const_iterator itr = synchronizedComponents_.begin()
                                             ; itr != synchronizedComponents_.end()
                                             ; itr++)
  {
    (*itr)->setSamplePeriod(dSamplePeriod);
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
