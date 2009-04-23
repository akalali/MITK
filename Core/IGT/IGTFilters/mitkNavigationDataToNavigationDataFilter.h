/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef MITKNNAVIGATIONDATATONAVIGATIONDATAFILTER_H_HEADER_INCLUDED_
#define MITKNNAVIGATIONDATATONAVIGATIONDATAFILTER_H_HEADER_INCLUDED_

#include <mitkNavigationDataSource.h>

namespace mitk 
{

  /**Documentation
  * \brief NavigationDataToNavigationDataFilter is the base class of all filters that receive 
  * NavigationDatas as input and produce NavigationDatas as output
  *
  * Base class that for all navigation filters that receive NavigationData objects as input 
  * and produce NavigationData objects as output.
  * This class defines the input-interface for NavigationDataFilters. 
  *
  * \ingroup IGT
  */
  class MITK_IGT_EXPORT NavigationDataToNavigationDataFilter : public NavigationDataSource
  {
  public:
    mitkClassMacro(NavigationDataToNavigationDataFilter, NavigationDataSource);

    /**
    * \brief Set the input of this filter
    *
    * \warning: this will set the number of outputs to the number of inputs, 
    * deleting any extra outputs that might have been initialized.
    * Subclasses that have a different number of outputs than inputs
    * must overwrite the SetInput methods.
    */
    virtual void SetInput( const NavigationData* nd);

    /**
    * \brief Set input with id idx of this filter
    *
    * \warning: this will set the number of outputs to the number of inputs, 
    * deleting any extra outputs that might have been initialized.
    * Subclasses that have a different number of outputs than inputs
    * must overwrite the SetInput methods.
    */
    virtual void SetInput( unsigned int idx, const NavigationData* nd);

    /**
    * \brief Get the input of this filter
    */
    const NavigationData* GetInput(void);

    /**
    * \brief Get the input with id idx of this filter
    */
    const NavigationData* GetInput(unsigned int idx);

  protected:
    NavigationDataToNavigationDataFilter();
    virtual ~NavigationDataToNavigationDataFilter();

    /**
    * \brief Create an output for each input
    *
    * This Method sets the number of outputs to the number of inputs
    * and creates missing outputs objects. 
    * \warning any additional outputs that exist before the method is called are deleted
    */
    void CreateOutputsForAllInputs();
  };
} // namespace mitk
#endif /* MITKNAVIGATIONDATATONAVIGATIONDATAFILTER_H_HEADER_INCLUDED_ */
