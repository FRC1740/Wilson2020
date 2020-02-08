/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignToPlayerStation.h"

AlignToPlayerStation::AlignToPlayerStation(Vision *vision, DriveTrain *drive) : m_vision(vision), m_drive(drive) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(vision);
  AddRequirements(drive);
}

// Called when the command is initially scheduled.
void AlignToPlayerStation::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignToPlayerStation::Execute() {
  rotation_factor = m_vision->Align();
  m_drive->TankDrive(rotation_factor, -rotation_factor);
}

// Called once the command ends or is interrupted.
void AlignToPlayerStation::End(bool interrupted) {}

// Returns true when the command should end.
//FIXME: this can probably be a PIDcontroller
bool AlignToPlayerStation::IsFinished() { 
  
  if (std::abs(m_vision->Align()) < ConVision::I){
    return true;
  }
  
  
  return false; 

}
