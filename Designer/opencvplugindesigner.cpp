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

#include <QtPlugin>

#include "opencvplugindesigner.h"

namespace CSIRO
{

namespace OpenCV
{
    /**
     *
     */
    OpenCVPluginDesigner::OpenCVPluginDesigner(QObject* parent) :
        QObject(parent)
    {
        // Add your own designer interfaces here, as per the below line.
        // designerInterfaces_.append(new CustomWidgetDesigner(this));
    }


    /**
     *
     */
    QList<QDesignerCustomWidgetInterface*> OpenCVPluginDesigner::customWidgets() const
    {
        return designerInterfaces_;
    }

}}

#ifndef USE_QT5
Q_EXPORT_PLUGIN2(opencvplugin, CSIRO::OpenCV::OpenCVPluginDesigner)
#endif
