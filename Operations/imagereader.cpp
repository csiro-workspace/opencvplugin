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

#include "imagereader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace CSIRO
{

namespace OpenCV
{
    /**
     * \internal
     */
    class ImageReaderImpl
    {
        // Allow string translation to work properly
        Q_DECLARE_TR_FUNCTIONS(CSIRO::OpenCV::ImageReaderImpl)

    public:
        ImageReader&  op_;

        // Data objects
        CSIRO::DataExecution::TypedObject<QString>  dataFileName_;
        CSIRO::DataExecution::TypedObject<cv::Mat>  dataOutputMat_;
        
        // Inputs and outputs
        CSIRO::DataExecution::InputScalar inputFileName_;
        CSIRO::DataExecution::Output      outputMat_;
            
        ImageReaderImpl(ImageReader& op);

        bool  execute();
        void  logText(const QString& msg)   { op_.logText(msg); }
    };


    /**
     *
     */
    ImageReaderImpl::ImageReaderImpl(ImageReader& op) :
        op_(op),
        dataFileName_(),
        dataOutputMat_(),
        inputFileName_("File name", dataFileName_, op_),
        outputMat_("Mat", dataOutputMat_, op_)
    {
        inputFileName_.setPreferredWidget("CSIRO::Widgets::FileNameWidget");
    }


    /**
     *
     */
    bool ImageReaderImpl::execute()
    {
        QString& dataFileName = *dataFileName_;
        cv::Mat& matOut = *dataOutputMat_;
        
        // Resolve any workspace strings
        QString fileName = CSIRO::System::Utilities::downloadIfRemote(dataFileName, op_.getLabel());

        // Load mat
        matOut = cv::imread(fileName.toLatin1().constData(), -CV_LOAD_IMAGE_ANYDEPTH);

        // Check for success
        if (matOut.data == NULL) {
            logText("ERROR: Cannot open image '" + dataFileName + "'\n");
            return false;
        }

        // Display image info
        cv::Size size = matOut.size();
        QString depthString;
        switch (matOut.depth()) {
            case CV_8U: depthString = "8-bit unsigned integer"; break;
            case CV_8S: depthString = "8-bit signed integer"; break;
            case CV_16U: depthString = "16-bit unsigned integer"; break;
            case CV_16S: depthString = "16-bit signed integer"; break;
            case CV_32S: depthString = "32-bit signed integer"; break;
            case CV_32F: depthString = "32-bit floating point"; break;
            case CV_64F: depthString = "64-bit floating point"; break;
            default: depthString = "Unknown"; break;
        }

        logText(
            "Read image; width: " + QString::number(size.width) + 
            "; height: " + QString::number(size.height) + 
            "; channels: " + QString::number(matOut.channels()) + 
            "; " + depthString + "\n");

        return true;
    }

    /**
     *
     */
    ImageReader::ImageReader() :
        CSIRO::DataExecution::Operation(
            CSIRO::DataExecution::OperationFactoryTraits< ImageReader >::getInstance(),
            tr("OpenCV read image")) {
        pImpl_ = new ImageReaderImpl(*this);
    }

    /**
     *
     */
    ImageReader::~ImageReader() {
        delete pImpl_;
    }

    /**
     *
     */
    bool  ImageReader::execute() {
        return pImpl_->execute();
    }
}}

using namespace CSIRO::OpenCV;
DEFINE_WORKSPACE_OPERATION_FACTORY_NAMED(
    ImageReader, 
    CSIRO::OpenCV::OpenCVPlugin::getInstance(),
    CSIRO::DataExecution::Operation::tr("OpenCV"),
    "OpenCV ImageReader")

