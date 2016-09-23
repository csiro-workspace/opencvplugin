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

#ifndef CSIRO_OPENCV_OPENCVPLUGINDESIGNER_H
#define CSIRO_OPENCV_OPENCVPLUGINDESIGNER_H

#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
#include <QDesignerCustomWidgetCollectionInterface>
#else
#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>
#endif

#include "opencvplugindesigner_api.h"

namespace CSIRO
{

namespace OpenCV
{
    /**
     * \brief WorkspacePlugin singleton class for this module.
     */
    class CSIRO_OPENCV_OPENCVPLUGINDESIGNER_API OpenCVPluginDesigner :
        public QObject,
        public QDesignerCustomWidgetCollectionInterface
    {
        Q_OBJECT
#ifdef USE_QT5
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif
        Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

        QList<QDesignerCustomWidgetInterface*>  designerInterfaces_;

    public:
        OpenCVPluginDesigner(QObject* parent = 0);

        virtual QList<QDesignerCustomWidgetInterface*>  customWidgets() const;
    };

}}

#endif

