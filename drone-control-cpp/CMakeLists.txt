cmake_minimum_required( VERSION 2.8 )

project( drone-control )

set(${PROJECT_NAME}_VERSION_MAJOR_0)
set(${PROJECT_NAME}_VERSION_MINOR_0)
set(${PROJECT_NAME}_VERSION_PATCH_0)

# If you build opencv from source, provide the path here
# Otherwise comment this and it should work
#SET(OpenCV_DIR ~/code/opencv/build)
# Some settings for Windows env / Embarcadero XE7 compiler
#SET(OpenCV_DIR D:/thirdparty/opencv/source/opencv/build)
#SET(BOOST_ROOT "C:/Program Files (x86)/Embarcadero/Studio/15.0/include/boost_1_39")
#SET(BOOST_LIBRARYDIR "C:/Program Files (x86)/Embarcadero/Studio/15.0/lib/win32/release")

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Some settings for OptiTrack NatNet
#SET ( NATNETSDK_ROOT ${CMAKE_SOURCE_DIR}/NatNetSDK )
# Some settings for Autodesk FBX support
#SET( FBX_DIR ... )

find_package( OpenCV REQUIRED )
find_package( Boost 1.39.0 REQUIRED system thread)
find_package( FBX REQUIRED )
find_package( NatNet REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${FBX_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${NatNet_INCLUDE_DIRS} )

file(GLOB_RECURSE drone-control_SOURCES "src/*.cpp")

add_executable( drone-control ${drone-control_SOURCES} )

target_link_libraries( drone-control ${OpenCV_LIBS} ${Boost_LIBRARIES} ${FBX_LIBRARY} ${NatNet_LIBRARIES} )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
