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

#ifdef ENABLE_SHOOTER
// Called when the command is initially scheduled.
void SpinUpFarShooter::Initialize() {
// FIXME (CRE): Is this where we set the calibrated values for RPM?
// FIXME (CRE): Write calibrated values to the shuffleboard and NT
}

// Called repeatedly when this Command is scheduled to run
void SpinUpFarShooter::Execute() {
  // FIXME (CRE): Read the (possibly updated) Motor RPM values from the shuffleboard and write to NT
} 

// Called once the command ends or is interrupted.
void SpinUpFarShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool SpinUpFarShooter::IsFinished() { return false; }
#endif // ENABLE_SHOOTER