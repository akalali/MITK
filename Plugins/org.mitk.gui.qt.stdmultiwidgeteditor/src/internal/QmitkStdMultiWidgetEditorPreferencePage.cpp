/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#include "QmitkStdMultiWidgetEditorPreferencePage.h"
#include <ui_QmitkStdMultiWidgetEditorPreferencePage.h>
#include <QmitkStdMultiWidgetEditor.h>

#include <berryIPreferencesService.h>
#include <berryPlatform.h>

#include <QColorDialog>

QmitkStdMultiWidgetEditorPreferencePage::QmitkStdMultiWidgetEditorPreferencePage()
  : m_Preferences(nullptr),
    m_Ui(new Ui::QmitkStdMultiWidgetEditorPreferencePage),
    m_Control(nullptr)
{
}

QmitkStdMultiWidgetEditorPreferencePage::~QmitkStdMultiWidgetEditorPreferencePage()
{
}

void QmitkStdMultiWidgetEditorPreferencePage::CreateQtControl(QWidget* parent)
{
  m_Control = new QWidget(parent);

  m_Ui->setupUi(m_Control);

  berry::IPreferencesService* prefService = berry::Platform::GetPreferencesService();
  Q_ASSERT(prefService);

  m_Preferences = prefService->GetSystemPreferences()->Node(QmitkStdMultiWidgetEditor::EDITOR_ID);

  QObject::connect( m_Ui->m_ColorButton1, SIGNAL( clicked() )
                    , this, SLOT( ColorChooserButtonClicked() ) );

  QObject::connect( m_Ui->m_ColorButton2, SIGNAL( clicked() )
                    , this, SLOT( ColorChooserButtonClicked() ) );

  QObject::connect( m_Ui->m_ResetButton, SIGNAL( clicked() )
                    , this, SLOT( ResetPreferencesAndGUI() ) );

  QObject::connect( m_Ui->m_RenderWindowDecorationColor, SIGNAL( clicked() )
                    , this, SLOT( ColorChooserButtonClicked() ) );

  QObject::connect( m_Ui->m_RenderWindowChooser, SIGNAL(activated(int) )
                    , this, SLOT( OnWidgetComboBoxChanged(int) ) );
  QObject::connect( m_Ui->m_RenderWindowDecorationText, SIGNAL(textChanged(QString) )
                    , this, SLOT( AnnotationTextChanged(QString) ) );

  this->Update();
}

QWidget* QmitkStdMultiWidgetEditorPreferencePage::GetQtControl() const
{
  return m_Control;
}

void QmitkStdMultiWidgetEditorPreferencePage::Init(berry::IWorkbench::Pointer)
{
}

void QmitkStdMultiWidgetEditorPreferencePage::PerformCancel()
{
}

bool QmitkStdMultiWidgetEditorPreferencePage::PerformOk()
{
  m_Preferences->Put("stdmulti.widget0 corner annotation", m_WidgetAnnotation[0]);
  m_Preferences->Put("stdmulti.widget1 corner annotation", m_WidgetAnnotation[1]);
  m_Preferences->Put("stdmulti.widget2 corner annotation", m_WidgetAnnotation[2]);
  m_Preferences->Put("stdmulti.widget3 corner annotation", m_WidgetAnnotation[3]);

  m_Preferences->Put("stdmulti.widget0 decoration color", m_WidgetDecorationColor[0]);
  m_Preferences->Put("stdmulti.widget1 decoration color", m_WidgetDecorationColor[1]);
  m_Preferences->Put("stdmulti.widget2 decoration color", m_WidgetDecorationColor[2]);
  m_Preferences->Put("stdmulti.widget3 decoration color", m_WidgetDecorationColor[3]);

  m_Preferences->Put("stdmulti.widget0 first background color", m_WidgetBackgroundColor1[0]);
  m_Preferences->Put("stdmulti.widget1 first background color", m_WidgetBackgroundColor1[1]);
  m_Preferences->Put("stdmulti.widget2 first background color", m_WidgetBackgroundColor1[2]);
  m_Preferences->Put("stdmulti.widget3 first background color", m_WidgetBackgroundColor1[3]);
  m_Preferences->Put("stdmulti.widget0 second background color", m_WidgetBackgroundColor2[0]);
  m_Preferences->Put("stdmulti.widget1 second background color", m_WidgetBackgroundColor2[1]);
  m_Preferences->Put("stdmulti.widget2 second background color", m_WidgetBackgroundColor2[2]);
  m_Preferences->Put("stdmulti.widget3 second background color", m_WidgetBackgroundColor2[3]);
  m_Preferences->PutInt("crosshair gap size", m_Ui->m_CrosshairGapSize->value());

  m_Preferences->PutBool("Use constrained zooming and panning"
                         , m_Ui->m_EnableFlexibleZooming->isChecked());
  m_Preferences->PutBool("Show level/window widget", m_Ui->m_ShowLevelWindowWidget->isChecked());
  m_Preferences->PutBool("PACS like mouse interaction", m_Ui->m_PACSLikeMouseMode->isChecked());

  return true;
}

