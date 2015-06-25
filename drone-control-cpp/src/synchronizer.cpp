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
 // : thread_()
 // , io_svc_()
 // , timer_(io_svc_, boost::posix_time::seconds(3))
{
  std::cout << "CSynchronizer::CSynchronizer()" << std::endl;
  // timer_.async_wait(&onTimer);
  // io_svc_.run();
}

/**
 * @brief Destructor
 */
CSynchronizer::~CSynchronizer()
{
  std::cout << "CSynchronizer::~CSynchronizer()" << std::endl;
}

/**
 * @brief onTimer
 */
void
CSynchronizer::onTimer()//const boost::system::error_code& e)
{
  std::cout << "CSynchronizer::onTimer()" << std::endl;
}

/**
 * @brief thread
 */
void
CSynchronizer::thread()
{
  std::cout << "CSynchronizer::thread()" << std::endl;

  // boost::asio::io_service io_svc;
  // boost::asio::deadline_timer timer(io_svc, boost::posix_time::seconds(2));
  // timer.async_wait(boost::bind(&CSynchronizer::onTimer, this));
  // io_svc.run();
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

  // std::cout << "creating thread" << std::endl;
  // while (true)
  // {
  //   boost::thread thread(boost::thread(&CSynchronizer::thread, this));
  //   std::cout << "thread with id: " << thread.get_id() << " created" << std::endl;
  //   thread.join();
  // }
  // boost::thread thread_ = boost::thread(&CSynchronizer::thread, this);
  // thread_.join();
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
