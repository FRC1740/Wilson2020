/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ControlPanelManipulator.h"
#include <frc/smartdashboard/SmartDashboard.h>

ControlPanelManipulator::ControlPanelManipulator() {
    m_currentSpeed = ConControlPanelManipulator::MOTOR_SPEED; // Optimum for multi-rotation
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);

}

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
    
  /**
   * Open Smart Dashboard or Shuffleboard to see the color detected by the 
   * sensor.
   */

  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  frc::SmartDashboard::PutNumber("Confidence", confidence);
  frc::SmartDashboard::PutString("Detected Color", colorString);
  frc::SmartDashboard::PutNumber("Matched R", matchedColor.red);
  frc::SmartDashboard::PutNumber("Matched G", matchedColor.green);
  frc::SmartDashboard::PutNumber("Matched B", matchedColor.blue);
  /* */
  //frc::SmartDashboard::PutNumber("Control Panel Rate: ", encoder.GetRate());
  //frc::SmartDashboard::PutBoolean("Control Panel Stopped?: ", encoder.GetStopped());
  //frc::SmartDashboard::PutBoolean("Control Panel Direction: ", encoderwifi.GetDirection());
  //frc::SmartDashboard::PutNumber("Control Panel Period: ", encoder.GetPeriod());

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
