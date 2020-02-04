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
  void SetBottomMotorSpeed(double);
  void SetTopMotorSpeed(double);
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

  frc::TimeOfFlight m_powerCellDetector{0};

};
