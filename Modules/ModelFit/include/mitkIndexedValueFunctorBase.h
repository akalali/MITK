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

#ifndef IndexedValueFunctorBase_H
#define IndexedValueFunctorBase_H

#include <itkObject.h>
#include <itkIndex.h>
#include <mitkVector.h>

#include "mitkModelBase.h"

#include "MitkModelFitExports.h"

namespace mitk
{

  /**Functor base class for functors that use the index and/or input value
   to generate the output.
   This class is used in conjunction with IndexedValueFunctorPolicy and
   the itkMultiOutputNaryFunctorImageFilter. */
  class MITKMODELFIT_EXPORT IndexedValueFunctorBase: public ::itk::Object
  {
  public:
    typedef IndexedValueFunctorBase Self;
    typedef itk::Object Superclass;
    typedef itk::SmartPointer< Self >                            Pointer;
    typedef itk::SmartPointer< const Self >                      ConstPointer;

    itkTypeMacro(IndexedValueFunctorBase, itk::Object);

    typedef ScalarType InputImagePixelType;
    typedef std::vector<InputImagePixelType> InputPixelVectorType;
    typedef std::vector<InputImagePixelType> OutputPixelVectorType;

    typedef itk::Array<double> GridArrayType;
    typedef itk::Index<3> IndexType;

    virtual OutputPixelVectorType Compute(const InputPixelVectorType & value, const IndexType& currentIndex) const = 0;

    virtual unsigned int GetNumberOfOutputs() const = 0;

  protected:

    IndexedValueFunctorBase()
    {};

    ~IndexedValueFunctorBase() override
    {};

  };

}


#endif // IndexedValueFunctorBase_H
