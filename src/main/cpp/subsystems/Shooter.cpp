/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"

Shooter::Shooter() {}

void Shooter::SpinUp()
{
  m_topMotor.Set(ConShooter::TOP_MOTOR_SPEED);
  m_bottomMotor.Set(ConShooter::BOTTOM_MOTOR_SPEED);
}

void Shooter::SpinTop()
{
  m_topMotor.Set(ConShooter::TOP_MOTOR_SPEED);
}

void Shooter::SpinBottom()
{
  m_bottomMotor.Set(ConShooter::BOTTOM_MOTOR_SPEED);
}

void Shooter::StopSpinUp(){
  m_topMotor.Set(0.0);
  m_bottomMotor.Set(0.0);
}

void Shooter::StopTop(){
  m_topMotor.Set(0.0);
}

void Shooter::StopBottom(){
  m_bottomMotor.Set(0.0);
}

void Shooter::Activate() {
  m_feedMotor.Set(ConShooter::FEED_MOTOR_SPEED);
}

void Shooter::Deactivate() {
  m_feedMotor.Set(0.0);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}