void QmitkStdMultiWidgetEditorPreferencePage::Update()
{
  //Note: there should be default preferences already defined in the
  //QmitkStdMultiWidgetEditor::InitializePreferences(). Therefore,
  //all default values here are not relevant.
  //gradient background colors
  m_WidgetBackgroundColor1[0] = m_Preferences->Get("stdmulti.widget0 first background color", "#1d1d1c");
  m_WidgetBackgroundColor2[0] = m_Preferences->Get("stdmulti.widget0 second background color", "#1d1d1c");
  m_WidgetBackgroundColor1[1] = m_Preferences->Get("stdmulti.widget1 first background color", "#1d1d1c");
  m_WidgetBackgroundColor2[1] = m_Preferences->Get("stdmulti.widget1 second background color", "#1d1d1c");
  m_WidgetBackgroundColor1[2] = m_Preferences->Get("stdmulti.widget2 first background color", "#1d1d1c");
  m_WidgetBackgroundColor2[2] = m_Preferences->Get("stdmulti.widget2 second background color", "#1d1d1c");
  m_WidgetBackgroundColor1[3] = m_Preferences->Get("stdmulti.widget3 first background color", "#1d1d1c");
  m_WidgetBackgroundColor2[3] = m_Preferences->Get("stdmulti.widget3 second background color", "#adb1b6");

  //decoration colors
  m_WidgetDecorationColor[0] = m_Preferences->Get("stdmulti.widget0 decoration color", "#c00000");
  m_WidgetDecorationColor[1] = m_Preferences->Get("stdmulti.widget1 decoration color", "#0fad00");
  m_WidgetDecorationColor[2] = m_Preferences->Get("stdmulti.widget2 decoration color", "#0080ff");
  m_WidgetDecorationColor[3] = m_Preferences->Get("stdmulti.widget3 decoration color", "#fec500");

  //annotation text
  m_WidgetAnnotation[0] = m_Preferences->Get("stdmulti.widget0 corner annotation", "Axial");
  m_WidgetAnnotation[1] = m_Preferences->Get("stdmulti.widget1 corner annotation", "Sagittal");
  m_WidgetAnnotation[2] = m_Preferences->Get("stdmulti.widget2 corner annotation", "Coronal");
  m_WidgetAnnotation[3] = m_Preferences->Get("stdmulti.widget3 corner annotation", "3D");


  //Ui stuff
  int index = m_Ui->m_RenderWindowChooser->currentIndex();
  QColor firstBackgroundColor(m_WidgetBackgroundColor1[index]);
  QColor secondBackgroundColor(m_WidgetBackgroundColor2[index]);
  QColor widgetColor(m_WidgetDecorationColor[index]);

  this->SetStyleSheetToColorChooserButton(firstBackgroundColor, m_Ui->m_ColorButton1);
  this->SetStyleSheetToColorChooserButton(secondBackgroundColor, m_Ui->m_ColorButton2);
  this->SetStyleSheetToColorChooserButton(widgetColor, m_Ui->m_RenderWindowDecorationColor);

  m_Ui->m_RenderWindowDecorationText->setText(m_WidgetAnnotation[index]);

  m_Ui->m_EnableFlexibleZooming->setChecked(m_Preferences->GetBool("Use constrained zooming and panning", true));
  m_Ui->m_ShowLevelWindowWidget->setChecked(m_Preferences->GetBool("Show level/window widget", true));
  m_Ui->m_PACSLikeMouseMode->setChecked(m_Preferences->GetBool("PACS like mouse interaction", false));
  m_Ui->m_CrosshairGapSize->setValue(m_Preferences->GetInt("crosshair gap size", 32));
}

