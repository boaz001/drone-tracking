# - Try to find OptiTrack NatNet SDK
# Once done this will define
#  NatNet_FOUND - System has NatNet
#  NatNet_INCLUDE_DIRS - The NatNet include directories
#  NatNet_LIBRARIES - The libraries needed to use NatNet
#
# Issues or weaknesses:
#  - does not support x64 libraries
#  - does not support dynamic/static linking depending on CMake setting
#  - relies on NATNETSDK_ROOT

# Set environment variable NATNETSDK_ROOT to be able to find it.
SET( NatNet_SEARCH_PATHS
     $ENV{NATNETSDK_ROOT} )

# find includes
find_path( NatNet_INCLUDE_DIR "NatNetClient.h"
           PATHS ${NatNet_SEARCH_PATHS}
           PATH_SUFFIXES include )

# find libaries (TODO: add support for x64, and Static and ML(?))
find_library( NatNet_LIBRARY NAMES NatNetLib
              PATHS ${NatNet_SEARCH_PATHS}
              PATH_SUFFIXES lib )

set( NatNet_LIBRARIES ${NatNet_LIBRARY} )
set( NatNet_INCLUDE_DIRS ${NatNet_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )
# handle the QUIETLY and REQUIRED arguments and set NatNet_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args( NatNet DEFAULT_MSG
                                   NatNet_LIBRARY NatNet_INCLUDE_DIR )
