
#ifndef QMITKTRANSFERFUNCTIONWIDGET_H
#define QMITKTRANSFERFUNCTIONWIDGET_H

#include "ui_QmitkTransferFunctionWidget.h"

#include <mitkCommon.h>

#include <QWidget>

#include <mitkDataTreeNode.h>
#include <mitkTransferFunctionProperty.h>

class QMITKEXT_EXPORT QmitkTransferFunctionWidget : public QWidget, public Ui::QmitkTransferFunctionWidget
{

  Q_OBJECT

  public:

    QmitkTransferFunctionWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~QmitkTransferFunctionWidget () ;

	  void SetDataTreeNode(mitk::DataTreeNode* node);

  public slots:

	  void SetXValueScalar();
	  void SetYValueScalar();
	  void SetXValueGradient();
	  void SetYValueGradient();
	  void SetXValueColor();
	 
	  void OnUpdateCanvas();

  protected:
  
    mitk::TransferFunctionProperty::Pointer tfpToChange;
};
#endif
