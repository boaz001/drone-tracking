// drone-control.cpp

#include <iostream>

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

  return EXIT_SUCCESS;
}
