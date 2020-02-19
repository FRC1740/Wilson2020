/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StarveShooterJumbler.h"

StarveShooterJumbler::StarveShooterJumbler(Jumbler *jumbler) : m_jumbler(jumbler) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(jumbler);
}

// Called when the command is initially scheduled.
void StarveShooterJumbler::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StarveShooterJumbler::Execute() {}

// Called once the command ends or is interrupted.
void StarveShooterJumbler::End(bool interrupted) {}

// Returns true when the command should end.
bool StarveShooterJumbler::IsFinished() { return false; }
