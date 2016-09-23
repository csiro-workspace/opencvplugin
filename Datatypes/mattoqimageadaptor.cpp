/*=========================================================================

  Revision:       $Revision: 7784 $
  Last changed:   $Date: 2016-01-12 12:07:31 +1100 (Tue, 12 Jan 2016) $

  Copyright 2016 by:

    Commonwealth Scientific and Industrial Research Organisation (CSIRO)
    
    This file is licensed by CSIRO under the copy of the CSIRO Binary  
    License Agreement included with the file when downloaded or obtained 
    from CSIRO (including any Supplementary License).  If no copy was 
    included, you must obtain a new copy of the Software from CSIRO before 
    any use is permitted.

    For further information, contact: workspace@csiro.au

  This copyright notice must be included with all copies of the source code.

===========================================================================*/

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

