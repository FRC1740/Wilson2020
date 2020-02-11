/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ControlPanelManipulator.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <stdio.h>

ControlPanelManipulator::ControlPanelManipulator() {
#ifdef ENABLE_CONTROL_PANEL_MANIPULATOR
    m_tabCPM = &frc::Shuffleboard::GetTab(ConShuffleboard::ControlPanelManipulatorTab);
    //frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab(ConShuffleboard::RobotTab);

    // Optimize rotation speed for RotateThree command, scale down for GoToColor
    m_currentSpeed = ConControlPanelManipulator::MOTOR_SPEED; 
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);


		m_rotationMotor.ConfigFactoryDefault();
        /* first choose the sensor */
		m_rotationMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.SetSensorPhase(true);

		/* set the peak and nominal outputs */
		m_rotationMotor.ConfigNominalOutputForward(0, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.ConfigNominalOutputReverse(0, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.ConfigPeakOutputForward(1, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.ConfigPeakOutputReverse(-1, ConControlPanelManipulator::kTimeoutMs);
		/* set closed loop gains in slot0 */
		m_rotationMotor.Config_kF(ConControlPanelManipulator::kPIDLoopIdx, 0.1097, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.Config_kP(ConControlPanelManipulator::kPIDLoopIdx, 0.22, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.Config_kI(ConControlPanelManipulator::kPIDLoopIdx, 0.0, ConControlPanelManipulator::kTimeoutMs);
		m_rotationMotor.Config_kD(ConControlPanelManipulator::kPIDLoopIdx, 0.0, ConControlPanelManipulator::kTimeoutMs);

    // Shuffleboard values
    m_detectedRed = m_tabCPM->Add("Red", 0.0).GetEntry();
    m_detectedGreen = m_tabCPM->Add("Green", 0.0).GetEntry();
    m_detectedBlue = m_tabCPM->Add("Blue", 0.0).GetEntry();
    m_confidence = m_tabCPM->Add("Confidence", 0.0).GetEntry();
    m_colorString = m_tabCPM->Add("Detected Color", "PURPLE").GetEntry();
    m_matchedRed = m_tabCPM->Add("Matched R", 0.0).GetEntry();
    m_matchedGreen = m_tabCPM->Add("Matched G", 0.0).GetEntry();
    m_matchedBlue = m_tabCPM->Add("Matched B", 0.0).GetEntry();
    m_motorCurrent = m_tabCPM->Add("Motor Current", 0.0).GetEntry();

#endif // ENABLE_CONTROL_PANEL_MANIPULATOR
}

#ifdef ENABLE_CONTROL_PANEL_MANIPULATOR
// This method will be called once per scheduler run
void ControlPanelManipulator::Periodic() {

  /**
   * The method GetColor() returns a normalized color value from the sensor and can be
   * useful if outputting the color to an RGB LED or similar. To
   * read the raw color, use GetRawColor().
   * 
   * The color sensor works best when within a few inches from an object in
   * well lit conditions (the built in LED is a big help here!). The farther
   * an object is the more light from the surroundings will bleed into the 
   * measurements and make it difficult to accurately determine its color.
   */
  frc::Color detectedColor = m_colorSensor.GetColor();
  // frc::Shuffleboard::SelectTab(ConShuffleboard::ControlPanelManipulatorTab);

  /**
   * Run the color match algorithm on our detected color
   */
  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);


  // FIXME: change these to : if (matchedColor == kWhenISeeBlue) , etc.
  if (matchedColor == kBlueTarget) {
    colorString = "Blue";
  } else if (matchedColor == kRedTarget) {
    colorString = "Red";
  } else if (matchedColor == kGreenTarget) {
    colorString = "Green";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Yellow";
  } else {
    colorString = "Unknown";
  }
  /* */
  m_sensedColor = colorString;
  m_fieldColor = LookupColor(m_sensedColor);
  /**
   * Open Smart Dashboard or Shuffleboard to see the color detected by the 
   * sensor.
   */

  m_detectedRed.SetDouble(detectedColor.red);
  //frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  m_detectedGreen.SetDouble(detectedColor.green);
  //frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  m_detectedBlue.SetDouble(detectedColor.blue);
  //frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  
  m_confidence.SetDouble(confidence);
  // frc::SmartDashboard::PutNumber("Confidence", confidence);
  m_colorString.SetString(colorString);
  // frc::SmartDashboard::PutString("Detected Color", colorString);

  m_matchedRed.SetDouble(matchedColor.red);
  //frc::SmartDashboard::PutNumber("Matched R", matchedColor.red);
  m_matchedGreen.SetDouble(matchedColor.green);
  // frc::SmartDashboard::PutNumber("Matched G", matchedColor.green);
  m_matchedBlue.SetDouble(matchedColor.blue);
  // frc::SmartDashboard::PutNumber("Matched B", matchedColor.blue);
  m_motorCurrent.SetDouble(m_rotationMotor.GetOutputCurrent());
  // frc::SmartDashboard::PutNumber("Motor Current: ", m_rotationMotor.GetOutputCurrent());

}

std::string ControlPanelManipulator::ReadCurrentColor() {
  return m_sensedColor;
}
std::string ControlPanelManipulator::ReadFieldColor() {
  return m_fieldColor;
}

std::string ControlPanelManipulator::LookupColor(std::string source) { // FIXME: Design color lookup scheme
  return source;
}

void ControlPanelManipulator::Rotate() {
  m_rotationMotor.Set(ControlMode::Velocity, m_currentSpeed); // Maybe 300 RPM?
}

void ControlPanelManipulator::SetSpeed(double speed) {
  m_currentSpeed = speed;
}

void ControlPanelManipulator::Stop() {
  m_rotationMotor.Set(ControlMode::Velocity, 0.0);
  m_currentSpeed = ConControlPanelManipulator::MOTOR_SPEED;
}
#endif // ENABLE_CONTROL_PANEL_MANIPULATOR
