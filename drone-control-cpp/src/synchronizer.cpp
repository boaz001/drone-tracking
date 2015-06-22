/**
 * synchronizer.cpp
 */

#include "synchronizer.h"
#include "dataCollector.h"

/**
 * @brief Constructor
 */
CSynchronizer::CSynchronizer()
 : thread_()
 , io_svc_()
 , timer_(io_svc_, boost::posix_time::seconds(3))
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
  std::cout << "onTimer()" << std::endl;
}

/**
 * @brief service
 */
void
CSynchronizer::service()
{
  std::cout << "CSynchronizer::service()" << std::endl;

  timer_.async_wait(&CSynchronizer::onTimer);
  io_svc_.run();
}

/**
 * @brief Start
 */
void
CSynchronizer::start()
{
  std::cout << "CSynchronizer::start()" << std::endl;
  thread_ = boost::thread(&CSynchronizer::service, this);
  thread_.join();
}

/**
 * @brief stop
 */
void
CSynchronizer::stop()
{
  std::cout << "CSynchronizer::stop()" << std::endl;
}

/**
 * @brief register dataCollector
 */
void
CSynchronizer::registerDataCollector(IDataCollector* const dataCollector)
{}
