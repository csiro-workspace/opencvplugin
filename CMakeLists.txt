#============================================================================
#
#  Copyright 2016 by:
#
#    Commonwealth Scientific and Industrial Research Organisation (CSIRO)
#    
#    This file is licensed by CSIRO under the copy of the CSIRO Open Source
#    Software License Agreement (variation of the BSD / MIT License) included
#    with the file.
#
#    As a condition of this license, you agree that where you make any 
#    adaptations, modifications, further developments, or additional features 
#    available to CSIRO or the public in connection with your access to the 
#    Software, you do so on the terms of the BSD 3-Clause License template,
#    a copy available at: http://opensource.org/licenses/BSD-3-Clause
#
#    For further information, contact the CSIRO Workspace Team:
#    workspace@csiro.au
#
#  This copyright notice must be included with all copies of the source code.
#
#============================================================================

cmake_minimum_required(VERSION 3.0)
project(OPENCV)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    find_path(WORKSPACE_CMAKE_ROOT Workspace_CMake_Root.txt
              HINTS ${CMAKE_SOURCE_DIR} ENV WORKSPACE_CMAKE_ROOT
              DOC "Directory containing the Workspace_CMake_Root.txt file")
    if (NOT WORKSPACE_CMAKE_ROOT)
        message(FATAL_ERROR "Please set WORKSPACE_CMAKE_ROOT to the directory containing the file Workspace_CMake_Root.txt")
    endif()
    include( ${WORKSPACE_CMAKE_ROOT}/CMakeLists.txt NO_POLICY_SCOPE )
endif()

include_directories(${OPENCV_SOURCE_DIR})
if (NOT ${OPENCV_SOURCE_DIR} STREQUAL ${OPENCV_BINARY_DIR})
    include_directories(${OPENCV_BINARY_DIR})
endif()

set(OPENCV_PLUGIN_VERSION 0.1.0)
string(REGEX MATCH "^[0-9]+" OPENCV_PLUGIN_SOVERSION ${OPENCV_PLUGIN_VERSION})

set(CMAKE_AUTOMOC ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if(WIN32)
    # Stop OpenCV RelWithDebInfo build trying to use the debug libs (kaboom!)
    set_target_properties(${OpenCV_LIBS} PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
endif()

find_package(Qt5Core)
find_package(Qt5Widgets)
set(QT_LIBRARIES Qt5::Core;Qt5::Widgets)

set(HEADERS
    ${OPENCV_SOURCE_DIR}/cvtypes.h
    ${OPENCV_SOURCE_DIR}/opencvplugin_api.h
    ${OPENCV_SOURCE_DIR}/opencvplugin.h
)

set(INSTALL_HEADERS
    ${OPENCV_SOURCE_DIR}/cvtypes.h
    ${OPENCV_SOURCE_DIR}/opencvplugin_api.h
    ${OPENCV_SOURCE_DIR}/opencvplugin.h
)

set(MOC_HEADERS
)

set(SOURCES
    ${OPENCV_SOURCE_DIR}/cvtypes.cpp
    ${OPENCV_SOURCE_DIR}/opencvplugin.cpp
)

set(UI_SOURCES
)

include(${OPENCV_SOURCE_DIR}/Datatypes/CMakeLists.txt)
include(${OPENCV_SOURCE_DIR}/Operations/CMakeLists.txt)
include(${OPENCV_SOURCE_DIR}/Widgets/CMakeLists.txt)

add_definitions(-DOPENCV_PLUGIN_VERSION=${OPENCV_PLUGIN_VERSION})

# The next line is used by the simple application generator wizard
# add_subdirectory(${OPENCV_SOURCE_DIR}/Application)

# qtx macros are defined in the ${WORKSPACE_CMAKE_ROOT}/CMakeLists.txt included at the top of this file
# to support both Qt4 and Qt5 builds.
qtx_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
qtx_wrap_ui(UIC_SOURCES ${UI_SOURCES})
qtx_add_resources(RES_SOURCES ${RESOURCES})

add_library(opencvplugin ${SOURCES} ${HEADERS} ${MOC_SOURCES} ${UIC_SOURCES} ${RES_SOURCES})
target_link_libraries(opencvplugin dataanalysisplugin meshplugin renderingplugin workspace ${OpenCV_LIBS} ${QT_LIBRARIES})

set_target_properties(opencvplugin PROPERTIES
    DEFINE_SYMBOL CSIRO_OPENCV_EXPORT
    VERSION ${OPENCV_PLUGIN_VERSION}
    SOVERSION ${OPENCV_PLUGIN_SOVERSION}
)

setTargetOutputDirectory(opencvplugin ${CSIRO_INSTALL_AREA}/lib/Plugins)
configure_file(pkg-opencvplugin.cmake ${CSIRO_INSTALL_AREA}/cmake/Exports/pkg-opencvplugin.cmake @ONLY)

# If your plugin is dependent on any other dynamic libraries you can add the root path 
# of that library (the path above the lib, bin and include) as a new line to the installAreas
# file below. Anything in this file will be added to the path on Workspace startup.
#
# CMake probably wont have write access into the Workspace install area so we simply print a 
# message for the user.
file(WRITE ${CSIRO_INSTALL_AREA}/installAreas/installArea-opencvplugin.txt "${CSIRO_INSTALL_AREA}")
foreach(iPath ${OpenCV_LIB_DIR})
    file(APPEND ${CSIRO_INSTALL_AREA}/installAreas/installArea-opencvplugin.txt "\n${iPath}/..")
endforeach()
message(STATUS "Copy ${CSIRO_INSTALL_AREA}/installAreas/installArea-opencvplugin.txt into ${WORKSPACE_CMAKE_ROOT}/../installAreas to auto-load your plugin on startup")

# Copy our install headers into the install directory so that others can build against our plugin.
foreach(inFile ${INSTALL_HEADERS})
    string(REGEX REPLACE "(${OPENCV_SOURCE_DIR}/)(.*)" "${CSIRO_INSTALL_AREA}/include/OpenCV/\\2" outFile "${inFile}")
    configure_file(${inFile} ${outFile} COPYONLY)
endforeach(inFile)

add_subdirectory(Designer)

