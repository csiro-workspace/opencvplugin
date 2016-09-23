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

#ifndef CSIRO_OPENCV_MATWIDGET_FACTORY_H
#define CSIRO_OPENCV_MATWIDGET_FACTORY_H

#include "Workspace/Widgets/widgetfactory.h"
#include "opencvplugin.h"

namespace CSIRO
{
namespace Widgets
{
    class NamePath;
    class QWidgetConnector;
}
namespace DataExecution
{
    class DataFactory;
}
}

namespace CSIRO
{

namespace OpenCV
{


    /**
     *
     */
    class CSIRO_OPENCV_API MatWidgetFactory : public CSIRO::Widgets::WidgetFactory
    {
        virtual QWidget&                            createWidgetImpl(QWidget* parent) const;
        virtual CSIRO::Widgets::QWidgetConnector&   createWidgetConnectorImpl(QWidget& widget, const CSIRO::Widgets::NamePath& namePath) const;

    public:
        static MatWidgetFactory&  getInstance();

        virtual const QMetaObject&  getQWidgetMetaObject() const;
        virtual const CSIRO::DataExecution::DataFactory&  getDataFactory() const;
  };
}}

#endif
