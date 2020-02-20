/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

namespace ConJumbler {
  constexpr int MOTOR_ID = 1;
  constexpr double MOTOR_SPEED = 0.75;
}


class Jumbler : public frc2::SubsystemBase {
 public:
  Jumbler();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Jumble(double speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonSRX m_jumblerMotor{ConJumbler::MOTOR_ID};
};
