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

/**
 * \file
 */

#ifndef CSIRO_DATAEXECUTION_MATTOQIMAGEADAPTOR_H
#define CSIRO_DATAEXECUTION_MATTOQIMAGEADAPTOR_H

#include "Workspace/DataExecution/DataObjects/typeadaptor.h"
#include "Workspace/DataExecution/DataObjects/typeadaptorfactory.h"


namespace CSIRO
{

namespace OpenCV
{
    /**
     * \brief Adapts a cv::Mat to a QImage
     */
    class MatToQImageAdaptor : public DataExecution::TypeAdaptor
    {
    public:
        /**
         * \brief Nest factory class of MatToQImageAdaptor
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

#endif // CSIRO_DATAEXECUTION_MATTOQIMAGEADAPTOR_H

