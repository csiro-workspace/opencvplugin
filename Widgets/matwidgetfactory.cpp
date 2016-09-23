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
#include <limits>

#include "Workspace/Application/builtinplugin.h"
#include "Workspace/Widgets/namepath.h"
#include "Workspace/DataExecution/DataObjects/datafactorytraits.h"

#include "opencvplugin.h"
#include "matwidget.h"
#include "matwidgetfactory.h"
#include "matwidgetconnector.h"

namespace CSIRO
{

namespace OpenCV
{



    /**
     *
     */
    MatWidgetFactory&  MatWidgetFactory::getInstance()
    {
        static MatWidgetFactory  factory;
        return factory;
    }


    /**
     *
     */
    const QMetaObject&  MatWidgetFactory::getQWidgetMetaObject() const
    {
        return MatWidget::staticMetaObject;
    }


    /**
     *
     */
    const CSIRO::DataExecution::DataFactory&  MatWidgetFactory::getDataFactory() const
    {
        return CSIRO::DataExecution::DataFactoryTraits<cv::Mat>::getInstance();
    }


    /**
     *
     */
    QWidget&  MatWidgetFactory::createWidgetImpl(QWidget* parent) const
    {
        return *(new MatWidget(parent));
    }


    /**
     *
     */
    CSIRO::Widgets::QWidgetConnector&  MatWidgetFactory::createWidgetConnectorImpl(QWidget& widget, const CSIRO::Widgets::NamePath& namePath) const
    {
        return *new MatWidgetConnector(widget, namePath);
    }
}}

