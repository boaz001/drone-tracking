// drone-control.cpp

#include <iostream>
#include "synchronizer.h"
#include "OptiTrackDataCollector.h"
#include "referenceDataCollector.h"

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
  COptiTrackDataCollector OptiTrackDC;
  CReferenceDataCollector ReferenceDC;
  CSynchronizer synchronizer;
  synchronizer.registerDataCollector(&OptiTrackDC);
  synchronizer.registerDataCollector(&ReferenceDC);
  synchronizer.setSampleRate(1.002);

  // run the app for a while
  std::cout << "going to sleep..." << std::endl;
  usleep(10000000);
  std::cout << "awake!" << std::endl;

  // stop the synchronizer before closing the application
  synchronizer.stop();

  return EXIT_SUCCESS;
}
