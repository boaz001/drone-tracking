/**
 * synchronizer.h
 */
#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <boost/thread.hpp>

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
  void setSampleRate(const double dSampleRate);

private:
  // @brief
  void run();

  // private data members
  boost::thread thread_;

  // @brief is synchronizer timer running?
  bool bStopped_;
  // @brief registered DataCollectors
  typedef std::set<IDataCollector* const> tDataCollectors;
  tDataCollectors dataCollectors_;
  // @brief sample rate
  double dSampleRate_;

  // mutexes to guard private data members thread-safe
  boost::mutex mtxStopped_;
  boost::mutex mtxDataCollectors_;
};

#endif
