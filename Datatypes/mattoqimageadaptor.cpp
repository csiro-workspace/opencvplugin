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

#include <QtGlobal>
#include <QImage>

#include "Workspace/DataExecution/DataObjects/datafactorytraits.h"
#include "Workspace/DataExecution/DataObjects/dataobject.h"

#include "Workspace/Application/builtinplugin.h"

#include "mattoqimageadaptor.h"
#include "cvtypes.h"


namespace CSIRO
{
    using namespace Application;
    using namespace DataExecution;

namespace OpenCV
{
   
    /**
     *
     */
    const MatToQImageAdaptor::Factory& MatToQImageAdaptor::Factory::getInstance()
    {
        static MatToQImageAdaptor::Factory factory;
        return factory;
    }


    /**
     *
     */
    DataFactory&  MatToQImageAdaptor::Factory::getSrcTypeFactory() const
    {
        return DataFactoryTraits<cv::Mat>::getInstance();
    }


    /**
     *
     */
    const DataFactory&  MatToQImageAdaptor::Factory::getDestTypeFactory() const
    {
        return DataFactoryTraits<QImage>::getInstance();
    }


    /**
     *
     */
    TypeAdaptor*  MatToQImageAdaptor::Factory::create() const
    {
        return new MatToQImageAdaptor;
    }


    /**
     *
     */
    void  MatToQImageAdaptor::Factory::destroy(DataExecution::TypeAdaptor* a) const
    {
        assert(a);
        assert(&a->getFactory() == &getInstance());
        delete a;
    }


    /**
     *
     */
    const Application::WorkspacePlugin&  MatToQImageAdaptor::Factory::getPlugin() const
    {
        return BuiltinPlugin::getInstance();
    }


    /**
     *
     */
    bool  MatToQImageAdaptor::adapt(DataExecution::DataObject& src, DataExecution::DataObject& dest, bool copy)
    {
        Q_UNUSED(copy);

        // Must always have data at the source if we want to adapt it
        if (!src.hasData())
            return false;

        // Check the source and destination data types
        assert(&getFactory().getSrcTypeFactory() == &src.getFactory());
        assert(&getFactory().getDestTypeFactory() == &dest.getFactory());
        assert(&src.getFactory() == &DataFactoryTraits<QDateTime>::getInstance());
        assert(&dest.getFactory() == &DataFactoryTraits<QString>::getInstance());

        dest.ensureHasData();
        dest.getRawData<QImage>() = convertMatToQImage(src.getRawData<cv::Mat>());
        return true;
    }


    /**
     *
     */
    const MatToQImageAdaptor::Factory&  MatToQImageAdaptor::getFactory() const
    {
        return MatToQImageAdaptor::Factory::getInstance();
    }

}}  // end of namespaces

