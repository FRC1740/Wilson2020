/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Constants.h"
#include <frc2/command/SubsystemBase.h>
#include <rev/CANPIDController.h>
#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <TimeOfFlight.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter(); 
  void SetBottomMotorSpeed(double);
  void SetTopMotorSpeed(double);
  double GetBottomMotorSpeed();
  double GetTopMotorSpeed();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SpinUp();

  void SpinTop();

  void SpinBottom();
  
  void StopSpinUp();

  void StopTop();

  void StopBottom();

  void Activate();

  void Deactivate();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Which do we use? TalonSRX is in the ctre library, WPI_TalonSRX is 
  // TalonSRX m_feedMotor{ConShooter::FEED_MOTOR_ID};
  WPI_TalonSRX m_feedMotor{ConShooter::FEED_MOTOR_ID};
  rev::CANSparkMax m_topMotor{ConShooter::TOP_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_bottomMotor{ConShooter::BOTTOM_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  frc::TimeOfFlight m_powerCellDetector{0};
};
