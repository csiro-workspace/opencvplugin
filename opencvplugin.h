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

#ifndef CSIRO_OPENCV_OPENCVPLUGIN_H
#define CSIRO_OPENCV_OPENCVPLUGIN_H

#include "Workspace/Application/workspaceplugin.h"

#include "opencvplugin_api.h"

namespace CSIRO
{

namespace OpenCV
{
    class OpenCVPluginImpl;

    /**
     * \brief Plugin to expose OpenCV for use in Workspace
     */
    class CSIRO_OPENCV_API OpenCVPlugin : public CSIRO::Application::WorkspacePlugin
    {
        OpenCVPluginImpl*  pImpl_;

        OpenCVPlugin();
        ~OpenCVPlugin();

        // Prevent copying and assignment
        OpenCVPlugin(const OpenCVPlugin&);
        OpenCVPlugin& operator=(const OpenCVPlugin&);

    protected:
        virtual const CSIRO::DataExecution::DataFactory*       getAliasedDataFactory(const QString& dataType) const;
        virtual const CSIRO::DataExecution::OperationFactory*  getAliasedOperationFactory(const QString& opType) const;

    public:
        static OpenCVPlugin&  getInstance();
        
        QStringList  getCustomWidgetPaths() const;

        virtual bool  setup();
    };
}}

#endif
