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

project(OPENCV_DESIGNER)

if (USE_QT5)
    find_package(Qt5Core)
    find_package(Qt5Widgets)
    find_package(Qt5Designer)
    set(QT_LIBRARIES Qt5::Core;Qt5::Widgets;Qt5::Designer)
else()
    find_package(Qt4 COMPONENTS QtCore QtGui QtDesigner)
    include(${QT_USE_FILE})
endif()

set(OPENCV_DESIGNER_HEADERS
    ${OPENCV_DESIGNER_SOURCE_DIR}/opencvplugindesigner_api.h
    ${OPENCV_DESIGNER_SOURCE_DIR}/opencvplugindesigner.h
)

set(OPENCV_DESIGNER_MOC_HEADERS
    ${OPENCV_DESIGNER_SOURCE_DIR}/opencvplugindesigner.h
)

set(OPENCV_DESIGNER_SOURCES
    ${OPENCV_DESIGNER_SOURCE_DIR}/opencvplugindesigner.cpp
)

if (USE_QT5)
    set(CMAKE_AUTOMOC ON)
else()
    qt4_wrap_cpp(OPENCV_DESIGNER_MOC_SOURCES ${OPENCV_DESIGNER_MOC_HEADERS})
endif()

add_library(opencvplugindesigner ${OPENCV_DESIGNER_SOURCES} ${OPENCV_DESIGNER_MOC_SOURCES} ${OPENCV_DESIGNER_HEADERS})
target_link_libraries(opencvplugindesigner opencvplugin workspace ${QT_LIBRARIES})

set_target_properties(opencvplugindesigner PROPERTIES
    DEFINE_SYMBOL CSIRO_OPENCV_OPENCVPLUGINDESIGNER_EXPORTS
    VERSION ${OPENCV_PLUGIN_VERSION}
    SOVERSION ${OPENCV_PLUGIN_SOVERSION}
)
setTargetOutputDirectory(opencvplugindesigner ${CSIRO_INSTALL_AREA}/plugins/designer)

foreach(inFile ${OPENCV_DESIGNER_HEADERS})
    get_filename_component(TARGET_INCLUDE_FILE ${inFile} NAME)
    postLinkCopy(opencvplugindesigner
                 ${inFile}
                 ${CSIRO_INSTALL_AREA}/include/OpenCV/Designer/${TARGET_INCLUDE_FILE})
endforeach(inFile)

source_group("Moc Source Files" FILES ${OPENCV_DESIGNER_MOC_SOURCES})

