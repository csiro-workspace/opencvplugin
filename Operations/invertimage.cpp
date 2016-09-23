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

#include "invertimage.h"

namespace CSIRO
{

namespace OpenCV
{
    /**
     * \internal
     */
    class InvertImageImpl
    {
        // Allow string translation to work properly
        Q_DECLARE_TR_FUNCTIONS(CSIRO::OpenCV::InvertImageImpl)

    public:
        InvertImage&  op_;

        // Data objects
        CSIRO::DataExecution::TypedObject<cv::Mat>  dataInputMat_;
        CSIRO::DataExecution::TypedObject<cv::Mat>  dataOutputMat_;
        
        // Inputs and outputs
        CSIRO::DataExecution::InputScalar inputMat_;
        CSIRO::DataExecution::Output      outputMat_;
            
        InvertImageImpl(InvertImage& op);

        bool  execute();
        void  logText(const QString& msg)   { op_.logText(msg); }
    };


    /**
     *
     */
    InvertImageImpl::InvertImageImpl(InvertImage& op) :
        op_(op),
        dataInputMat_(),
        dataOutputMat_(),
        inputMat_("Mat", dataInputMat_, op_),
        outputMat_("Mat", dataOutputMat_, op_)
    {
    }


    /**
     *
     */
    bool InvertImageImpl::execute()
    {
        cv::Mat& matIn = *dataInputMat_;
        cv::Mat& matOut = *dataOutputMat_;

        // Invert mat 
        cv::bitwise_not(matIn, matOut);

        return true;
    }

    /**
     *
     */
    InvertImage::InvertImage() :
        CSIRO::DataExecution::Operation(
            CSIRO::DataExecution::OperationFactoryTraits< InvertImage >::getInstance(),
            tr("OpenCV invert image")) {
        pImpl_ = new InvertImageImpl(*this);
    }

    /**
     *
     */
    InvertImage::~InvertImage() {
        delete pImpl_;
    }

    /**
     *
     */
    bool  InvertImage::execute() {
        return pImpl_->execute();
    }
}}

using namespace CSIRO::OpenCV;
DEFINE_WORKSPACE_OPERATION_FACTORY_NAMED(
    InvertImage,
    CSIRO::OpenCV::OpenCVPlugin::getInstance(),
    CSIRO::DataExecution::Operation::tr("OpenCV"),
    "OpenCV InvertImage")
