/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SpinUpFarShooter.h"

SpinUpFarShooter::SpinUpFarShooter(Shooter *shooter) : m_shooter(shooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(shooter);
}

// Called when the command is initially scheduled.
void SpinUpFarShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SpinUpFarShooter::Execute() {}

// Called once the command ends or is interrupted.
void SpinUpFarShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool SpinUpFarShooter::IsFinished() { return false; }
