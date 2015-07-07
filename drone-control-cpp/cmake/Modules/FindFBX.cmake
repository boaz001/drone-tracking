#
# Originally from: http://trac.openscenegraph.org/projects/osg/browser/OpenSceneGraph/trunk/CMakeModules/FindFBX.cmake adjusted to work with this project.
# Full license at: http://trac.openscenegraph.org/projects/osg/attachment/wiki/Legal/LICENSE.txt
#                 OpenSceneGraph Public License, Version 0.0
#                 ==========================================
#
#   Copyright (C) 2002 Robert Osfield.
#
#   Everyone is permitted to copy and distribute verbatim copies
#   of this licence document, but changing it is not allowed.
#
#                        OPENSCENEGRAPH PUBLIC LICENCE
#      TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
#
#   This library is free software; you can redistribute it and/or modify it
#   under the terms of the OpenSceneGraph Public License (OSGPL) version 0.0
#   or later.
#
#   Notes: the OSGPL is based on the LGPL, with the 4 exceptions laid
#   out in the wxWindows section below.  The LGPL is contained in the
#   final section of this license.
#
# Locate FBX
# This module defines:
# FBX_INCLUDE_DIR, where to find the headers
#
# FBX_LIBRARY
# FBX_FOUND
#
# $FBX_DIR is an environment variable that would
# correspond to the ./configure --prefix=$FBX_DIR

IF(APPLE)
    SET(FBX_LIBDIR "ios-i386")
ELSEIF(CMAKE_COMPILER_IS_GNUCXX)
    SET(FBX_LIBDIR "gcc4")
ELSEIF(MSVC80)
    SET(FBX_LIBDIR "vs2005")
ELSEIF(MSVC90)
    SET(FBX_LIBDIR "vs2008")
ELSEIF(MSVC10)
    SET(FBX_LIBDIR "vs2010")
ELSEIF(MSVC11)
    SET(FBX_LIBDIR "vs2012")
ELSEIF(MSVC12 OR MSVC_VERSION>1800)
    SET(FBX_LIBDIR "vs2013")
ENDIF()

IF(APPLE)
    # do nothing
ELSEIF(CMAKE_CL_64)
    SET(FBX_LIBDIR ${FBX_LIBDIR}/x64)
ELSEIF(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(FBX_LIBDIR ${FBX_LIBDIR}/x64)
ELSE()
    SET(FBX_LIBDIR ${FBX_LIBDIR}/x86)
ENDIF()

IF(APPLE)
    SET(FBX_LIBNAME "libfbxsdk.a")
ELSEIF(CMAKE_COMPILER_IS_GNUCXX)
    SET(FBX_LIBNAME "fbxsdk")
ELSE()
    SET(FBX_LIBNAME "libfbxsdk-md")
ENDIF()

SET( FBX_SEARCH_PATHS
    $ENV{FBX_DIR}
    "$ENV{ProgramW6432}/Autodesk/FBX/FBX SDK/2015.1"
    "$ENV{PROGRAMFILES}/Autodesk/FBX/FBX SDK/2015.1"
    /Applications/Autodesk/FBX\ SDK/2015.1
)

# search for headers & debug/release libraries
FIND_PATH(FBX_INCLUDE_DIR "fbxsdk.h"
    PATHS ${FBX_SEARCH_PATHS}
    PATH_SUFFIXES "include")

IF(CMAKE_BUILD_TYPE EQUAL "Debug")
  FIND_LIBRARY( FBX_LIBRARY ${FBX_LIBNAME}
      PATHS ${FBX_SEARCH_PATHS}
      PATH_SUFFIXES "lib/${FBX_LIBDIR}/debug")
ELSE()
  FIND_LIBRARY( FBX_LIBRARY ${FBX_LIBNAME}
      PATHS ${FBX_SEARCH_PATHS}
      PATH_SUFFIXES "lib/${FBX_LIBDIR}/release")
ENDIF()

IF(FBX_LIBRARY AND FBX_INCLUDE_DIR)
    SET(FBX_FOUND "YES")
ELSE()
    SET(FBX_FOUND "NO")
ENDIF()
