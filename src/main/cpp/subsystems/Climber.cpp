/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

Climber::Climber() {}

void Climber::ExtendClimber(double speed)
{
    ClimbMotor.Set(speed);
}

void Climber::RetractClimber(double speed)
{

    ClimbMotor.Set(speed);

}

void Climber::StopClimber()
{

    ClimbMotor.Set(0.0);

}

// This method will be called once per scheduler run
void Climber::Periodic() {}
