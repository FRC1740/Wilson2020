/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDriveAngle.h"

AutoDriveAngle::AutoDriveAngle(DriveTrain *drivetrain) : m_driveTrain(drivetrain) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

// Called when the command is initially scheduled.
void AutoDriveAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAngle::Execute() {}

// Called once the command ends or is interrupted.
void AutoDriveAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoDriveAngle::IsFinished() { return false; }
