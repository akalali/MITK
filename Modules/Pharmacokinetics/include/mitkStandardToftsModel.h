#ifndef MITKSTANDARDTOFTSMODEL_H
#define MITKSTANDARDTOFTSMODEL_H

#include "mitkAIFBasedModelBase.h"
#include "MitkPharmacokineticsExports.h"

namespace mitk
{
  /** @class StandardToftsModel
   * @brief Implementation of the Model function of the Tofts pharmacokinetic model, using an Aterial Input Function
   * The Model calculates the Concentration-Time-Curve as a convolution of the plasma curve Cp (the AIF) and a tissue specific
   * residue function (in this case an exponential: R(t) = ktrans * exp(-ktrans/ve * (t)) ).
   *       C(t) = vp * Cp(t) + conv(Cp(t),R(t))
   * The parameters ktrans, ve and ve are subject to the fitting routine*/

  class MITKPHARMACOKINETICS_EXPORT StandardToftsModel : public AIFBasedModelBase
  {

  public:
    typedef StandardToftsModel Self;
    typedef AIFBasedModelBase Superclass;
    typedef itk::SmartPointer< Self >                            Pointer;
    typedef itk::SmartPointer< const Self >                      ConstPointer;

    /** Method for creation through the object factory. */
    itkFactorylessNewMacro(Self);
    itkCloneMacro(Self);

    /** Run-time type information (and related methods). */
    itkTypeMacro(StandardToftsModel, ModelBase);

    static const std::string MODEL_DISPLAY_NAME;

    static const std::string NAME_PARAMETER_Ktrans;
    static const std::string NAME_PARAMETER_ve;
    static const std::string NAME_PARAMETER_vp;

    static const std::string UNIT_PARAMETER_Ktrans;
    static const std::string UNIT_PARAMETER_ve;
    static const std::string UNIT_PARAMETER_vp;

    static const unsigned int POSITION_PARAMETER_Ktrans;
    static const unsigned int POSITION_PARAMETER_ve;
    static const unsigned int POSITION_PARAMETER_vp;

    static const unsigned int NUMBER_OF_PARAMETERS;

    std::string GetModelDisplayName() const override;

    std::string GetModelType() const override;

    ParameterNamesType GetParameterNames() const override;
    ParametersSizeType  GetNumberOfParameters() const override;

    ParamterUnitMapType GetParameterUnits() const override;

    ParameterNamesType GetDerivedParameterNames() const override;

    ParametersSizeType  GetNumberOfDerivedParameters() const override;

    ParamterUnitMapType GetDerivedParameterUnits() const override;

  protected:
    StandardToftsModel();
    ~StandardToftsModel() override;

    /**
     * Actual implementation of the clone method. This method should be reimplemeted
     * in subclasses to clone the extra required parameters.
     */
    itk::LightObject::Pointer InternalClone() const override;

    ModelResultType ComputeModelfunction(const ParametersType& parameters) const override;

    DerivedParameterMapType ComputeDerivedParameters(const mitk::ModelBase::ParametersType&
        parameters) const override;


    void PrintSelf(std::ostream& os, ::itk::Indent indent) const override;

  private:


    //No copy constructor allowed
    StandardToftsModel(const Self& source);
    void operator=(const Self&);  //purposely not implemented




  };
}

#endif // MITKSTANDARDTOFTSMODEL_H
