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

#ifndef CSIRO_DATAEXECUTION_QIMAGETOMATADAPTOR_H
#define CSIRO_DATAEXECUTION_QIMAGETOMATADAPTOR_H

#include "Workspace/DataExecution/DataObjects/typeadaptor.h"
#include "Workspace/DataExecution/DataObjects/typeadaptorfactory.h"


namespace CSIRO
{

namespace OpenCV
{
    /**
     * \brief Adapts a cv::Mat to a QImage
     */
    class QImageToMatAdaptor : public DataExecution::TypeAdaptor
    {
    public:
        /**
         * \brief Nest factory class of QImageToMatAdaptor
         */
        class Factory : public DataExecution::TypeAdaptorFactory
        {
        public:
            static const Factory& getInstance();

            virtual DataExecution::DataFactory&         getSrcTypeFactory() const;
            virtual const DataExecution::DataFactory&   getDestTypeFactory() const;
            virtual DataExecution::TypeAdaptor*         create() const;
            virtual void                                destroy(DataExecution::TypeAdaptor* a) const;
            virtual const Application::WorkspacePlugin& getPlugin() const;
        };

        virtual bool adapt(DataExecution::DataObject& src, DataExecution::DataObject& dest, bool copy);

        virtual const Factory&  getFactory() const;
    };
}
}  // end of namespaces

#endif // CSIRO_DATAEXECUTION_QIMAGETOMATADAPTOR_H

