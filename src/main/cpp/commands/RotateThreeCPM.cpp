/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RotateThreeCPM.h"

RotateThreeCPM::RotateThreeCPM(ControlPanelManipulator *controlpanelmanipulator) : m_controlPanelManipulator(controlpanelmanipulator) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(controlpanelmanipulator);
}

// Called when the command is initially scheduled.
void RotateThreeCPM::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RotateThreeCPM::Execute() {}

// Called once the command ends or is interrupted.
void RotateThreeCPM::End(bool interrupted) {}

// Returns true when the command should end.
bool RotateThreeCPM::IsFinished() { return false; }
