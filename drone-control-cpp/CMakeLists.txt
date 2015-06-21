cmake_minimum_required( VERSION 2.8 )

project( drone-control )

set(${PROJECT_NAME}_VERSION_MAJOR_0)
set(${PROJECT_NAME}_VERSION_MINOR_0)
set(${PROJECT_NAME}_VERSION_PATCH_0)

# If you build opencv from source, provide the path here
# Otherwise comment this and it should work
#SET(OpenCV_DIR ~/code/opencv/build)

find_package( OpenCV REQUIRED )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable( drone-control src/drone-control.cpp )

target_link_libraries( drone-control ${OpenCV_LIBS} )

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
