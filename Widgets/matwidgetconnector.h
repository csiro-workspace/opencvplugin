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

#ifndef CSIRO_OPENCV_MATWIDGET_CONNECTOR_H
#define CSIRO_OPENCV_MATWIDGET_CONNECTOR_H

#include "Workspace/Widgets/qwidgetconnector.h"
#include "opencvplugin.h"

namespace CSIRO
{

namespace OpenCV
{


    /**
     *
     */
    class CSIRO_OPENCV_API MatWidgetConnector : public CSIRO::Widgets::QWidgetConnector
    {
        Q_OBJECT

        virtual  void  updateWidget(CSIRO::DataExecution::DataObject& dataObject);
        virtual  void  updateData(CSIRO::DataExecution::DataObject& dataObject);

    public:
        MatWidgetConnector(QWidget& widget, const CSIRO::Widgets::NamePath& namePath);

#if CSIRO_WORKSPACE_VERSION_MAJOR >= 4
        virtual  void  setWidgetReadOnly(bool b) override;
#endif
    };
}}

#endif
