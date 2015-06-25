/**
 * synchronizer.h
 */
#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// forward declaration
class IDataCollector;

/**
 * @brief Synchronizer class
 * @details [long description]
 */
class CSynchronizer
{
public:
  CSynchronizer();
  virtual ~CSynchronizer();

  // @brief
  bool isStopped();
  // @brief
  void start();
  // @brief
  void stop();
  // @brief
  void registerDataCollector(IDataCollector* const dataCollector);
  // @brief
  void onTimer();
  // @brief
  void thread();

private:
  boost::mutex mtxStopped_;
  bool bStopped_;

  boost::mutex mtxDataCollectors_;
  typedef std::set<IDataCollector* const> tDataCollectors;
  tDataCollectors dataCollectors_;
  // boost::thread thread_;

  // boost::asio::io_service io_svc_;
  // boost::asio::deadline_timer timer_;

  // list of all registered dataCollectors
};

#endif
