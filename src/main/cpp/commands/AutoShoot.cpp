/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoShoot.h"

AutoShoot::AutoShoot(Shooter *shooter) : m_shooter(shooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  timer = frc::Timer();
}

// Called when the command is initially scheduled.
void AutoShoot::Initialize() {
  timer.Reset();
  timer.Start();
  m_feeding = false;
}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {
  m_shooter->SpinUp();
  if (timer.Get() > 0.5) {
    if (int(timer.Get() * 10) % 3 == 0) // Turn the feeder on and off every 0.3 seconds
    {
      m_feeding = !m_feeding;
    }
  }

  if (m_feeding) {
    //FIXME: make this read the networktable jumbler speed
    m_shooter->Jumble(1);
  } else {
    m_shooter->Dejumble();
  }


}

// Called once the command ends or is interrupted.
void AutoShoot::End(bool interrupted) {
  m_shooter->StopSpinUp();
  m_shooter->Dejumble();
}

// Returns true when the command should end.
bool AutoShoot::IsFinished() { return timer.Get() >= 10.0; }