void QmitkStdMultiWidgetEditorPreferencePage::ColorChooserButtonClicked()
{
  unsigned int widgetIndex = m_Ui->m_RenderWindowChooser->currentIndex();
  if(widgetIndex > 3)
  {
    MITK_ERROR << "Selected index for unknown.";
    return;
  }
  QObject *senderObj = sender(); // This will give Sender button
  //find out last used color and set it
  QColor initialColor;
  if( senderObj->objectName() == m_Ui->m_ColorButton1->objectName())
  {
    initialColor = QColor(m_WidgetBackgroundColor1[widgetIndex]);
  }else if( senderObj->objectName() == m_Ui->m_ColorButton2->objectName())
  {
    initialColor = QColor(m_WidgetBackgroundColor2[widgetIndex]);
  }else if( senderObj->objectName() == m_Ui->m_RenderWindowDecorationColor->objectName())
  {
    initialColor = QColor(m_WidgetDecorationColor[widgetIndex]);
  }

  //get the new color
  QColor newcolor = QColorDialog::getColor(initialColor);
  if(!newcolor.isValid())
  {
    newcolor = initialColor;
  }
  this->SetStyleSheetToColorChooserButton(newcolor, static_cast<QPushButton*>(senderObj));

  //convert it to std string and apply it
  if( senderObj->objectName() == m_Ui->m_ColorButton1->objectName())
  {
    m_WidgetBackgroundColor1[widgetIndex] = newcolor.name();
  }
  else if( senderObj->objectName() == m_Ui->m_ColorButton2->objectName())
  {
    m_WidgetBackgroundColor2[widgetIndex] = newcolor.name();
  }
  else if( senderObj->objectName() == m_Ui->m_RenderWindowDecorationColor->objectName())
  {
    m_WidgetDecorationColor[widgetIndex] = newcolor.name();
  }
}

void QmitkStdMultiWidgetEditorPreferencePage::SetStyleSheetToColorChooserButton(QColor backgroundcolor,
                                                                                QPushButton* button)
{
  button->setAutoFillBackground(true);
  QString styleSheet = "background-color:rgb(";

  styleSheet.append(QString::number(backgroundcolor.red()));
  styleSheet.append(",");
  styleSheet.append(QString::number(backgroundcolor.green()));
  styleSheet.append(",");
  styleSheet.append(QString::number(backgroundcolor.blue()));
  styleSheet.append(")");
  button->setStyleSheet(styleSheet);
}

void QmitkStdMultiWidgetEditorPreferencePage::AnnotationTextChanged(QString text)
{
  unsigned int widgetIndex = m_Ui->m_RenderWindowChooser->currentIndex();
  if( widgetIndex > 3)
  {
    MITK_INFO << "Selected index for unknown widget.";
    return;
  }
  m_WidgetAnnotation[widgetIndex] = text;
}

void QmitkStdMultiWidgetEditorPreferencePage::ResetPreferencesAndGUI()
{
  m_Preferences->Clear();
  this->Update();
}

void QmitkStdMultiWidgetEditorPreferencePage::OnWidgetComboBoxChanged(int i)
{
  if( i > 3)
  {
    MITK_ERROR << "Selected unknown widget.";
    return;
  }
  QColor widgetColor(m_WidgetDecorationColor[i]);
  QColor gradientBackground1(m_WidgetBackgroundColor1[i]);
  QColor gradientBackground2(m_WidgetBackgroundColor2[i]);
  this->SetStyleSheetToColorChooserButton(widgetColor, m_Ui->m_RenderWindowDecorationColor);
  this->SetStyleSheetToColorChooserButton(gradientBackground1, m_Ui->m_ColorButton1);
  this->SetStyleSheetToColorChooserButton(gradientBackground2, m_Ui->m_ColorButton2);
  m_Ui->m_RenderWindowDecorationText->setText(m_WidgetAnnotation[i]);
}
