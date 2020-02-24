/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "commands/AutoDriveDistance.h"
#include "commands/AutoDriveAngle.h"
#include "commands/AutoShoot.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html

AutoDrive::AutoDrive(DriveTrain *drivetrain, Shooter *shooter) {
#if 0 //def ENABLE_DRIVETRAIN
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands (
    AutoDriveDistance(drivetrain, 10.0),
    //AutoDriveAngle(drivetrain, 90),
    AutoDriveDistance(drivetrain, -10.0),
    AutoShoot(shooter)
  );
#endif // ENABLE_DRIVETRAIN
}
