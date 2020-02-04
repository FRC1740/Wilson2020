/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter() {
    // Invert
    m_topMotor.SetInverted(false);
    m_bottomMotor.SetInverted(true);
    //Set velocity of shaft relative to velocity of wheel
    m_topEncoder.SetVelocityConversionFactor(ConShooter::Top::VELOCITY_FACTOR);
    m_bottomEncoder.SetVelocityConversionFactor(ConShooter::Bottom::VELOCITY_FACTOR);

    //Set controller gains
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
    m_topVelocityPID = m_topMotor.GetPIDController();
    m_bottomVelocityPID = m_bottomMotor.GetPIDController();

}

// This method will be called once per scheduler run
void Shooter::Periodic() {
	// Check TimeofFLight sensor to see if a powerCell is ... stuck? loaded? ??
	if (m_powerCellDetector.GetRange() > 0.0) {
		frc::SmartDashboard::PutBoolean("PowerCell", false);
	}
	else {
		frc::SmartDashboard::PutBoolean("PowerCell", true);
	}
}

void SetBottomMotorSpeed(double velocity) {
    m_bottomVelocityPID.SetReference(velocity, rev::ControlType::kVelocity);
}

void SetTopMotorSpeed(double velocity) {
    m_topVelocityPID.SetReference(velocity, rev::ControlType::kVelocity);
}

double GetBottomMotorSpeed() {
    return m_bottomEncoder.GetVelocity();
}

double GetTopMotorSpeed() {
    return m_topEncoder.GetVelocity();
}

