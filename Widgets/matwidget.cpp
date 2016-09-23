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

#include <QScopedPointer>

#include "Workspace/DataExecution/DataObjects/datafactory.h"
#include "Workspace/DataExecution/InputOutput/iobase.h"
#include "Workspace/Widgets/widgetmanager.h"

#include "opencvplugin.h"
#include "cvtypes.h"
#include "matwidget.h"
#include "ui_matwidget.h"

namespace CSIRO
{

namespace OpenCV
{
    using namespace CSIRO::OpenCV;

    /**
     * \internal
     */
    class MatWidgetImpl
    {
    public:
        MatWidget&                      owner_;
        QScopedPointer<Ui::MatWidget>   ui_;

        MatWidgetImpl(MatWidget& owner) :
            owner_(owner),
            ui_(new Ui::MatWidget)
        {
            ui_->setupUi(&owner);
        }

        bool updateWidget(const cv::Mat& data);
        bool updateData(cv::Mat& data);
    };


    /**
     * 
     */
    bool MatWidgetImpl::updateWidget( const cv::Mat& data )
    {
        ui_->imageWidget->setImage(convertMatToQImage(data));
        return true;
    }


    /**
     * 
     */
    bool MatWidgetImpl::updateData( cv::Mat& data )
    {
        // =================================== //
        // Update the data argument with data  //
        // from your widgets controls here     //
        // =================================== //

        return true;
    }


    //====================================//


    /**
     *
     */
    MatWidget::MatWidget(QWidget* parent) :
        QWidget(parent),
        pImpl_(new MatWidgetImpl(*this))
    {
        bool connected = true;

        // ====================================== //
        // Connect up your signals and slots here //
        // (see examples below)                   //
        // ====================================== //
        //connected = connect(pImpl_->ui_->addButton, SIGNAL(clicked()), this, SIGNAL(widgetUpdated()));
        assert(connected);
    }


    /**
     * 
     */
    MatWidget::~MatWidget()
    {
        delete pImpl_;
    }


    /**
     * 
     */
    bool MatWidget::updateWidget( const cv::Mat& data )
    {
        return pImpl_->updateWidget(data);
    }


    /**
     * 
     */
    bool MatWidget::updateData( cv::Mat& data )
    {
        return pImpl_->updateData(data);
    }

}}
