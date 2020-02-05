/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <Constants.h>
#include <rev/CANSparkMax.h>
class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SpinUp(double speed);

  void SpinTop(double speed);

  void SpinBottom(double speed);
  
  void StopSpinUp();

  void StopTop();

  void StopBottom();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonSRX SpinUpMotor{ConShooter::SPIN_UP_MOTOR};
  rev::CANSparkMax TopMotor{ConShooter::TOP_SHOOT_MOTOR, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax BottomMotor{ConShooter::BOTTOM_SHOOT_MOTOR, rev::CANSparkMax::MotorType::kBrushless};

  
};
