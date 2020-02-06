/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractClimber.h"

RetractClimber::RetractClimber(Climber *climber) : m_climber(climber) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

#ifdef ENABLE_CLIMBER
// Called when the command is initially scheduled.
void RetractClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RetractClimber::Execute() {
  m_climber->RetractClimber(ConClimber::RET_SPEED);
}

// Called once the command ends or is interrupted.
void RetractClimber::End(bool interrupted) {
  m_climber->StopClimber();
}

// Returns true when the command should end.
bool RetractClimber::IsFinished() { return false; }
#endif // ENABLE_CLIMBER
