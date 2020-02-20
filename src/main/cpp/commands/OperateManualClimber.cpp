/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OperateManualClimber.h"
#include "subsystems/Climber.h"

OperateManualClimber::OperateManualClimber(Climber *climber, std::function<double()> speed) : m_climber(climber), m_speed(speed) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

// Called when the command is initially scheduled.
void OperateManualClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void OperateManualClimber::Execute() {
  m_climber->Go(m_speed());
}

// Called once the command ends or is interrupted.
void OperateManualClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool OperateManualClimber::IsFinished() { return false; }
