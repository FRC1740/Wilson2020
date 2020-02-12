/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"

DriveTrain::DriveTrain() {
#ifdef ENABLE_DRIVETRAIN
  // Settings for Spark Max motor controllers should be done here, in code
  // and not in the Spark Max Client Software
  m_rightMotorA.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_rightMotorB.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_leftMotorA.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_leftMotorB.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);

  m_rightMotorA.SetInverted(ConDriveTrain::INVERSION);
  m_rightMotorB.SetInverted(ConDriveTrain::INVERSION);
  m_leftMotorA.SetInverted(ConDriveTrain::INVERSION);
  m_leftMotorB.SetInverted(ConDriveTrain::INVERSION);

  // Set additional motor controllers on drive train to follow
  m_rightMotorB.Follow(m_rightMotorA, false);
  m_leftMotorB.Follow(m_leftMotorA, false);
#endif // ENABLE_DRIVETRAIN
}

#ifdef ENABLE_DRIVETRAIN
// This method will be called once per scheduler run
void DriveTrain::Periodic() {}

void DriveTrain::ArcadeDrive(double speed, double rotation) {
  m_driveTrain.ArcadeDrive(speed, DeadZone(rotation));
}

void DriveTrain::TankDrive(double left, double right){
  m_driveTrain.TankDrive(left, right);
}



void DriveTrain::SetMaxOutput(double maxOutput) {
  m_maxOutput = maxOutput;
  m_driveTrain.SetMaxOutput(maxOutput);
}

// This is used by autonomous code
void DriveTrain::ResetEncoders() {
  m_rightEncoderA.SetPosition(0.0);
  m_rightEncoderB.SetPosition(0.0);
  m_leftEncoderA.SetPosition(0.0);
  m_leftEncoderB.SetPosition(0.0);
}

// FIXME: Account for two encoders per side
// Right Encoder set to negative b/c motor flipped
double DriveTrain::GetRightDistance() {
  return (m_rightEncoderA.GetPosition() * ConAuto::ENCODER_TICKS_TO_INCHES) + ConAuto::ENCODER_TICKS_OFFSET;
}

double DriveTrain::GetLeftDistance() {
  return (m_leftEncoderA.GetPosition() * ConAuto::ENCODER_TICKS_TO_INCHES) + ConAuto::ENCODER_TICKS_OFFSET;
}

double DriveTrain::GetAverageEncoderDistance() {
  return (m_leftEncoderA.GetPosition() + m_rightEncoderA.GetPosition()) / 2.0;
}
#endif // ENABLE_DRIVETRAIN
