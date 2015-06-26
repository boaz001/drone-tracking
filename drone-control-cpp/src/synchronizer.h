/**
 * synchronizer.h
 */
#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <boost/thread.hpp>
#include <set>

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
  void registerDataCollector(IDataCollector* const dataCollector);
  // @brief
  void setSampleRate(const double dSampleRate);
  // @brief
  void setPaused(const bool bPaused_);

private:
  // @brief
  void run();
  // @brief
  void stop();

  // private data members
  // @brief the thread the synchronizer runs in
  boost::thread thread_;

  // @brief is synchronizer pauzed?
  bool bPaused_;
  // @brief stop the synchronizer (will return from the thread)
  bool bStop_;
  // @brief registered DataCollectors
  typedef std::set<IDataCollector*> tDataCollectors;
  tDataCollectors dataCollectors_;
  // @brief sample rate
  double dSampleRate_;

  // mutexes to guard private data members thread-safe
  boost::condition_variable varPauseChanged_;
  boost::mutex mtxStop_;
  boost::mutex mtxPause_;
  boost::mutex mtxDataCollectors_;
};

#endif
