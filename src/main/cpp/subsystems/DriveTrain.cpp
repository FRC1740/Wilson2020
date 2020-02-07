/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"

DriveTrain::DriveTrain() {}

#ifdef ENABLE_DRIVETRAIN
// This method will be called once per scheduler run
void DriveTrain::Periodic() {}

void DriveTrain::ArcadeDrive(double speed, double rotation) {
  m_driveTrain.ArcadeDrive(speed, (DeadZone(rotation) * ConDriveTrain::ROTATION_FACTOR));
}

void DriveTrain::SetMaxOutput(double maxOutput) {
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
double DriveTrain::GetRightEncoder() {
  return (-m_rightEncoderA.GetPosition() * ConAuto::ENCODER_TICKS_TO_INCHES) + ConAuto::ENCODER_TICKS_OFFSET;
}

double DriveTrain::GetLeftEncoder() {
  return (m_leftEncoderA.GetPosition() * ConAuto::ENCODER_TICKS_TO_INCHES) + ConAuto::ENCODER_TICKS_OFFSET;
}

double DriveTrain::GetAverageEncoderDistance() {
  return (DriveTrain::GetRightEncoder() + DriveTrain::GetLeftEncoder()) / 2.0;
}
#endif // ENABLE_DRIVETRAIN
