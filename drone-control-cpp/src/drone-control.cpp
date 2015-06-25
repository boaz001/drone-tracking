// drone-control.cpp

#include <iostream>
#include "drone.h"
#include "synchronizer.h"
#include "OptiTrackDataCollector.h"

CSynchronizer* pSynchronizer = NULL;

// thread to run the synchronizer in
void
synchronizer_thread()
{
  std::cout << "synchronizer_thread" << std::endl;
  if (pSynchronizer)
  {
    pSynchronizer->start();
  }
}

// main entry point
int
main(int argc, char** argv)
{
  // TODO: use OpenCV getCommandArgs
  int iDebug = 0;
  if (argc == 2)
  {
    iDebug = std::atoi(argv[1]);
  }

  if (pSynchronizer == NULL)
  {
    pSynchronizer = new CSynchronizer();
  }
  COptiTrackDataCollector OptiTrackDC;
  pSynchronizer->registerDataCollector(&OptiTrackDC);

  boost::thread thread_sync(&synchronizer_thread);
  std::cout << "synchronizer_thread with id: " << thread_sync.get_id() << " created" << std::endl;
  std::cout << "joining sync thread" << std::endl;
  thread_sync.join();

  // usleep(10000);

  // CSynchronizer synchronizer;

  // boost::thread main_thread(&print2);
  // std::cout << "main_thread with id: " << main_thread.get_id() << " created" << std::endl;
  // main_thread.join();

  std::cout << "start()" << std::endl;
  // synchronizer.start();


  // boost::asio::io_service io;
  // boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  // t.async_wait(&print);
  // io.run();
  std::cout << "done" << std::endl;

  if (iDebug > 0)
  {
    std::cout << "debug level set to: " << iDebug << std::endl;
  }

  if (pSynchronizer)
  {
    delete pSynchronizer;
  }

  return EXIT_SUCCESS;
}
