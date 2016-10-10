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

#include "OpenCV/opencvplugin.h"

#include "cvtypes.h"

DEFINE_WORKSPACE_DATA_FACTORY(cv::Mat, CSIRO::OpenCV::OpenCVPlugin::getInstance())
DEFINE_WORKSPACE_DATA_FACTORY(cv::Point2f, CSIRO::OpenCV::OpenCVPlugin::getInstance())
DEFINE_WORKSPACE_DATA_FACTORY(cv::Point3f, CSIRO::OpenCV::OpenCVPlugin::getInstance())
DEFINE_WORKSPACE_DATA_FACTORY(std::vector<cv::Point2f>, CSIRO::OpenCV::OpenCVPlugin::getInstance())
DEFINE_WORKSPACE_DATA_FACTORY(std::vector<cv::Point3f>, CSIRO::OpenCV::OpenCVPlugin::getInstance())

#if CV_MAJOR_VERSION > 2
DEFINE_WORKSPACE_DATA_FACTORY(cv::UMat, CSIRO::OpenCV::OpenCVPlugin::getInstance())
#endif

namespace CSIRO
{

namespace OpenCV
{

QImage convertMatToQImage(const cv::Mat& srcImage)
{
	QImage result;
    
    switch ( srcImage.type() )
    {            
         // 8-bit, 4 channel
         case CV_8UC4:         
			result = QImage(srcImage.data, srcImage.cols, srcImage.rows, (int)srcImage.step, QImage::Format_RGB32).rgbSwapped();
			break;

         // 8-bit, 3 channel
		 case CV_8UC3:         
			result = QImage(srcImage.data, srcImage.cols, srcImage.rows, (int)srcImage.step, QImage::Format_RGB888).rgbSwapped();
			break;

		 // 8-bit, 1 channel
		 case CV_8UC1:
            result = QImage(srcImage.data, srcImage.cols, srcImage.rows, (int)srcImage.step, QImage::Format_Grayscale8).copy();
            break;
            
        default:
			OpenCVPlugin::getInstance().logText(
                "ERROR: Cannot convert OpenCV image to QImage - cv::Mat image type (" + 
                QString::number(srcImage.type()) + 
                ") not supported\n");
            break;		
	} 

    return result;
}

cv::Mat convertQImageToMat(QImage srcImage)
{
	cv::Mat result;

	if (srcImage.hasAlphaChannel())
    {
        if (srcImage.format() != QImage::Format_ARGB32)
        {
            srcImage = srcImage.convertToFormat(QImage::Format_ARGB32);
        }
        
        result = cv::Mat(srcImage.height(), srcImage.width(), CV_8UC4, srcImage.bits(), srcImage.bytesPerLine());
    }
	else if (srcImage.format() != QImage::Format_RGB888) 
	{ 
        srcImage = srcImage.convertToFormat(QImage::Format_RGB888);
        result = cv::Mat(srcImage.height(), srcImage.width(), CV_8UC3, srcImage.bits(), srcImage.bytesPerLine());
	}

	return result.clone(); // deep copy the data
}

}}
