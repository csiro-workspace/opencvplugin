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

#ifndef CSIRO_OPENCV_MATWIDGET_H
#define CSIRO_OPENCV_MATWIDGET_H

#include <QWidget>

#include "opencvplugin.h"

namespace cv
{
    class Mat;
}

namespace CSIRO
{

namespace OpenCV
{


    class MatWidgetImpl;

    /**
     * \brief cv::Mat viewer
     */
    class CSIRO_OPENCV_API MatWidget : public QWidget
    {
        Q_OBJECT
        
        // Uncomment the line below for large widgets that should be collapsed by default
        // in Workspace's Operation Editor tree view. The READ value of this property
        // isn't used (but is required by Qt), we simply check if the property exists.
        //Q_PROPERTY(bool collapseInIOTree READ isVisible())

        MatWidgetImpl*  pImpl_;

    public:
        MatWidget(QWidget* parent = 0);
        virtual ~MatWidget();

        bool updateWidget(const cv::Mat& data);
        bool updateData(cv::Mat& data);

    signals:
        void widgetUpdated();
    };
}}

#endif
