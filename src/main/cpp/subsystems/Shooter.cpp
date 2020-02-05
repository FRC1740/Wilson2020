/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"

Shooter::Shooter() {}

void Shooter::SpinUp(double speed)
{
    SpinUpMotor.Set(speed);

}

void Shooter::SpinTop(double speed)
{
    TopMotor.Set(speed);
}

void Shooter::SpinBottom(double speed)
{
    BottomMotor.Set(speed);
}

void Shooter::StopSpinUp(){
    SpinUpMotor.Set(0.0);
}

void Shooter::StopTop(){
    TopMotor.Set(0.0);
}

void Shooter::StopBottom(){
    BottomMotor.Set(0.0);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}
