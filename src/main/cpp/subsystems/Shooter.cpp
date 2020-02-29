/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <frc/shuffleboard/BuiltInWidgets.h>
#include <wpi/StringMap.h> // for wpi::StringMap
#include <utility> // for std::pair

Shooter::Shooter() {

#ifdef ENABLE_SHOOTER
    // Invert shooter motors correctly
    m_topMotor.SetInverted(false);
    m_bottomMotor.SetInverted(true);
    m_kickerMotor.SetInverted(true);
    // m_jumblerMotor.SetInverted(true);

    // Set velocity of shaft relative to velocity of wheel
    m_topEncoder.SetVelocityConversionFactor(ConShooter::Top::VELOCITY_FACTOR);
    m_bottomEncoder.SetVelocityConversionFactor(ConShooter::Bottom::VELOCITY_FACTOR);

    // Set controller gains from constants
    // See this for tuning help (Robot Characterization Tool)
    // https://docs.wpilib.org/en/latest/docs/software/wpilib-overview/new-for-2020.html
    m_topVelocityPID.SetP(ConShooter::Top::P);
    m_topVelocityPID.SetI(ConShooter::Top::I);
    m_topVelocityPID.SetD(ConShooter::Top::D);
    m_topVelocityPID.SetFF(ConShooter::Top::FF);
    m_topVelocityPID.SetOutputRange(0.0, 1.0);
    
    m_bottomVelocityPID.SetP(ConShooter::Bottom::P);
    m_bottomVelocityPID.SetI(ConShooter::Bottom::I);
    m_bottomVelocityPID.SetD(ConShooter::Bottom::D);
    m_bottomVelocityPID.SetFF(ConShooter::Bottom::FF);
    m_bottomVelocityPID.SetOutputRange(0.0, 1.0);

    m_topMotor.BurnFlash();
    m_bottomMotor.BurnFlash();
    
    // First choose kicker sensor
    m_kickerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 30);    

    // Set the peak and nominal outputs
    m_kickerMotor.ConfigNominalOutputForward(0, 30);
    m_kickerMotor.ConfigNominalOutputReverse(0, 30);
    m_kickerMotor.ConfigPeakOutputForward(1, 30);
    m_kickerMotor.ConfigPeakOutputReverse(-1, 30);

    // Kicker motor PID code
    m_kickerMotor.SelectProfileSlot(0,0);
    m_kickerMotor.Config_kP(0, ConShooter::Kicker::P, 30); // "Slot", Value, timeout (ms)
    m_kickerMotor.Config_kI(0, ConShooter::Kicker::I, 30);  
    m_kickerMotor.Config_kD(0, ConShooter::Kicker::D, 30); 
    m_kickerMotor.Config_kF(0, ConShooter::Kicker::F, 30);
    
    m_kickerMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
    m_jumblerMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_hopperFlapper.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
#endif // ENABLE_SHOOTER

  // Create and get reference to SB tab
  m_sbt_Shooter = &frc::Shuffleboard::GetTab(ConShuffleboard::ShooterTab);

  m_nte_TopMotorInputRPM = m_sbt_Shooter->
    AddPersistent("Top Motor Input RPM", ConShooter::Top::OPTIMAL_RPM)
    .WithSize(2, 1)
    .WithPosition(0, 0)
    .GetEntry();

  m_nte_BottomMotorInputRPM = m_sbt_Shooter->
    AddPersistent("Bottom Motor Input RPM", ConShooter::Bottom::OPTIMAL_RPM)
    .WithSize(2, 1)
    .WithPosition(0, 1)
    .GetEntry();

  m_nte_TopMotorOutputRPM = m_sbt_Shooter->
    AddPersistent("Top Motor Output RPM", 0.0)
    .WithWidget(frc::BuiltInWidgets::kGraph)
    .WithSize(6, 2)
    .WithPosition(2, 0)
    .GetEntry();

  m_nte_BottomMotorOutputRPM = m_sbt_Shooter->
    AddPersistent("Bottom Motor Output RPM", 0.0)
    .WithWidget(frc::BuiltInWidgets::kGraph)
    .WithSize(6, 2)
    .WithPosition(2, 2)
    .GetEntry();

  m_nte_EnableMotorGraphs = m_sbt_Shooter->
    AddPersistent("Enable Motor Graphs", true)
    .WithWidget(frc::BuiltInWidgets::kToggleButton)
    .WithSize(1, 1)
    .WithPosition(8, 0)
    .GetEntry();

  m_nte_JumblerMotorSpeed = m_sbt_Shooter->
    AddPersistent("Jumbler Motor Speed", ConShooter::Jumbler::MOTOR_SPEED)
    .WithSize(2, 1)
    .WithPosition(0, 3)
    .GetEntry();

  m_nte_KickerInputRPM = m_sbt_Shooter->
    AddPersistent("Kicker RPM", ConShooter::Kicker::OPTIMAL_RPM)
    .WithSize(1, 1)
    .WithPosition(0, 2)
    .GetEntry();

  m_nte_KickerMotorError = m_sbt_Shooter->
    AddPersistent("Kicker Error", 0.0)
    .WithSize(2,1)
    .WithPosition(6,1)
    .GetEntry();

  /* Is there a way to get the current speed of a TalonSRX Motor? */
  m_nte_KickerMotorVoltage = m_sbt_Shooter->
    AddPersistent("Kicker Motor Voltage", 0.0)
    .WithSize(2, 1)
    .WithPosition(6, 2)
    .GetEntry();

  /*
  m_nte_JumblerStatus = m_sbt_Shooter->
    AddPersistent("Jumbler Status", false)
    .WithWidget(frc::BuiltInWidgets::kToggleButton)
    .WithSize(2, 1)
    .WithPosition(3, 2)
    .GetEntry();
  */
}

