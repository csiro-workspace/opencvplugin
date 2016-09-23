/*============================================================================

  Copyright 2016 by:

    Commonwealth Scientific and Industrial Research Organisation (CSIRO)
    
    This file is licensed by CSIRO under the copy of the CSIRO Open Source
    Software License Agreement (variation of the BSD / MIT License) included
    with the file.

    As a condition of this license, you agree that where you make any 
    adaptations, modifications, further developments, or additional features 
    available to CSIRO or the public in connection with your access to the 
    Software, you do so on the terms of the BSD 3-Clause License template,
    a copy available at: http://opensource.org/licenses/BSD-3-Clause

    For further information, contact the CSIRO Workspace Team:
    workspace@csiro.au

  This copyright notice must be included with all copies of the source code.

============================================================================*/

/**
 * \file
 */

#ifndef CSIRO_OPENCV_CVTYPES_H
#define CSIRO_OPENCV_CVTYPES_H

#include <vector>

#include <opencv2/opencv.hpp>

#include <QImage>

#include "OpenCV/opencvplugin_api.h"

#include "Workspace/DataExecution/DataObjects/typedobject.h"
#include "Workspace/DataExecution/DataObjects/datafactorytraits.h"
#include "Workspace/DataExecution/DataObjects/typeddatafactory.h"

DECLARE_WORKSPACE_DATA_FACTORY(cv::Mat, CSIRO_OPENCV_API)
DECLARE_WORKSPACE_DATA_FACTORY(cv::Point2f, CSIRO_OPENCV_API)
DECLARE_WORKSPACE_DATA_FACTORY(cv::Point3f, CSIRO_OPENCV_API)
DECLARE_WORKSPACE_DATA_FACTORY(std::vector<cv::Point2f>, CSIRO_OPENCV_API)
DECLARE_WORKSPACE_DATA_FACTORY(std::vector<cv::Point3f>, CSIRO_OPENCV_API)

#if CV_MAJOR_VERSION > 2
DECLARE_WORKSPACE_DATA_FACTORY(cv::UMat, CSIRO_OPENCV_API)
#endif

namespace CSIRO
{
namespace OpenCV
{
    cv::Mat convertQImageToMat(QImage srcImage);
    QImage convertMatToQImage(const cv::Mat& srcImage);
}}

#endif

