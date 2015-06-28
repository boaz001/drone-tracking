// drone-control.cpp

#include "synchronizer.h"
#include "dataAquisitionController.h"
#include "droneManager.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h> // Sleep((ms)
#else
#include <unistd.h> // sleep(us)
#endif

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
  if (iDebug > 0)
  {
    std::cout << "debug level set to: " << iDebug << std::endl;
  }

  // application components
  CSynchronizer synchronizer;
  CDroneManager droneManager;
  CDataAquisitionController dataAquisitionController;
  dataAquisitionController.registerDroneManager(&droneManager);
  synchronizer.registerSynchronizedComponent(&dataAquisitionController);
  synchronizer.setSamplePeriod(1000.0);
  synchronizer.setPaused(false);

  // run the app for a while
  std::cout << "[app] going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "[app] awake!" << std::endl;

  synchronizer.setPaused(true);

  std::cout << "[app] going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "[app] awake!" << std::endl;

  synchronizer.setPaused(false);

  std::cout << "[app] going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "[app] awake!" << std::endl;

  // close the application
  synchronizer.unregisterSynchronizedComponent(&dataAquisitionController);

  return EXIT_SUCCESS;
}
