/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <rev/CANSparkMax.h>

#include "Constants.h"

class DriveTrain : public frc2::SubsystemBase {
 public:
  DriveTrain();

#ifdef ENABLE_DRIVETRAIN
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * Drives the robot using arcade controls.
   *
   * @param speed the commanded forward movement
   * @param rotation the commanded rotation
   */
  void ArcadeDrive(double speed, double rotation);

  void TankDrive(double left, double right);

  void SetMaxOutput(double maxOutput);

  double GetAverageEncoderDistance();

  double GetRightEncoder();

  double GetLeftEncoder();

  void ResetEncoders();
  
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Neo motor controllers
  rev::CANSparkMax m_rightMotorA{ConDriveTrain::RIGHT_MOTOR_A_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorB{ConDriveTrain::RIGHT_MOTOR_B_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorA{ConDriveTrain::LEFT_MOTOR_A_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorB{ConDriveTrain::LEFT_MOTOR_B_ID, rev::CANSparkMax::MotorType::kBrushless};

  // Drive encoders

  rev::CANEncoder m_rightEncoderA = m_rightMotorA.GetEncoder();
  rev::CANEncoder m_rightEncoderB = m_rightMotorB.GetEncoder();
  rev::CANEncoder m_leftEncoderA = m_leftMotorA.GetEncoder();
  rev::CANEncoder m_leftEncoderB = m_leftMotorB.GetEncoder();

  // Robot Drive
  // FIXME: need to make MotorB followers of MotorA
  frc::DifferentialDrive m_driveTrain{m_leftMotorA, m_rightMotorA};
#endif // ENABLE_DRIVETRAIN
};
