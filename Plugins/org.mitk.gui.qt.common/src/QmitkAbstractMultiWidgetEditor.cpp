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

#include "QmitkAbstractMultiWidgetEditor.h"

// mitk qt widgets module
#include <QmitkAbstractMultiWidget.h>
#include <QmitkRenderWindowWidget.h>

// mitk gui qt common plugin
#include "QmitkMultiWidgetDecorationManager.h"

// berry
#include <berryIWorkbenchPartConstants.h>

const QString QmitkAbstractMultiWidgetEditor::EDITOR_ID = "org.mitk.editors.abstractmultiwidget";

struct QmitkAbstractMultiWidgetEditor::Impl final
{
  Impl();
  ~Impl() = default;

  QmitkAbstractMultiWidget* m_MultiWidget;

  std::unique_ptr<QmitkMultiWidgetDecorationManager> m_MultiWidgetDecorationManager;
};

QmitkAbstractMultiWidgetEditor::Impl::Impl()
  : m_MultiWidget(nullptr)
{
  // nothing here
}

QmitkAbstractMultiWidgetEditor::QmitkAbstractMultiWidgetEditor()
  : m_Impl(std::make_unique<Impl>())
{
  // nothing here
}

QmitkAbstractMultiWidgetEditor::~QmitkAbstractMultiWidgetEditor() {}

QmitkRenderWindow* QmitkAbstractMultiWidgetEditor::GetActiveQmitkRenderWindow() const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr != multiWidget)
  {
    auto activeRenderWindowWidget = multiWidget->GetActiveRenderWindowWidget();
    if (nullptr != activeRenderWindowWidget)
    {
      return activeRenderWindowWidget->GetRenderWindow();
    }
  }

  return nullptr;
}

QHash<QString, QmitkRenderWindow*> QmitkAbstractMultiWidgetEditor::GetQmitkRenderWindows() const
{
  QHash<QString, QmitkRenderWindow*> result;
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return result;
  }

  result = multiWidget->GetRenderWindows();
  return result;
}

QmitkRenderWindow* QmitkAbstractMultiWidgetEditor::GetQmitkRenderWindow(const QString& id) const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return nullptr;
  }

  return multiWidget->GetRenderWindow(id);
}

QmitkRenderWindow* QmitkAbstractMultiWidgetEditor::GetQmitkRenderWindow(const mitk::BaseRenderer::ViewDirection& viewDirection) const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return nullptr;
  }

  return multiWidget->GetRenderWindow(viewDirection);
}

mitk::Point3D QmitkAbstractMultiWidgetEditor::GetSelectedPosition(const QString& id/* = QString()*/) const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return mitk::Point3D();
  }

  return multiWidget->GetSelectedPosition(id);
}

void QmitkAbstractMultiWidgetEditor::SetSelectedPosition(const mitk::Point3D& pos, const QString& id/* = QString()*/)
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr != multiWidget)
  {
    return multiWidget->SetSelectedPosition(pos, id);
  }
}

void QmitkAbstractMultiWidgetEditor::EnableDecorations(bool enable, const QStringList& decorations)
{
  m_Impl->m_MultiWidgetDecorationManager->ShowDecorations(enable, decorations);
}

bool QmitkAbstractMultiWidgetEditor::IsDecorationEnabled(const QString& decoration) const
{
  return m_Impl->m_MultiWidgetDecorationManager->IsDecorationVisible(decoration);
}

QStringList QmitkAbstractMultiWidgetEditor::GetDecorations() const
{
  return m_Impl->m_MultiWidgetDecorationManager->GetDecorations();
}

berry::IPartListener::Events::Types QmitkAbstractMultiWidgetEditor::GetPartEventTypes() const
{
  return Events::CLOSED | Events::OPENED;
}

void QmitkAbstractMultiWidgetEditor::PartOpened(const berry::IWorkbenchPartReference::Pointer& partRef)
{
  if (partRef->GetId() == QmitkAbstractMultiWidgetEditor::EDITOR_ID)
  {
    const auto& multiWidget = GetMultiWidget();
    if (nullptr != multiWidget)
    {
      multiWidget->MultiWidgetOpened();
    }
  }
}

void QmitkAbstractMultiWidgetEditor::PartClosed(const berry::IWorkbenchPartReference::Pointer& partRef)
{
  if (partRef->GetId() == QmitkAbstractMultiWidgetEditor::EDITOR_ID)
  {
    const auto& multiWidget = GetMultiWidget();
    if (nullptr != multiWidget)
    {
      multiWidget->MultiWidgetClosed();
    }
  }
}

QmitkRenderWindow* QmitkAbstractMultiWidgetEditor::GetQmitkRenderWindowByIndex(int index) const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return nullptr;
  }

  QString renderWindowName = multiWidget->GetNameFromIndex(index);
  return multiWidget->GetRenderWindow(renderWindowName);
}

QmitkRenderWindow* QmitkAbstractMultiWidgetEditor::GetQmitkRenderWindowByIndex(int row, int column) const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return nullptr;
  }

  QString renderWindowName = multiWidget->GetNameFromIndex(row, column);
  return multiWidget->GetRenderWindow(renderWindowName);
}

void QmitkAbstractMultiWidgetEditor::SetMultiWidget(QmitkAbstractMultiWidget* multiWidget)
{
  m_Impl->m_MultiWidget = multiWidget;
  m_Impl->m_MultiWidgetDecorationManager.reset(new QmitkMultiWidgetDecorationManager(multiWidget));
}

QmitkAbstractMultiWidget* QmitkAbstractMultiWidgetEditor::GetMultiWidget() const
{
  return m_Impl->m_MultiWidget;
}

int QmitkAbstractMultiWidgetEditor::GetRowCount() const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return 0;
  }

  return multiWidget->GetRowCount();
}

int QmitkAbstractMultiWidgetEditor::GetColumnCount() const
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr == multiWidget)
  {
    return 0;
  }

  return multiWidget->GetColumnCount();
}

void QmitkAbstractMultiWidgetEditor::OnLayoutSet(int row, int column)
{
  const auto& multiWidget = GetMultiWidget();
  if (nullptr != multiWidget)
  {
    multiWidget->SetLayout(row, column);
    FirePropertyChange(berry::IWorkbenchPartConstants::PROP_INPUT);
  }
}

 void QmitkAbstractMultiWidgetEditor::OnSynchronize(bool synchronized)
 {
   const auto& multiWidget = GetMultiWidget();
   if (nullptr != multiWidget)
   {
     multiWidget->Synchronize(synchronized);
   }
 }

 void QmitkAbstractMultiWidgetEditor::OnInteractionSchemeChanged(mitk::InteractionSchemeSwitcher::InteractionScheme scheme)
 {
   const auto& multiWidget = GetMultiWidget();
   if (nullptr != multiWidget)
   {
     multiWidget->SetInteractionScheme(scheme);
   }
 }
