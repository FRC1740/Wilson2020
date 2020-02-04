/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter() {

}

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

void SetBottomMotorSpeed(double velocity) {
}

void SetTopMotorSpeed(double velocity) {
}

double GetBottomMotorSpeed() {
}

double GetTopMotorSpeed() {
}

