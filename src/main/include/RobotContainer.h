/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include "commands/AutoDriveDistance.h"
#include "subsystems/DriveTrain.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  DriveTrain m_driveTrain;

  //FIXME: change to AutoDrive instead of AutoDriveDistance for the auto command group
  AutoDriveDistance m_autoDriveDistance;
  /*
  EXAMPLE:
  int m_x;
  string m_name; 

  WHERE:
  int and string are types
  m_x and m_name are members of the RobotContainer

  SO:
  DriveTrain m_driveTrain;
  DriveTrain is the type
  m_driveTrain is the member of RobotContainer
  */

  void ConfigureButtonBindings();
};
