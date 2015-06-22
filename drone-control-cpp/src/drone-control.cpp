// drone-control.cpp

#include <iostream>
#include "drone.h"
#include "synchronizer.h"
#include "OptiTrackDataCollector.h"

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

  COptiTrackDataCollector OptiTrackDC;
  CSynchronizer synchronizer;

  if (iDebug > 0)
  {
    std::cout << "debug level set to: " << iDebug << std::endl;
  }

  return EXIT_SUCCESS;
}
