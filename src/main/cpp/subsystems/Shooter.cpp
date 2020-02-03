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
    top_motor.SetInverted(false);
    bottom_motor.SetInverted(true);
    //Set velocity of shaft relative to velocity of wheel
    top_encoder.SetVelocityConversionFactor(ConShooter::Top::VELOCITY_FACTOR);
    bottom_encoder.SetVelocityConversionFactor(ConShooter::Bottom::VELOCITY_FACTOR);

    //Set controller gains
    top_velocity_PID.SetP(ConShooter::Top::P);
    top_velocity_PID.SetI(ConShooter::Top::I);
    top_velocity_PID.SetD(ConShooter::Top::D);
    top_velocity_PID.SetFF(ConShooter::Top::FF);
    top_velocity_PID.SetOutputRange(0,1);
    
    bottom_velocity_PID.SetP(ConShooter::Bottom::P);
    bottom_velocity_PID.SetI(ConShooter::Bottom::I);
    bottom_velocity_PID.SetD(ConShooter::Bottom::D);
    bottom_velocity_PID.SetFF(ConShooter::Bottom::FF);
    bottom_velocity_PID.SetOutputRange(0,1);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
	// Check TimeofFLight sensor to see if a powerCell is ... stuck? loaded? ??
	if (powerCellDetector.GetRange() > 0.0) {
		frc::SmartDashboard::PutBoolean("PowerCell", false);
	}
	else {
		frc::SmartDashboard::PutBoolean("PowerCell", true);
	}
}

void SetBottomMotorSpeed(double velocity) {
    bottom_velocity_PID.SetReference(velocity, rev::ControlType::kVelocity);
}

void SetTopMotorSpeed(double velocity) {
    top_velocity_PID.SetReference(velocity, rev::ControlType::kVelocity);
}

double GetBottomMotorSpeed() {
    return bottom_encoder.GetVelocity();
}

double GetTopMotorSpeed() {
    return top_encoder.GetVelocity();
}

