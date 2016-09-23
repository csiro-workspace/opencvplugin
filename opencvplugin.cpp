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

#include <QString>
#include <QStringList>

#include "Workspace/DataExecution/DataObjects/datafactorytraits.h"
#include "Workspace/DataExecution/Operations/operationfactorytraits.h"

#include "opencvplugin.h"

#include "cvtypes.h"

#include "Datatypes/mattoqimageadaptor.h"
#include "Datatypes/qimagetomatadaptor.h"

#include "Operations/invertimage.h"
#include "Operations/imagereader.h"

#include "Widgets/matwidgetfactory.h"


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace CSIRO
{

namespace OpenCV
{
    /**
     * \internal
     */
    class OpenCVPluginImpl
    {
    public:
        // You can add, remove or modify anything in here without
        // breaking binary compatibility. It starts as empty, but
        // leave it here in case at some time in the future you
        // want to add some data for your plugin without breaking
        // binary compatibility.
    };


    /**
     *
     */
    OpenCVPlugin::OpenCVPlugin() :
            CSIRO::Application::WorkspacePlugin("www.csiro.au/workspace/opencv",
                                                "OpenCV",
                                                TOSTRING(OPENCV_PLUGIN_VERSION))
    {
        pImpl_ = new OpenCVPluginImpl;
    }


    /**
     *
     */
    OpenCVPlugin::~OpenCVPlugin()
    {
        delete pImpl_;
    }


    /**
     * \return  The singleton instance of this plugin.
     */
    OpenCVPlugin&  OpenCVPlugin::getInstance()
    {
        // This is a Singleton pattern. There will only ever be one
        // instance of the plugin across the entire application.
        static OpenCVPlugin plugin;
        return plugin;
    }


    /**
     *
     */
    bool  OpenCVPlugin::setup()
    {
        // Add your data factories like this:
        addFactory(DataExecution::DataFactoryTraits<cv::Mat>::getInstance());
        addFactory(DataExecution::DataFactoryTraits<cv::Point2f>::getInstance());
        addFactory(DataExecution::DataFactoryTraits<cv::Point3f>::getInstance());
        addFactory(DataExecution::DataFactoryTraits<std::vector<cv::Point2f>>::getInstance());
        addFactory(DataExecution::DataFactoryTraits<std::vector<cv::Point3f>>::getInstance());

#if CV_MAJOR_VERSION > 2
        addFactory(DataExecution::DataFactoryTraits<cv::UMat>::getInstance());
#endif

        //// Add your operation factories like this:
        addFactory(DataExecution::OperationFactoryTraits<InvertImage>::getInstance());
        addFactory(DataExecution::OperationFactoryTraits<ImageReader>::getInstance());

        // Add your widget factories like this:
        addFactory(MatWidgetFactory::getInstance());

        addFactory(MatToQImageAdaptor::Factory::getInstance());
        addFactory(QImageToMatAdaptor::Factory::getInstance());

        return true;
    }


    /**
     *
     */
    const CSIRO::DataExecution::OperationFactory*  OpenCVPlugin::getAliasedOperationFactory(const QString& opType) const
    {
        // If you rename an operation, you can provide backwards
        // compatibility using something like this (don't forget to
        // include namespaces in the names if relevant):
        //if (opType == "SomeOperationName")
        //    return &CSIRO::DataExecution::OperationFactoryTraits<NewOperationName>::getInstance();

        // If you make use of opType, you can delete the following Q_UNUSED line
        Q_UNUSED(opType);

        // If we get here, opType is not something we renamed, so return a
        // a null pointer to tell the caller
        return static_cast<const CSIRO::DataExecution::OperationFactory*>(0);
    }


    /**
     *
     */
    const CSIRO::DataExecution::DataFactory*  OpenCVPlugin::getAliasedDataFactory(const QString& dataType) const
    {
        // If you rename a data type, you can provide backwards
        // compatibility using something like this (don't forget to
        // include namespaces in the names if relevant):
        //if (dataType == "SomeDataType")
        //    return &CSIRO::DataExecution::DataFactoryTraits<NewDataType>::getInstance();

        // If you make use of dataType, you can delete the following Q_UNUSED line
        Q_UNUSED(dataType);

        // If we get here, dataType is not something we renamed, so return a
        // a null pointer to tell the caller
        return static_cast<const CSIRO::DataExecution::DataFactory*>(0);
    }
    
    
    /**
     *
     */
    QStringList  OpenCVPlugin::getCustomWidgetPaths() const
    {
        QStringList result;
        result.push_back("widgets:OpenCV");
        return result;
    }
    
}}

#ifndef CSIRO_STATIC_BUILD
extern "C"
{
    CSIRO_EXPORTSPEC CSIRO::Application::WorkspacePlugin* getWorkspacePlugin()
    {
        return &CSIRO::OpenCV::OpenCVPlugin::getInstance();
    }
    
    /**
     *	\return The version string for the Workspace build we've been built against
     */
    CSIRO_EXPORTSPEC const char* builtAgainstWorkspace()
    {
        #define STRINGIFY(x) #x
        #define TOSTRING(x) STRINGIFY(x)
        return TOSTRING(CSIRO_WORKSPACE_VERSION_CHECK);
    }
}
#endif
