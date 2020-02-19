/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FeedShooterJumbler.h"

FeedShooterJumbler::FeedShooterJumbler(Jumbler *jumbler) : m_jumbler(jumbler) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(jumbler);
}

// Called when the command is initially scheduled.
void FeedShooterJumbler::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FeedShooterJumbler::Execute() {}

// Called once the command ends or is interrupted.
void FeedShooterJumbler::End(bool interrupted) {}

// Returns true when the command should end.
bool FeedShooterJumbler::IsFinished() { return false; }
