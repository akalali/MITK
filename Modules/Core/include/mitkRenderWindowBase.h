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

#ifndef MITKRENDERWINDOWBASE_H_HEADER_INCLUDED_C1C40D66ASDF
#define MITKRENDERWINDOWBASE_H_HEADER_INCLUDED_C1C40D66ASDF

#include <MitkCoreExports.h>

#include "mitkCameraRotationController.h"
#include "mitkSliceNavigationController.h"
#include "mitkVtkPropRenderer.h"
#include "vtkMitkRenderProp.h"

#include "mitkInteractionEvent.h"

namespace mitk
{
  /**
   * \brief Base class of MITK RenderWindows
   *
   * This class sets up the MITK rendering mechanism and it's integration into VTK.
   *
   * Currently, there are two specific implementations of this abstract class:
   * QmitkRenderWindow, inerhits from the QVTKWidget and is the matured way for MITK rendering
   * mitkRenderWindow is a new, QT-independent RenderWindow implementation
   *
   * \ingroup Renderer
   */

  class MITKCORE_EXPORT RenderWindowBase
  {
  public:
    // mitkClassMacroItkParent(RenderWindowBase,itk::Object);
    // itkFactorylessNewMacro(Self)
    // itkCloneMacro(Self)

    virtual ~RenderWindowBase();

    void InitRenderer();

    virtual mitk::SliceNavigationController *GetSliceNavigationController();
    virtual mitk::CameraRotationController *GetCameraRotationController();
    virtual mitk::BaseController *GetController();
    virtual mitk::VtkPropRenderer *GetRenderer();
    virtual vtkRenderWindow *GetVtkRenderWindow() = 0;
    virtual vtkRenderWindowInteractor *GetVtkRenderWindowInteractor() = 0;

    virtual bool HandleEvent(InteractionEvent *interactionEvent);

  protected:
    RenderWindowBase();

    // helper functions: within constructors and destructors classes are not polymorph.
    void Initialize(const char *name = "unnamed renderer");
    void Destroy();

    mitk::VtkPropRenderer::Pointer m_Renderer;

    vtkMitkRenderProp *m_RenderProp;

    bool m_InResize;

  private:
  };
}

#endif /* MITKRENDERWINDOWBASE_H_HEADER_INCLUDED_C1C40D66ASDF */
