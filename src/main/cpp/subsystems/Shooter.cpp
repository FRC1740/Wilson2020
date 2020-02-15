/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

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
    
    frc::SmartDashboard::PutNumber("Top Motor RPM", 0.0);
    frc::SmartDashboard::PutNumber("Bottom Motor RPM", 0.0);
    frc::SmartDashboard::PutNumber("Feeder Speed", 0.0);
#endif // ENABLE_SHOOTER
}

#ifdef ENABLE_SHOOTER
// This method will be called once per scheduler run
void Shooter::Periodic() {
	// Check TimeofFLight sensor to see if a powerCell is ... stuck? loaded? ??
    frc::SmartDashboard::PutNumber("Range: ", m_powerCellDetector.GetRange());
    if (m_powerCellDetector.GetRange() < 300.0)  { // FIXME: range in mm 
        frc::SmartDashboard::PutBoolean("PowerCell", true);
    }
    else {
        frc::SmartDashboard::PutBoolean("PowerCell", false);
    }
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
  m_topMotor.Set(frc::SmartDashboard::GetNumber("Top Motor RPM", 0.0));
  m_bottomMotor.Set(frc::SmartDashboard::GetNumber("Bottom Motor RPM", 0.0));
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 
    frc::SmartDashboard::GetNumber("Feeder Speed", 0.0));
#else
  m_topMotor.Set(ConShooter::Top::MOTOR_SPEED);
  m_bottomMotor.Set(ConShooter::Bottom::MOTOR_SPEED);
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, ConShooter::Feeder::MOTOR_SPEED);
#endif
}

void Shooter::SpinTop()
{
  m_topMotor.Set(ConShooter::Top::MOTOR_SPEED);
}

void Shooter::SpinBottom()
{
  m_bottomMotor.Set(ConShooter::Bottom::MOTOR_SPEED);
}

void Shooter::StopSpinUp(){
  m_topMotor.Set(0.0);
  m_bottomMotor.Set(0.0);
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Shooter::StopTop(){
  m_topMotor.Set(0.0);
}

void Shooter::StopBottom(){
  m_bottomMotor.Set(0.0);
}

void Shooter::Activate() {
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, ConShooter::Feeder::MOTOR_SPEED);
}

void Shooter::Deactivate() {
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Shooter::SetFeedSpeed(double speed) {
  m_feedMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Shooter::SetHopperSpeed(double speed) {
  m_hopperMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

#endif // ENABLE_SHOOTER
