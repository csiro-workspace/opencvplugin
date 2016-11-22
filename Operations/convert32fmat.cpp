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

#include "OpenCV/cvtypes.h"

#include "convert32fmat.h"

namespace CSIRO
{
    using namespace DataExecution;

namespace OpenCV
{
    /**
     * \internal
     */
    class Convert32fMatImpl
    {
        // Allow string translation to work properly
        Q_DECLARE_TR_FUNCTIONS(CSIRO::OpenCV::Convert32fMatImpl)

    public:
        Convert32fMat&  op_;

        // Data objects
        TypedObject<cv::Mat>  dataInputMat_;
        TypedObject<double>   dataRange_;
        TypedObject<cv::Mat>  dataOutputMat_;
        
        // Inputs and outputs
        InputScalar inputMat_;
        InputScalar inputRange_;
        Output      outputMat_;
            
        Convert32fMatImpl(Convert32fMat& op);

        bool  execute();
        void  logText(const QString& msg)   { op_.logText(msg); }
    };


    /**
     *
     */
    Convert32fMatImpl::Convert32fMatImpl(Convert32fMat& op) :
        op_(op),
        dataInputMat_(),
        dataRange_(1.0),
        dataOutputMat_(),
        inputMat_("Mat", dataInputMat_, op_),
        inputRange_("Range", dataRange_, op_),
        outputMat_("Mat", dataOutputMat_, op_)
    {
    }


    /**
     *
     */
    bool Convert32fMatImpl::execute()
    {
        dataInputMat_->convertTo(*dataOutputMat_, CV_32F, 1.0 / *dataRange_, 0);
        return true;
    }

    /**
     *
     */
    Convert32fMat::Convert32fMat() :
        CSIRO::DataExecution::Operation(
            CSIRO::DataExecution::OperationFactoryTraits< Convert32fMat >::getInstance(),
            tr("OpenCV convert CV_32f Mat")) 
    {
        pImpl_ = new Convert32fMatImpl(*this);
    }

    /**
     *
     */
    Convert32fMat::~Convert32fMat() {
        delete pImpl_;
    }

    /**
     *
     */
    bool  Convert32fMat::execute() {
        return pImpl_->execute();
    }
}}

using namespace CSIRO::OpenCV;
DEFINE_WORKSPACE_OPERATION_FACTORY_NAMED(
    Convert32fMat,
    CSIRO::OpenCV::OpenCVPlugin::getInstance(),
    CSIRO::DataExecution::Operation::tr("OpenCV"),
    "OpenCV Convert32fMat")
