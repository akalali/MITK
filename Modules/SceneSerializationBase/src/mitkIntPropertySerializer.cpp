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

#ifndef mitkIntPropertySerializer_h_included
#define mitkIntPropertySerializer_h_included

#include "mitkBasePropertySerializer.h"

#include "mitkProperties.h"

namespace mitk
{
  class IntPropertySerializer : public BasePropertySerializer
  {
  public:
    mitkClassMacro(IntPropertySerializer, BasePropertySerializer);
    itkFactorylessNewMacro(Self) itkCloneMacro(Self)

      TiXmlElement *Serialize() override
    {
      if (const IntProperty *prop = dynamic_cast<const IntProperty *>(m_Property.GetPointer()))
      {
        auto element = new TiXmlElement("int");
        element->SetAttribute("value", prop->GetValue());
        return element;
      }
      else
        return nullptr;
    }

    BaseProperty::Pointer Deserialize(TiXmlElement *element) override
    {
      if (!element)
        return nullptr;

      int integer;
      if (element->QueryIntAttribute("value", &integer) == TIXML_SUCCESS)
      {
        return IntProperty::New(integer).GetPointer();
      }
      else
      {
        return nullptr;
      }
    }

  protected:
    IntPropertySerializer() {}
    ~IntPropertySerializer() override {}
  };

} // namespace

// important to put this into the GLOBAL namespace (because it starts with 'namespace mitk')
MITK_REGISTER_SERIALIZER(IntPropertySerializer);

#endif
