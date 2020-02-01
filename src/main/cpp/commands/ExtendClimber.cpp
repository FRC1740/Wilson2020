/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendClimber.h"

ExtendClimber::ExtendClimber(Climber *climber) : m_climber(climber) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

// Called when the command is initially scheduled.
void ExtendClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ExtendClimber::Execute() {}

// Called once the command ends or is interrupted.
void ExtendClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool ExtendClimber::IsFinished() { return false; }
