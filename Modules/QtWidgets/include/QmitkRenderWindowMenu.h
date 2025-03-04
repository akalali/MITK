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

#ifndef QMITKRENDERWINDOWMENU_H
#define QMITKRENDERWINDOWMENU_H

#if defined(_WIN32) || defined(__APPLE__)
#define QMITK_USE_EXTERNAL_RENDERWINDOW_MENU
#endif

// mitk qtwidgets module
#include "MitkQtWidgetsExports.h"
#include "QmitkMultiWidgetLayoutManager.h"

// mitk core
#include <mitkBaseRenderer.h>

// qt
#include <QAction>
#include <QEvent>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QTimer>
#include <QToolButton>
#include <QWidget>

/**
 * \ingroup QmitkModule
 * \brief The QmitkRenderWindowMenu is a popup Widget which shows
 * up when the mouse cursor enter a QmitkRenderWindow.
 * The Menu Widget is located in the right top corner of each
 * RenderWindow. It includes different settings. For example
 * the layout design can be changed with the setting button. Switching
 * between full-screen mode and layout design can be done
 * with the full-screen button.
 * The popup Widget can be deactivated with ActivateMenuWidget(false) in
 * QmitkRenderWindow.
 *
 * \sa QmitkRenderWindow
 *
 */
class MITKQTWIDGETS_EXPORT QmitkRenderWindowMenu : public QWidget
{
  Q_OBJECT

public:

  using LayoutIndex = mitk::BaseRenderer::ViewDirection;
  using LayoutDesign = QmitkMultiWidgetLayoutManager::LayoutDesign;

  QmitkRenderWindowMenu(QWidget *parent = nullptr,
                        Qt::WindowFlags f = nullptr,
                        mitk::BaseRenderer *b = nullptr);
  ~QmitkRenderWindowMenu() override;

  /*! Return visibility of settings menu. The menu is connected with m_SettingsButton and includes
  layout direction (axial, coronal .. ) and layout design (standard layout, 2D images top,
  3D bottom ... ). */
  bool GetSettingsMenuVisibilty()
  {
    if (m_LayoutActionsMenu == nullptr)
      return false;
    else
      return m_LayoutActionsMenu->isVisible();
  }

  /*! Set layout index. Defines layout direction (axial, coronal, sagital or threeD) of the parent. */
  void SetLayoutIndex(LayoutIndex layoutIndex);

  /*! Return layout direction of parent (axial, coronal, sagital or threeD) */
  LayoutIndex GetLayoutIndex() { return m_Layout; }
  /*! Update list of layout design (standard layout, 2D images top, 3D bottom ..). Set action of current layout design
  to disable and all other to enable. */
  void UpdateLayoutDesignList(LayoutDesign layoutDesign);

/*! Move menu widget to correct position (right upper corner). E.g. it is necessary when the full-screen mode
is activated.*/
#ifdef QMITK_USE_EXTERNAL_RENDERWINDOW_MENU
  void MoveWidgetToCorrectPos(float opacity);
#else
  void MoveWidgetToCorrectPos(float /*opacity*/);
#endif

  void ShowMenu();
  void HideMenu();

protected:

  /*! Reimplemented from QWidget. The paint event is a request to repaint all or part of a widget.*/
  void paintEvent(QPaintEvent *event) override;

  void CreateMenuWidget();

  /*! Create settings menu which contains layout direction and the different layout designs. */
  void CreateSettingsWidget();

  /*! Change Icon of full-screen button depending on full-screen mode. */
  void ChangeFullScreenIcon();

Q_SIGNALS:

  void ResetView(); // == "global reinit"

  void CrosshairVisibilityChanged(bool);

  // \brief int parameters are enum from QmitkStdMultiWidget
  void CrosshairRotationModeChanged(int);

  /*! emit signal, when layout design changed by the setting menu.*/
  void LayoutDesignChanged(LayoutDesign layoutDesign);

public Q_SLOTS:

  void DeferredShowMenu();
  void DeferredHideMenu();
  /*! This method is responsible for non fluttering of
  the renderWindowMenu when mouse cursor moves along the renderWindowMenu*/
  void smoothHide();

protected Q_SLOTS:

  void enterEvent(QEvent * /*e*/) override;
  void leaveEvent(QEvent * /*e*/) override;

  /// this function is continuously called by a timer
  /// to do the auto rotation
  void AutoRotateNextStep();

  /// this function is invoked when the auto-rotate action
  /// is clicked
  void OnAutoRotationActionTriggered();

  void OnTSNumChanged(int);

  void OnCrosshairMenuAboutToShow();
  void OnCrosshairVisibilityChanged(bool);
  void OnCrosshairRotationModeSelected(QAction *);

  /*! slot for activating/deactivating the full-screen mode. The slot is connected to the clicked() event of
  m_FullScreenButton.
  Activating the full-screen maximize the current widget, deactivating restore If layout design changed by the settings
  menu, the full-Screen mode is automatically switched to false. */
  void OnFullScreenButton(bool checked);

  /*! Slot for opening setting menu. The slot is connected to the clicked() event of m_SettingsButton.
  The settings menu includes different layout directions (axial, coronal, sagittal and 3D) as well all layout design
  (standard layout, 2D images top, 3D bottom ..)*/
  void OnLayoutDesignButton(bool checked);

  void OnSetLayout(LayoutDesign layoutDesign);

protected:

  QToolButton* m_CrosshairModeButton;

  QToolButton* m_FullScreenButton;

  QToolButton* m_LayoutDesignButton;
  QMenu* m_LayoutActionsMenu;
  QAction* m_DefaultLayoutAction;
  QAction* m_All2DTop3DBottomLayoutAction;
  QAction* m_All2DLeft3DRightLayoutAction;
  QAction* m_OneBigLayoutAction;
  QAction* m_Only2DHorizontalLayoutAction;
  QAction* m_Only2DVerticalLayoutAction;
  QAction* m_OneTop3DBottomLayoutAction;
  QAction* m_OneLeft3DRightLayoutAction;
  QAction* m_AllHorizontalLayoutAction;
  QAction* m_AllVerticalLayoutAction;
  QAction* m_RemoveOneLayoutAction;

  QLabel *m_TSLabel;

  QMenu *m_CrosshairMenu;

  /*! Flag if full-screen mode is activated or deactivated. */
  bool m_FullScreenMode;

private:

  mitk::BaseRenderer::Pointer m_Renderer;

  QTimer* m_AutoRotationTimer;
  QTimer* m_HideTimer;

  QWidget *m_Parent;

  //memory because mode is set to default for slice num = 1
  static unsigned int m_DefaultThickMode;

  int m_CrosshairRotationMode;
  bool m_CrosshairVisibility;

  LayoutIndex m_Layout;
  LayoutDesign m_LayoutDesign;
  LayoutDesign m_OldLayoutDesign;

};

#endif // QMITKRENDERWINDOWMENU_H
