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


#include "org_mitk_gui_qt_matchpoint_evaluator_Activator.h"

#include "QmitkMatchPointRegistrationEvaluator.h"

ctkPluginContext* org_mitk_gui_qt_matchpoint_evaluator_Activator::m_Context = nullptr;

void org_mitk_gui_qt_matchpoint_evaluator_Activator::start(
    ctkPluginContext* context)
{
	BERRY_REGISTER_EXTENSION_CLASS(QmitkMatchPointRegistrationEvaluator, context)

	m_Context = context;
}

void org_mitk_gui_qt_matchpoint_evaluator_Activator::stop(
    ctkPluginContext* context)
{
	Q_UNUSED(context)

	m_Context = nullptr;
}

ctkPluginContext* org_mitk_gui_qt_matchpoint_evaluator_Activator::GetContext()
{
	return m_Context;
}
