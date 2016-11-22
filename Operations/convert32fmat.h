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

#ifndef CSIRO_OPENCV_CONVERT32FMAT_H
#define CSIRO_OPENCV_CONVERT32FMAT_H

#include <cassert>

#include "Workspace/DataExecution/DataObjects/typedobject.h"
#include "Workspace/DataExecution/DataObjects/datafactorytraits.h"
#include "Workspace/DataExecution/DataObjects/typeddatafactory.h"
#include "Workspace/DataExecution/InputOutput/inputscalar.h"
#include "Workspace/DataExecution/InputOutput/inputarray.h"
#include "Workspace/DataExecution/InputOutput/output.h"
#include "Workspace/DataExecution/Operations/typedoperationfactory.h"
#include "Workspace/DataExecution/Operations/operation.h"
#include "Workspace/DataExecution/Operations/operationfactorytraits.h"

#include "opencvplugin.h"

namespace CSIRO
{

namespace OpenCV
{
    class Convert32fMatImpl;

    /**
     * \brief Converts CV_32F to a 0->1 range
     */
    class CSIRO_OPENCV_API Convert32fMat : public DataExecution::Operation
    {
        // Allow string translation to work properly
        Q_DECLARE_TR_FUNCTIONS(CSIRO::OpenCV::Convert32fMat)

        Convert32fMatImpl*  pImpl_;

        // Prevent copy and assignment - these should not be implemented
        Convert32fMat(const Convert32fMat&);
        Convert32fMat& operator=(const Convert32fMat&);

    protected:
        virtual bool  execute();

    public:
        Convert32fMat();
        virtual ~Convert32fMat();
    };
}}

DECLARE_WORKSPACE_OPERATION_FACTORY(CSIRO::OpenCV::Convert32fMat, CSIRO_OPENCV_API)

#endif

