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

// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

// Qmitk
#include "QmitkLaserControl.h"

// Qt
#include <QMessageBox>

//mitk
#include <mitkOpotekPumpLaserController.h>

#include <vector>

const std::string OPOLaserControl::VIEW_ID = "org.mitk.views.lasercontrol";

void OPOLaserControl::SetFocus()
{
}

void OPOLaserControl::CreateQtPartControl(QWidget *parent)
{
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi(parent);
  connect(m_Controls.buttonInitLaser, SIGNAL(clicked()), this, SLOT(InitLaser()));
  connect(m_Controls.buttonTune, SIGNAL(clicked()), this, SLOT(TuneWavelength()));
  connect(m_Controls.buttonFastTuning, SIGNAL(clicked()), this, SLOT(StartFastTuning()));
  connect(m_Controls.buttonFlashlamp, SIGNAL(clicked()), this, SLOT(ToggleFlashlamp()));
  connect(m_Controls.buttonQSwitch, SIGNAL(clicked()), this, SLOT(ToggleQSwitch()));

  connect(m_Controls.sliderWavelength, SIGNAL(valueChanged(int)), this, SLOT(SyncWavelengthSetBySlider()));
  connect(m_Controls.spinBoxWavelength, SIGNAL(valueChanged(double)), this, SLOT(SyncWavelengthSetBySpinBox()));

  m_SyncFromSpinBox = true;
  m_SyncFromSlider = true;

  m_PumpLaserConnected = false;
  m_OPOConnected = false;
}
void OPOLaserControl::SyncWavelengthSetBySlider()
{
  if (m_SyncFromSlider)
  {
    m_SyncFromSpinBox = false;
    m_Controls.spinBoxWavelength->setValue(m_Controls.sliderWavelength->value() / 10);
  }
  else
    m_SyncFromSlider = true;
}

void OPOLaserControl::SyncWavelengthSetBySpinBox()
{
  if (m_SyncFromSpinBox)
  {
    m_SyncFromSlider = false;
    m_Controls.sliderWavelength->setValue(m_Controls.spinBoxWavelength->value() * 10);
  }
  else
    m_SyncFromSpinBox = true;
}

void OPOLaserControl::InitLaser()
{
  m_Controls.buttonInitLaser->setEnabled(false);
  m_Controls.buttonInitLaser->setText("working ...");
  if (!m_PumpLaserConnected)
  {
    m_PumpLaserController = mitk::OpotekPumpLaserController::New();

    if (m_PumpLaserController->OpenConnection("OpotekPhocusMobile"))
    {
      m_Controls.buttonFlashlamp->setEnabled(true);
      m_Controls.buttonQSwitch->setEnabled(true);
      m_Controls.buttonInitLaser->setText("Reset and Release Laser");

      std::string message("TRIG EE"); // set both Triggers external
      std::string response("");

      m_PumpLaserController->Send(&message);
      m_PumpLaserController->ReceiveLine(&response);
      m_PumpLaserConnected = true;
      this->GetState();
    }
    else
    {
      MITK_ERROR << "Opotek Pump Laser Initialization Failed.";
      m_Controls.buttonInitLaser->setText("Init Laser");
    }
  }
  else
  {
    // destroy and free
    if (m_PumpLaserController->CloseConnection())
    {
      m_Controls.buttonFlashlamp->setEnabled(false);
      m_Controls.buttonQSwitch->setEnabled(false);
      m_Controls.buttonInitLaser->setText("Init Laser");
      m_PumpLaserConnected = false;
    }
    else
    {
      MITK_ERROR << "Opotek Pump Laser Release failed.";
      m_Controls.buttonInitLaser->setText("Reset and Release Laser");
    }
  }

  if (!m_OPOConnected)
  {
    m_OPOMotor = mitk::GalilMotor::New();
    if (m_OPOMotor->OpenConnection("OpotekPhocusMobile"))
    {
      m_Controls.buttonTune->setEnabled(true);
      m_Controls.buttonFastTuning->setEnabled(true);
      m_Controls.sliderWavelength->setMinimum(m_OPOMotor->GetMinWavelength() * 10);
      m_Controls.sliderWavelength->setMaximum(m_OPOMotor->GetMaxWavelength() * 10);
      m_Controls.spinBoxWavelength->setMinimum(m_OPOMotor->GetMinWavelength());
      m_Controls.spinBoxWavelength->setMaximum(m_OPOMotor->GetMaxWavelength());
      m_Controls.sliderWavelength->setValue(m_OPOMotor->GetCurrentWavelength() * 10);
      m_Controls.spinBoxWavelength->setValue(m_OPOMotor->GetCurrentWavelength());
      m_OPOConnected = true; // not always right FIXME
    }
    else
    {
      MITK_ERROR << "OPO Initialization Failed.";
      m_Controls.buttonInitLaser->setText("Init Laser");
    }
  }
  else
  {
    // destroy and free
    if (m_OPOMotor->CloseConnection())
    {
      m_Controls.buttonTune->setEnabled(false);
      m_Controls.buttonFastTuning->setEnabled(false);
      m_Controls.buttonInitLaser->setText("Init Laser");
      m_OPOConnected = false;
    }
    else
    {
      MITK_ERROR << "OPO release failed.";
      m_Controls.buttonInitLaser->setText("Reset and Release Laser");
    }
  }
  m_Controls.buttonInitLaser->setEnabled(true);
}

