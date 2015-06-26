// drone-control.cpp

#include "dataAquisitionController.h"
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
  CDataAquisitionController dataAquisitionController;
  dataAquisitionController.setSampleRate(1.0);

  // run the app for a while
  std::cout << "going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "awake!" << std::endl;

  dataAquisitionController.setPaused(true);

  std::cout << "going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "awake!" << std::endl;

  dataAquisitionController.setPaused(false);

  std::cout << "going to sleep..." << std::endl;
#ifdef _WIN32
   Sleep(10000);
#else
  usleep(10000000);
#endif
  std::cout << "awake!" << std::endl;

  // close the application

  return EXIT_SUCCESS;
}
