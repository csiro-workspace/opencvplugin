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

#include <QtTest/QtTest>

#include "Workspace/testcommon.h"
#include "Workspace/Application/LanguageUtils/stringhelpers.h"
#include "Workspace/Application/logmanager.h"
#include "Workspace/Application/pluginmanager.h"
#include "Workspace/DataExecution/Operations/operationfactorytraits.h"
#include "Workspace/DataExecution/Execution/operationrunner.h"
#include "Workspace/DataExecution/InputOutput/inputarray.h"
#include "Workspace/DataExecution/InputOutput/inputscalar.h"

#include "OpenCV/cvtypes.h"
#include "OpenCV/Operations/imagereader.h"


namespace CSIRO
{

namespace Testing
{
    using namespace Application;
    using namespace DataExecution;
    using namespace OpenCV;
    
    class TestImageReader : public QObject
    {
        Q_OBJECT

    // The testing framework will run through and execute each Qt Slot on this class as a test
    private slots:

        void  initTestCase()
        {
            // Any global init stuff can go here
        }
        
        void  doTest1()
        {
            // Test and individual operation
            DataExecution::OperationRunner opRunner(OperationFactoryTraits<OpenCV::ImageReader>::getInstance());
           
            // Set inputs
            opRunner.setInputValue<QString>("File name", "http://melbourne-things-to-do.com.au/wp-content/uploads/2015/03/Melbourne-2.jpg");
            
            // Run the operation
            QVERIFY(opRunner.runOnceAndWait());
            
            // Check outputs
            cv::Mat& result = opRunner.getOutputValue<cv::Mat>("Mat");
            QVERIFY2(result.size().width == 1732, "Wrong width");
            QVERIFY2(result.size().height == 1155, "Wrong height");
            QVERIFY2(result.channels() == 3, "Wrong number of channels");
        }

        void  doTest2()
        {
            // Test a more complex workflow
            QString testWorkflow = QString(TOSTRING(TEST_DIR)) + "/test_opencv.wsx";
            DataExecution::OperationRunner opRunner(testWorkflow);
            
            // Run the workflow
            QVERIFY(opRunner.runOnceAndWait());
            
            // Check outputs
            cv::Mat& result = opRunner.getGlobalNameValue<cv::Mat>("invertedAndResized");
            QVERIFY2(result.size().width == 1732 * .5, "Wrong width");
            QVERIFY2(result.size().height == 1155, "Wrong height");
            QVERIFY2(result.channels() == 3, "Wrong number of channels");
        }        
    };
}}

QTEST_MAIN(CSIRO::Testing::TestImageReader)
#include "test_imagereader.moc"