#ifdef ENABLE_SHOOTER
// This method will be called once per scheduler run
void Shooter::Periodic() {

    // Update Network Table/Shuffleboard Values
    m_nte_TopMotorOutputRPM.SetDouble(GetTopMotorSpeed());
    m_nte_BottomMotorOutputRPM.SetDouble(GetBottomMotorSpeed());
    m_nte_KickerMotorVoltage.SetDouble(GetKickerMotorVoltage());
    m_nte_KickerMotorError.SetDouble(GetKickerError());

#if 0 // NOT PLANNING TO USE THIS SENSOR
    // Check TimeofFLight sensor to see if a powerCell is ... stuck? loaded? ??
    frc::SmartDashboard::PutNumber("Range: ", m_powerCellDetector.GetRange());
    if (m_powerCellDetector.GetRange() < 300.0)  { // FIXME: range in mm 
        frc::SmartDashboard::PutBoolean("PowerCell", true);
    }
    else {
        frc::SmartDashboard::PutBoolean("PowerCell", false);
    } 
#endif
}

// Used internally only
void Shooter::SetBottomMotorSpeed(double velocity) {
    double vlimit = (velocity > ConShooter::Bottom::MAX_RPM) ? ConShooter::Bottom::MAX_RPM : velocity;
    m_bottomVelocityPID.SetReference(vlimit, rev::ControlType::kVelocity);
}

// Used internally only
void Shooter::SetTopMotorSpeed(double velocity) {
    double vlimit = (velocity > ConShooter::Top::MAX_RPM) ? ConShooter::Top::MAX_RPM : velocity;
    m_topVelocityPID.SetReference(vlimit, rev::ControlType::kVelocity);
}

// Used internally only for dashboard
double Shooter::GetBottomMotorSpeed() {
    return m_bottomEncoder.GetVelocity();
}

// Used internally only for dashboard
double Shooter::GetTopMotorSpeed() {
    return m_topEncoder.GetVelocity();
}

// Used internally only for dashboard
double Shooter::GetKickerMotorVoltage() {
    return m_kickerMotor.GetMotorOutputVoltage();
}

// Used internally only for dashboard
double Shooter::GetKickerError() {
    return m_kickerMotor.GetClosedLoopError();
}

// Used by SpinUpShooter
void Shooter::SpinUp()
{
  SetTopMotorSpeed(m_nte_TopMotorInputRPM.GetDouble(ConShooter::Top::OPTIMAL_RPM));
  SetBottomMotorSpeed(m_nte_BottomMotorInputRPM.GetDouble(ConShooter::Bottom::OPTIMAL_RPM));
  SetKickerSpeed(m_nte_KickerMotorSpeed.GetDouble(ConShooter::Kicker::OPTIMAL_RPM));
}

// Used by SpinUpShooter
void Shooter::StopSpinUp(){
  //SetTopMotorSpeed(0.0);
  //SetBottomMotorSpeed(0.0);
  m_topVelocityPID.SetReference(0.0, rev::ControlType::kVoltage);
  m_bottomVelocityPID.SetReference(0.0, rev::ControlType::kVoltage);
  SetKickerSpeed(0.0);
}

// Used by JumbleShooter
void Shooter::Jumble(int direction) {
  double speed = m_nte_JumblerMotorSpeed.GetDouble(ConShooter::Jumbler::MOTOR_SPEED);
  if (direction != 1) { speed = -speed; }
  m_jumblerMotor.Set(TalonSRXControlMode::PercentOutput, speed);
  m_hopperFlapper.Set(TalonSRXControlMode::PercentOutput, ConShooter::HopperFlapper::MOTOR_SPEED);
}

// Used by JumbleShooter
void Shooter::Dejumble() {
  m_jumblerMotor.Set(TalonSRXControlMode::PercentOutput, 0.0);
  m_hopperFlapper.Set(TalonSRXControlMode::PercentOutput, 0.0);
}

// Used internally only
void Shooter::SetKickerSpeed(double speed) {
  // Power Mode...
  // m_kickerMotor.Set(TalonSRXControlMode::PercentOutput, speed);
  /// Velocity Mode for use with hex shaft encoder
  m_kickerMotor.Set(TalonSRXControlMode::Velocity, speed); 
}

#endif // ENABLE_SHOOTER
