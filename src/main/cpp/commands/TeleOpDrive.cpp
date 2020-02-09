/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleOpDrive.h"

TeleOpDrive::TeleOpDrive(DriveTrain *drivetrain,
                         std::function<double()> speed,
                         std::function<double()> rotation)
            : m_driveTrain(drivetrain),
              m_speed(speed),
              m_rotation(rotation) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

#ifdef ENABLE_DRIVETRAIN
// Called when the command is initially scheduled.
void TeleOpDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TeleOpDrive::Execute() {
  m_driveTrain->ArcadeDrive(m_speed(), m_rotation());
}

// Called once the command ends or is interrupted.
void TeleOpDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool TeleOpDrive::IsFinished() { return false; }

#endif // ENABLE_DRIVETRAIN