void OPOLaserControl::TuneWavelength()
{
  m_OPOMotor->TuneToWavelength(m_Controls.spinBoxWavelength->value());
  QString wavelengthText = QString::number(m_OPOMotor->GetCurrentWavelength());
  wavelengthText.append("nm");
  m_Controls.labelWavelength->setText(wavelengthText);
}

void OPOLaserControl::StartFastTuning()
{
  std::vector<double> listOfWavelengths;
  m_OPOMotor->FastTuneWavelengths(listOfWavelengths/*m_Controls.spinBoxFIXME->value()*/);

  //QString wavelengthText = QString::number(m_OpotekLaserSystem->GetWavelength() / 10);
  //wavelengthText.append("nm");
  //m_Controls.labelWavelength->setText(wavelengthText);
}

void OPOLaserControl::ToggleFlashlamp()
{
  m_Controls.buttonFlashlamp->setText("...");
  if (!m_PumpLaserController->IsFlashing())
  {
    m_PumpLaserController->StartFlashing();
    m_Controls.buttonFlashlamp->setText("Stop Lamp");
  }
  else
  {
    m_PumpLaserController->StopFlashing();
    m_Controls.buttonFlashlamp->setText("Start Lamp");
  }
  this->GetState();
}

void OPOLaserControl::ToggleQSwitch()
{
  m_Controls.buttonQSwitch->setText("...");
  if (!m_PumpLaserController->IsEmitting())
  {
    m_PumpLaserController->StartQswitching();
    m_Controls.buttonQSwitch->setText("Stop Laser");
  }
  else
  {
    m_PumpLaserController->StopQswitching();
    m_Controls.buttonQSwitch->setText("Start Laser");
  }
  this->GetState();
}

void OPOLaserControl::OnSelectionChanged(berry::IWorkbenchPart::Pointer /*source*/,
  const QList<mitk::DataNode::Pointer>& nodes)
{
}

void OPOLaserControl::GetState()
{
  mitk::OpotekPumpLaserController::PumpLaserState pumpLaserState = m_PumpLaserController->GetState();

  if (pumpLaserState == mitk::OpotekPumpLaserController::STATE0)
    m_Controls.labelStatus->setText("PL0: Boot Fault.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::STATE1)
    m_Controls.labelStatus->setText("PL1: Warm Up.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::STATE2)
    m_Controls.labelStatus->setText("PL2: Laser Ready.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::STATE3)
    m_Controls.labelStatus->setText("PL3: Flashing. Pulse Disabled.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::STATE4)
    m_Controls.labelStatus->setText("PL4: Flashing. Shutter Closed.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::STATE5)
    m_Controls.labelStatus->setText("PL5: Flashing. Pulse Enabled.");
  else if (pumpLaserState == mitk::OpotekPumpLaserController::UNCONNECTED)
    m_Controls.labelStatus->setText("PL ERROR.");
}