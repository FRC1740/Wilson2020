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
//#include <TimeOfFlight.h>
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
        constexpr double OPTIMAL_RPM = 1600.0; // Calibrated RPM from Saturday testing
        constexpr double MAX_RPM = 4000.0;
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
        constexpr double OPTIMAL_RPM = 3100.0; // Calibrated RPM from Saturday testing
        constexpr double MAX_RPM = 4000.0;
         //PID gains
        constexpr double P = 2e-4;
        constexpr double I = 0.0;
        constexpr double D = 2e-3;
        constexpr double FF = 1.7e-4;
    }
    namespace Kicker {
        constexpr int MOTOR_ID = 7;
        constexpr double MOTOR_SPEED = 0.5;
        constexpr double OPTIMAL_RPM = 3500.00; // RPM 
        // PID gains
        constexpr double P = 0.0;
        constexpr double I = 0.0;
        constexpr double D = 0.0;
        constexpr double F = 0.0;
    }
    namespace Jumbler {
        constexpr int MOTOR_ID = 1;
        constexpr double MOTOR_SPEED = 0.5;
    }
    namespace HopperFlapper {
        constexpr int MOTOR_ID = 3;
        constexpr double MOTOR_SPEED = 0.5;
    }
}

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  frc::ShuffleboardTab *m_sbt_Shooter;

  nt::NetworkTableEntry m_nte_TopMotorInputRPM; // TARGET value
  nt::NetworkTableEntry m_nte_BottomMotorInputRPM; // TARGET value
  nt::NetworkTableEntry m_nte_TopMotorOutputRPM; // Actual value
  nt::NetworkTableEntry m_nte_BottomMotorOutputRPM; // Actual value
  nt::NetworkTableEntry m_nte_EnableMotorGraphs;

  nt::NetworkTableEntry m_nte_KickerInputRPM;
  nt::NetworkTableEntry m_nte_KickerMotorSpeed;
  nt::NetworkTableEntry m_nte_KickerMotorVoltage;

  nt::NetworkTableEntry m_nte_JumblerMotorSpeed;
  nt::NetworkTableEntry m_nte_JumblerStatus;

#ifdef ENABLE_SHOOTER
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetBottomMotorSpeed(double velocity);

  void SetTopMotorSpeed(double velocity);

  double GetBottomMotorSpeed();
  
  double GetTopMotorSpeed();

  double GetKickerMotorVoltage();

  void SpinUp();

  void StopSpinUp();

  void Jumble(int direction);

  void Dejumble();

  void SetKickerSpeed(double speed);

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

  TalonSRX m_kickerMotor{ConShooter::Kicker::MOTOR_ID};
  TalonSRX m_jumblerMotor{ConShooter::Jumbler::MOTOR_ID};

  // Feb 24 - Adding Kicker Motor Encoder Feedback for Velocity mode 
  TalonSRXFeedbackDevice m_kickerEncoder;
  TalonSRXConfiguration m_kickerConfig;

  // For the new (Feb 24) hopper "flapper" actuator, either use this:
  TalonSRX m_hopperFlapper{ConShooter::HopperFlapper::MOTOR_ID}; // Window motor for "flapper"
  
  /// == OR == this:  
  // #include <frc/Solenoid.h> // Move to top of file
  // frc::Solenoid m_hopperActuator{1}; // Alternative method for "flapper"
  
  // Then provide a simple On/Off control from O/I at a constant power level

  //frc::TimeOfFlight m_powerCellDetector{0}; // Unused
#endif // ENABLE_SHOOTER
};
