#include "QmitkTransferFunctionWidget.h"

#include <mitkTransferFunctionProperty.h>

QmitkTransferFunctionWidget::QmitkTransferFunctionWidget(QWidget* parent,
    Qt::WindowFlags f) :
  QWidget(parent, f)
{
  this->setupUi(this);
                                                
  // signals and slots connections
  connect(m_XEditScalarOpacity, SIGNAL(returnPressed()), this, SLOT(SetXValueScalar()));
  connect(m_YEditScalarOpacity, SIGNAL(returnPressed()), this, SLOT(SetYValueScalar()));

  connect(m_XEditGradientOpacity, SIGNAL(returnPressed()), this, SLOT(SetXValueGradient()));
  connect(m_YEditGradientOpacity, SIGNAL(returnPressed()), this, SLOT(SetYValueGradient()));

  connect(m_XEditColor, SIGNAL(returnPressed()), this, SLOT(SetXValueColor()));

  m_ScalarOpacityFunctionCanvas->SetQLineEdits(m_XEditScalarOpacity, m_YEditScalarOpacity);
  m_GradientOpacityCanvas->SetQLineEdits(m_XEditGradientOpacity, m_YEditGradientOpacity);
  m_ColorTransferFunctionCanvas->SetQLineEdits(m_XEditColor, 0);
}

QmitkTransferFunctionWidget::~QmitkTransferFunctionWidget()
{
}

void QmitkTransferFunctionWidget::SetDataTreeNode(mitk::DataTreeNode* node)
{
  if (node)
  {
    tfpToChange = dynamic_cast<mitk::TransferFunctionProperty*>(node->GetProperty("TransferFunction"));
    
    if(!tfpToChange)
    {
      if (! dynamic_cast<mitk::Image*>(node->GetData()))
      {
        LOG_WARN << "QmitkTransferFunctionWidget::SetDataTreeNode called with non-image node";
        goto turnOff;
      }
      
      node->SetProperty("TransferFunction", tfpToChange = mitk::TransferFunctionProperty::New() );
      dynamic_cast<mitk::TransferFunctionProperty*>(node->GetProperty("TransferFunction"));
    }

    mitk::TransferFunction::Pointer tf = tfpToChange->GetValue();

    if( mitk::Image* image = dynamic_cast<mitk::Image*>( node->GetData() ) )
      tf->InitializeByItkHistogram( image->GetScalarHistogram() );
          
    OnUpdateCanvas();

    m_ScalarOpacityFunctionCanvas->setEnabled(true);
    m_GradientOpacityCanvas->setEnabled(true);
    m_ColorTransferFunctionCanvas->setEnabled(true);

    return; 
  }

  turnOff:

  m_ScalarOpacityFunctionCanvas->setEnabled(false);
  m_GradientOpacityCanvas->setEnabled(false);
  m_ColorTransferFunctionCanvas->setEnabled(false);
  tfpToChange = 0;
}


void QmitkTransferFunctionWidget::OnUpdateCanvas()
{
  if(tfpToChange.IsNull())
    return;

  mitk::TransferFunction::Pointer tf = tfpToChange->GetValue();

  if(tf.IsNull())
    return;

  if (m_ScalarOpacityFunctionCanvas)
  {
    m_ScalarOpacityFunctionCanvas->SetPiecewiseFunction( tf->GetScalarOpacityFunction() );
    m_ScalarOpacityFunctionCanvas->SetHistogram( tf->GetHistogram() );
    m_ScalarOpacityFunctionCanvas->SetMin( tf->GetMin() );
    m_ScalarOpacityFunctionCanvas->SetMax( tf->GetMax() );

    m_MinLabel_2->setText(QString::number(m_ScalarOpacityFunctionCanvas->GetMin()));
    m_MaxLabel_2->setText(QString::number(m_ScalarOpacityFunctionCanvas->GetMax()));
  }
  if (m_GradientOpacityCanvas)
  {
    m_GradientOpacityCanvas->SetPiecewiseFunction( tf->GetGradientOpacityFunction() );
    m_GradientOpacityCanvas->SetHistogram( tf->GetHistogram() );
    m_GradientOpacityCanvas->SetMin( tf->GetMin() );
    m_GradientOpacityCanvas->SetMax( tf->GetMax() );

    m_MinLabelGO->setText(QString::number(m_GradientOpacityCanvas->GetMin()));
    m_MaxLabelGO->setText(QString::number(m_GradientOpacityCanvas->GetMax()));
  }
  if (m_ColorTransferFunctionCanvas)
  {
    m_ColorTransferFunctionCanvas->SetColorTransferFunction( tf->GetColorTransferFunction() );
    m_ColorTransferFunctionCanvas->SetMin( tf->GetMin() );
    m_ColorTransferFunctionCanvas->SetMax( tf->GetMax() );

    m_MinLabel  ->setText(QString::number(m_ColorTransferFunctionCanvas->GetMin()));
    m_MaxLabel  ->setText(QString::number(m_ColorTransferFunctionCanvas->GetMax()));
  }

  m_ScalarOpacityFunctionCanvas->update();
  m_GradientOpacityCanvas->update();
  m_ColorTransferFunctionCanvas->update();
}

void QmitkTransferFunctionWidget::SetXValueScalar()
{
  m_ScalarOpacityFunctionCanvas->SetX(m_XEditScalarOpacity->text().toFloat());
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void QmitkTransferFunctionWidget::SetYValueScalar()
{
  m_ScalarOpacityFunctionCanvas->SetY(m_YEditScalarOpacity->text().toFloat());
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void QmitkTransferFunctionWidget::SetXValueGradient()
{
  m_GradientOpacityCanvas->SetX(m_XEditGradientOpacity->text().toFloat());
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void QmitkTransferFunctionWidget::SetYValueGradient()
{
  m_GradientOpacityCanvas->SetY(m_YEditGradientOpacity->text().toFloat());
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void QmitkTransferFunctionWidget::SetXValueColor()
{
  m_ColorTransferFunctionCanvas->SetX(m_XEditColor->text().toFloat());
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}





