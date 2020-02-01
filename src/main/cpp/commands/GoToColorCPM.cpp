/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GoToColorCPM.h"

GoToColorCPM::GoToColorCPM(ControlPanelManipulator *controlpanelmanipulator) : m_controlPanelManipulator(controlpanelmanipulator) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(controlpanelmanipulator);
}

// Called when the command is initially scheduled.
void GoToColorCPM::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void GoToColorCPM::Execute() {}

// Called once the command ends or is interrupted.
void GoToColorCPM::End(bool interrupted) {}

// Returns true when the command should end.
bool GoToColorCPM::IsFinished() { return false; }
