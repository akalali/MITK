/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.#include "QmitkUltrasoundSupport.h"

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#include "org_mitk_gui_qt_ultrasound_Activator.h"
#include "QmitkUltrasoundSupport.h"

namespace mitk {

ctkPluginContext* org_mitk_gui_qt_ultrasound_Activator::m_Context = nullptr;

void org_mitk_gui_qt_ultrasound_Activator::start(ctkPluginContext* context)
{
  m_Context = context;

  BERRY_REGISTER_EXTENSION_CLASS(QmitkUltrasoundSupport, context)
}

void org_mitk_gui_qt_ultrasound_Activator::stop(ctkPluginContext* context)
{
  m_Context = nullptr;

  Q_UNUSED(context)
}

ctkPluginContext *org_mitk_gui_qt_ultrasound_Activator::GetContext()
{
  return m_Context;
}

}
