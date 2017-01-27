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

#include <cassert>

#include "Workspace/DataExecution/InputOutput/iobase.h"
#include "Workspace/DataExecution/DataObjects/dataobject.h"
#include "Workspace/DataExecution/DataObjects/objectarray.h"
#include "Workspace/Widgets/namepath.h"

#include "opencvplugin.h"
#include "matwidget.h"
#include "matwidgetconnector.h"

namespace CSIRO
{

namespace OpenCV
{
    /**
     *
     */
    MatWidgetConnector::MatWidgetConnector(QWidget& widget, const CSIRO::Widgets::NamePath& namePath) :
        QWidgetConnector(widget, namePath)
    {
        MatWidget* typedWidget = qobject_cast<MatWidget*>(&widget);
        assert(typedWidget);

        connect(typedWidget, SIGNAL(widgetUpdated()), this, SLOT(requestUpdateData()));
    }


    /**
     *
     */
    void  MatWidgetConnector::updateWidget(CSIRO::DataExecution::DataObject& dataObject)
    {
        MatWidget* widget = qobject_cast<MatWidget*>(&getWidget());
        assert(widget);
        assert(&dataObject.getFactory() == &CSIRO::DataExecution::DataFactoryTraits<cv::Mat>::getInstance());
        if (dataObject.hasData())
            widget->updateWidget(dataObject.getRawData<cv::Mat>());
    }


    /**
     *
     */
    void  MatWidgetConnector::updateData(CSIRO::DataExecution::DataObject& dataObject)
    {
        MatWidget* widget = qobject_cast<MatWidget*>(&getWidget());
        assert(widget);
        assert(&dataObject.getFactory() == &CSIRO::DataExecution::DataFactoryTraits<cv::Mat>::getInstance());
        dataObject.ensureHasData();
        widget->updateData(dataObject.getRawData<cv::Mat>());
    }

#if CSIRO_WORKSPACE_VERSION_MAJOR >= 4
    /**
     *
     */
    void  MatWidgetConnector::setWidgetReadOnly(bool b) { }
#endif
}}

