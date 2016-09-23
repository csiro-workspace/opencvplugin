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

IF("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   MESSAGE(FATAL_ERROR "CMake >= 2.6.0 required")
ENDIF()
CMAKE_POLICY(PUSH)
CMAKE_POLICY(VERSION 2.6)
IF(NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 3.0)
    CMAKE_POLICY(SET CMP0045 OLD)
ENDIF()

GET_TARGET_PROPERTY(opencvplugin_location opencvplugin LOCATION)
if (NOT OPENCV_SOURCE_DIR AND NOT opencvplugin_location AND NOT TARGET opencvplugin)
    # Commands may need to know the format version.
    SET(CMAKE_IMPORT_FILE_VERSION 1)

    # Compute the installation prefix relative to this file.
    GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
    GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
    GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

    # Create imported target opencvplugin
    ADD_LIBRARY(opencvplugin SHARED IMPORTED)
    if (WIN32)
        find_file(IMPORTLIB opencvplugin.lib PATHS "${_IMPORT_PREFIX}/lib/Plugins"
                  PATH_SUFFIXES  Release RelWithDebInfo MinSizeRel Debug NO_DEFAULT_PATHS)
        SET_TARGET_PROPERTIES(opencvplugin PROPERTIES
                              IMPORTED_LOCATION "${_IMPORT_PREFIX}/lib/Plugins/opencvplugin.dll"
                              IMPORTED_IMPLIB   "${IMPORTLIB}")
        unset(IMPORTLIB CACHE)
    elseif(APPLE)
        SET_TARGET_PROPERTIES(opencvplugin PROPERTIES
                              IMPORTED_LOCATION "${_IMPORT_PREFIX}/lib/Plugins/libopencvplugin.@OPENCV_PLUGIN_SOVERSION@.dylib"
                              IMPORTED_SONAME "libopencvplugin.@OPENCV_PLUGIN_SOVERSION@.dylib")
    else()
        SET_TARGET_PROPERTIES(opencvplugin PROPERTIES
                              IMPORTED_LOCATION "${_IMPORT_PREFIX}/lib/Plugins/libopencvplugin.so.@OPENCV_PLUGIN_SOVERSION@"
                              IMPORTED_SONAME "libopencvplugin.so.@OPENCV_PLUGIN_SOVERSION@")
    endif()
    SET_TARGET_PROPERTIES(opencvplugin PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "workspace")

    # Commands beyond this point should not need to know the version.
    SET(CMAKE_IMPORT_FILE_VERSION)
endif()
UNSET(opencvplugin_location)

CMAKE_POLICY(POP)
