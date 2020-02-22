/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OperateManualClimber.h"
#include "subsystems/Climber.h"

OperateManualClimber::OperateManualClimber(Climber *climber) : m_climber(climber) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

// Called when the command is initially scheduled.
void OperateManualClimber::Initialize() {
  m_climber->Unlock();
}

// Called repeatedly when this Command is scheduled to run
void OperateManualClimber::Execute() {
//  double speed = -m_climber->m_codriver_control->GetRawAxis(ConLaunchPad::RIGHT_STICK_Y);
  double speed = -m_climber->m_codriver_control->GetRawAxis(0);
  m_climber->Go(speed);
}

// Called once the command ends or is interrupted.
void OperateManualClimber::End(bool interrupted) {
  m_climber->Stop();
  m_climber->Lock();
}

// Returns true when the command should end.
bool OperateManualClimber::IsFinished() { return false; }
