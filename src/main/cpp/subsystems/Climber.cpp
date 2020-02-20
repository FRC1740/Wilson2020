/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

Climber::Climber() {
#ifdef ENABLE_CLIMBER
    m_tabClimber = &frc::Shuffleboard::GetTab(ConShuffleboard::ClimberTab);
    m_tabClimberDistance = m_tabClimber->Add("Climber Position", 0.0).WithSize(2,1).WithPosition(0,0).GetEntry();
    // Set Encoder distance per rotation
    m_dutyCycleEncoder.SetDistancePerRotation(ConClimber::ROTATION_DISTANCE);
    m_dutyCycleEncoder.Reset();
    m_climberPosition = m_dutyCycleEncoder.GetDistance();
    m_motor.BurnFlash();
    
#endif // ENABLE_CLIMBER
}

#ifdef ENABLE_CLIMBER
void Climber::ExtendClimber() {
  if (m_climberPosition > ConClimber::EXT_LIMIT) { // Extending is NEGATIVE/DECREASING on the encoder
  //if (true){
    Go(ConClimber::EXT_SPEED);
  }
  else {
    StopClimber();
  }
}

void Climber::RetractClimber() {
  if (m_climberPosition < ConClimber::RET_LIMIT) { // Retracting is POSITIVE/INCREASING on the encoder
    Go(ConClimber::RET_SPEED);
  }
  else {
    StopClimber();
  }
}

void Climber::StopClimber() {
  //m_motor.Set(ControlMode::PercentOutput, 0.0);
  m_motor.Set(0.0);
}

void Climber::ResetEncoder() {
  m_dutyCycleEncoder.Reset();
}

void Climber::Go(double speed) {
  //m_motor.Set(ControlMode::PercentOutput, speed);
  m_motor.Set(speed);
}

// This method will be called once per scheduler run
void Climber::Periodic() {
  m_climberPosition = m_dutyCycleEncoder.GetDistance();
  m_tabClimberDistance.SetDouble(m_climberPosition);

  if ((m_codriver_control != nullptr) && 
      (m_codriver_control->GetRawButton(ConXBOXControl::START))) {
    ResetEncoder();
  }
}

void Climber::SetCodriverControl(frc::XboxController *codriver_control) {
  m_codriver_control = codriver_control;
}

#endif // ENABLE_CLIMBER
