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
    m_topVelocityPID.SetOutputRange(0,1);
    
    m_bottomVelocityPID.SetP(ConShooter::Bottom::P);
    m_bottomVelocityPID.SetI(ConShooter::Bottom::I);
    m_bottomVelocityPID.SetD(ConShooter::Bottom::D);
    m_bottomVelocityPID.SetFF(ConShooter::Bottom::FF);
    m_bottomVelocityPID.SetOutputRange(0,1);
    
#endif // ENABLE_SHOOTER
  // Create and get reference to SB tab
  m_sbt_Shooter = &frc::Shuffleboard::GetTab(ConShuffleboard::ShooterTab);

  // Create widgets for motors
  // FIXME: Still needs work on Widget Type and Properties- can't find valid WPI examples
  //wpi::StringMap propertiesTop = {
  //  std::make_pair("min", nt::Value::MakeDouble(0)),
  //  std::make_pair("max", nt::Value::MakeDouble(4000))
  //};
  //wpi::StringMap propertiesBottom = {
  //  std::make_pair("min", nt::Value::MakeDouble(0)),
  //  std::make_pair("max", nt::Value::MakeDouble(4000))
  //};

  m_nte_TopMotorRPM = m_sbt_Shooter->
    AddPersistent("Top Motor RPM", ConShooter::Top::MOTOR_SPEED)
    //.WithWidget(&frc::BuiltInWidgets::kDial),
    //.WithProperties(propertiesTop)
    .WithSize(3, 3)
    .WithPosition(0, 0)
    .GetEntry();

  m_nte_BottomMotorRPM = m_sbt_Shooter->
    AddPersistent("Bottom Motor RPM", ConShooter::Bottom::MOTOR_SPEED)
    //.WithWidget(&frc::BuiltInWidgets::kDial),
    //.WithProperties(propertiesBottom)
    .WithSize(3, 3)
    .WithPosition(0, 3)
    .GetEntry();

  m_nte_FeederMotorSpeed = m_sbt_Shooter->
    AddPersistent("Feeder Motor Speed", ConShooter::Feeder::MOTOR_SPEED)
    .WithSize(3, 3)
    .WithPosition(0, 6)
    .GetEntry();

  m_nte_HopperMotorSpeed = m_sbt_Shooter->
    AddPersistent("Hopper Motor Speed", ConShooter::Hopper::MOTOR_SPEED)
    .WithSize(3, 3)
    .WithPosition(0, 9)
    .GetEntry();
}

#ifdef ENABLE_SHOOTER
// This method will be called once per scheduler run
void Shooter::Periodic() {

    // Update Netwwork Table/Shuffleboard Values
    m_nte_TopMotorRPM.GetDouble(0.0);
    m_nte_BottomMotorRPM.GetDouble(0.0);
    m_nte_FeederMotorSpeed.GetDouble(0.0);
    m_nte_HopperMotorSpeed.GetDouble(0.0);

	// Check TimeofFLight sensor to see if a powerCell is ... stuck? loaded? ??
  /* NOT PLANNING TO USE THIS SENSOR
    frc::SmartDashboard::PutNumber("Range: ", m_powerCellDetector.GetRange());
    if (m_powerCellDetector.GetRange() < 300.0)  { // FIXME: range in mm 
        frc::SmartDashboard::PutBoolean("PowerCell", true);
    }
    else {
        frc::SmartDashboard::PutBoolean("PowerCell", false);
    } 
    */
}

void Shooter::SetBottomMotorSpeed(double velocity) {
    m_bottomVelocityPID.SetReference(velocity, rev::ControlType::kVelocity);
}

void Shooter::SetTopMotorSpeed(double velocity) {
    m_topVelocityPID.SetReference(velocity, rev::ControlType::kVelocity);
}

double Shooter::GetBottomMotorSpeed() {
    return m_bottomEncoder.GetVelocity();
}

double Shooter::GetTopMotorSpeed() {
    return m_topEncoder.GetVelocity();
}

void Shooter::SpinUp()
{
#if 1 // from Wes
  SetTopMotorSpeed(m_nte_TopMotorRPM.GetDouble(0.0));
  SetBottomMotorSpeed(m_nte_BottomMotorRPM.GetDouble(0.0));
  SetFeedSpeed(m_nte_FeederMotorSpeed.GetDouble(0.0));  
#else
  m_topMotor.Set(ConShooter::Top::MOTOR_SPEED);
  m_bottomMotor.Set(ConShooter::Bottom::MOTOR_SPEED);
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, ConShooter::Feeder::MOTOR_SPEED);
#endif
}

//void Shooter::SpinTop()
//{
//  m_topMotor.Set(ConShooter::Top::MOTOR_SPEED);
//}

//void Shooter::SpinBottom()
//{
//  m_bottomMotor.Set(ConShooter::Bottom::MOTOR_SPEED);
//}

void Shooter::StopSpinUp(){
  m_topMotor.Set(0.0);
  m_bottomMotor.Set(0.0);
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

//void Shooter::StopTop(){
//  m_topMotor.Set(0.0);
//}

//void Shooter::StopBottom(){
//  m_bottomMotor.Set(0.0);
//}

void Shooter::Activate() {
  m_hopperMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, ConShooter::Hopper::MOTOR_SPEED);
  //  Change to:  , m_nte_FeederMotorSpeed.GetDouble(0.0));  
}

void Shooter::Deactivate() {
  m_hopperMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Shooter::SetFeedSpeed(double speed) {
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

// Hopper is covered by Activate/Deactivate
//void Shooter::SetHopperSpeed(double speed) {
//  m_hopperMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
//}

#endif // ENABLE_SHOOTER
