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
#include <TimeOfFlight.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  void SetBottomMotorSpeed(double velocity);

  void SetTopMotorSpeed(double velocity);

  double GetBottomMotorSpeed();

  double GetTopMotorSpeed();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  // frc::Ultrasonic powerCellDetector{0,1};

  frc::TimeOfFlight::TimeOfFlight powerCellDetector{0};

  // Motors for spinning top and bottom wheels of the shooter
  rev::CANSparkMax top_motor{ConShooter::Top::MOTOR, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax bottom_motor{ConShooter::Bottom::MOTOR, rev::CANSparkMax::MotorType::kBrushless};

  // Built-in encoders on the NEO Motors above
  rev::CANEncoder top_encoder = top_motor.GetEncoder();
  rev::CANEncoder bottom_encoder = bottom_motor.GetEncoder();

  //PID controller
  rev::CANPIDController top_velocity_PID = top_motor.GetPIDController();
  rev::CANPIDController bottom_velocity_PID = bottom_motor.GetPIDController();


};
