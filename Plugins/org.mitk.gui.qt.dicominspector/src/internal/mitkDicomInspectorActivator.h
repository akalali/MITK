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


#ifndef mitkDicomInspectorActivator_h
#define mitkDicomInspectorActivator_h

#include <ctkPluginActivator.h>


class mitkDicomInspectorActivator : public QObject, public ctkPluginActivator
{
  Q_OBJECT
    Q_PLUGIN_METADATA(IID "org_mitk_gui_qt_dicominspector")
    Q_INTERFACES(ctkPluginActivator)
public:

  void start(ctkPluginContext* context) override;
  void stop(ctkPluginContext* context) override;

}; // mitkDicomInspectorActivator

#endif // mitkDicomInspectorActivator_h
