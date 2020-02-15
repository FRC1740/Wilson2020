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
#include <TimeOfFlight.h>
#include <frc/Encoder.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>

namespace ConShooter {
    namespace Top {
        constexpr int MOTOR_ID = 6;
        constexpr int WHEEL_SIZE = 4; //in inches
        constexpr double VELOCITY_FACTOR = 1; //(ConMath::PI*WHEEL_SIZE) * ConMath::METERS_2_INCH * ConMath::MINUTES_2_SECONDS; //(velocity) y [m/s] = PI*WHEEL_SIZE * m/in * 1/60 * x [RPM]
        constexpr double MOTOR_SPEED = 0.5;
        //PID gains
        constexpr double P = 2e-4;
        constexpr double I = 0.0;
        constexpr double D = 2e-3;
        constexpr double FF = 1.7e-4;
    }
    namespace Bottom {
        constexpr int MOTOR_ID = 9;
        constexpr int WHEEL_SIZE = 6; //in inches
        constexpr double VELOCITY_FACTOR = 1; //(ConMath::PI*WHEEL_SIZE) * ConMath::METERS_2_INCH * ConMath::MINUTES_2_SECONDS; //(velocity) y [m/s] = PI*WHEEL_SIZE * m/in * 1/60 * x [RPM]
        constexpr double MOTOR_SPEED = 0.5;
         //PID gains
        constexpr double P = 2e-4;
        constexpr double I = 0.0;
        constexpr double D = 2e-3;
        constexpr double FF = 1.7e-4;
    }
    namespace Feeder {
        constexpr int MOTOR_ID = 7;
        constexpr double MOTOR_SPEED = 0.5;
    }
    namespace Hopper {
        constexpr int MOTOR_ID = 1;
        constexpr int MOTOR_SPEED = 2.0/3.0;
    }
}

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

#ifdef ENABLE_SHOOTER
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetBottomMotorSpeed(double velocity);

  void SetTopMotorSpeed(double velocity);

  double GetBottomMotorSpeed();
  
  double GetTopMotorSpeed();

  void SpinUp();

  void SpinTop();

  void SpinBottom();
  
  void StopSpinUp();

  void StopTop();

  void StopBottom();

  void Activate();

  void Deactivate();

  void SetFeedSpeed(double speed);

  void SetHopperSpeed(double speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax m_topMotor{ConShooter::Top::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_bottomMotor{ConShooter::Bottom::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};

  // Built-in encoders on the NEO Motors above
  rev::CANEncoder m_topEncoder = m_topMotor.GetEncoder();
  rev::CANEncoder m_bottomEncoder = m_bottomMotor.GetEncoder();

  //PID controller
  rev::CANPIDController m_topVelocityPID = m_topMotor.GetPIDController();
  rev::CANPIDController m_bottomVelocityPID = m_bottomMotor.GetPIDController();

  TalonSRX m_feedMotor{ConShooter::Feeder::MOTOR_ID};
  TalonSRX m_hopperMotor{ConShooter::Hopper::MOTOR_ID};

  frc::TimeOfFlight m_powerCellDetector{0};

  frc::ShuffleboardTab *m_tabCPM;
  nt::NetworkTableEntry m_topMotorRPM;
  nt::NetworkTableEntry m_bottomMotorRPM;
  nt::NetworkTableEntry m_feederMotorSpeed;

#endif // ENABLE_SHOOTER
};
