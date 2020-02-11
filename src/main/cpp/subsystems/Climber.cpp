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
    m_tabClimberDistance = m_tabClimber->Add("Climber Position", 0.0).GetEntry();
    // Set Encoder distance per rotation
    m_dutyCycleEncoder.SetDistancePerRotation(ConClimber::ROTATION_DISTANCE);
    m_dutyCycleEncoder.Reset();
#endif // ENABLE_CLIMBER
}

#ifdef ENABLE_CLIMBER
<<<<<<< HEAD
void Climber::ExtendClimber() {
  if (m_climberPosition > ConClimber::EXT_LIMIT) { // Extending is NEGATIVE/DECREASING on the encoder
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
  m_motor.Set(ControlMode::PercentOutput, 0.0);
}

void Climber::ResetEncoder() {
  m_dutyCycleEncoder.Reset();
}

void Climber::Go(double speed) {
  m_motor.Set(ControlMode::PercentOutput, speed);
=======
void Climber::ExtendClimber(double speed) {
  m_motor.Set(speed);
}

void Climber::RetractClimber(double speed) {
  m_motor.Set(speed);
}

void Climber::StopClimber() {
  m_motor.Set(0.0);
>>>>>>> f135fa04359e12c729ae541d41e958b4db30cbbc
}

void Climber::ResetEncoder() {
  m_dutyCycleEncoder.Reset();
}
// This method will be called once per scheduler run
void Climber::Periodic() {
<<<<<<< HEAD
  m_climberPosition = m_dutyCycleEncoder.GetDistance();
  m_tabClimberDistance.SetDouble(m_climberPosition);
=======
  m_tabClimberDistance.SetDouble(m_dutyCycleEncoder.GetDistance());
>>>>>>> f135fa04359e12c729ae541d41e958b4db30cbbc
}
#endif // ENABLE_CLIMBER
