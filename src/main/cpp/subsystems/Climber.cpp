/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

Climber::Climber() {
#ifdef ENABLE_CLIMBER
    m_sbt_Climber = &frc::Shuffleboard::GetTab(ConShuffleboard::ClimberTab);
    m_nte_ClimberDistance = m_sbt_Climber->AddPersistent("Climber Position", 0.0)
          .WithSize(2,1)
          .WithPosition(0,0)
          .GetEntry();
    m_nte_ClimberSpeed = m_sbt_Climber->AddPersistent("Climber Speed", 0.0)
          .WithSize(2,1)
          .WithPosition(0,2)
          .GetEntry();

/*
    wpi::StringMap<std::shared_ptr<nt::Value>> properties {
        std::make_pair(true, "Green"),
        std::make_pair(false, "Red")
    };
*/
    m_nte_Locked = m_sbt_Climber->AddPersistent("Chain Locked?", true)
          .WithSize(1,1)
          .WithPosition(2,0)
          .WithWidget(frc::BuiltInWidgets::kBooleanBox)
 //         .WithProperties(properties)  // true:Green, false:Red
          .GetEntry();

    // Set Encoder distance per rotation
    m_dutyCycleEncoder.SetDistancePerRotation(ConClimber::ROTATION_DISTANCE);
    m_dutyCycleEncoder.Reset();
    m_climberPosition = m_dutyCycleEncoder.GetDistance();
    m_motor.BurnFlash();
    Lock(); // Starting Configuration: Engage chain log
    
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
  Lock();
}

void Climber::ResetEncoder() {
  m_dutyCycleEncoder.Reset();
}

void Climber::Go(double speed) {

/*
  if ((m_codriver_control != nullptr) && 
      (m_codriver_control->GetRawButton(ConLaunchPad::Button::WHITE))) { */
  if (!m_Locked) {
    m_motor.Set(speed);
  }
  else {
    m_motor.Set(0.0);
  }
  //m_motor.Set(ControlMode::PercentOutput, speed); // If we're using a Talon
}

void Climber::Stop() {
  m_motor.Set(0.0);
}

void Climber::Lock() {
  m_motor.Set(0.0);
  m_climberLock.Set(frc::DoubleSolenoid::kForward);
  m_Locked = true;
}

void Climber::Unlock() {
  m_climberLock.Set(frc::DoubleSolenoid::kReverse);
  m_Locked = false;
}

// This method will be called once per scheduler run
void Climber::Periodic() {
  m_climberPosition = m_dutyCycleEncoder.GetDistance();
  m_nte_ClimberDistance.SetDouble(m_climberPosition);
  m_nte_ClimberSpeed.SetDouble(m_motor.Get());
  m_nte_Locked.SetBoolean(m_Locked);

  if ((m_codriver_control != nullptr) && 
      (m_codriver_control->GetRawButton(ConLaunchPad::Switch::GREEN))) { // Nearest to climber controls
    ResetEncoder();
  }
}

void Climber::SetCodriverControl(frc::XboxController *codriver_control) {
  m_codriver_control = codriver_control;
}

#endif // ENABLE_CLIMBER
