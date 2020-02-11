/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"

Vision::Vision() {
}

// This method will be called once per scheduler run
void Vision::Periodic() {
    //FIXME: this is deprecated
    table = NetworkTable::GetTable("limelight");
}

double Vision::Align(){
    tx = table->GetNumber("tx", 0.0);
    steering_adjust = ConVision::P * tx;
    return steering_adjust;
}

void Vision::ToggleLight(){
    /*
    3 = On
    2 = Blink
    1 = Off
    */

    if (table->GetNumber("ledMode", 3) == 1)
    {
        table->PutNumber("ledMode", 3);

    } 
    else

    {
        table->PutNumber("ledMode", 1);
    }
    

}
