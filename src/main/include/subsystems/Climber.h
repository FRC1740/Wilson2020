/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include "Constants.h"


class Climber : public frc2::SubsystemBase {
 public:
  Climber();

#ifdef ENABLE_CLIMBER
  frc::ShuffleboardTab *m_tabClimber;

  void ExtendClimber(double speed);

  void RetractClimber(double speed);

  void StopClimber();

  void ResetEncoder();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonSRX m_motor{ConClimber::MOTOR_ID};
  frc::DutyCycleEncoder m_dutyCycleEncoder{0};
  nt::NetworkTableEntry m_tabClimberDistance;

#endif // ENABLE_CLIMBER
};
