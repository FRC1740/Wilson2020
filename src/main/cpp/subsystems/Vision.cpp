/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"

Vision::Vision() {
    m_tabLimelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

#ifdef ENABLE_VISION
// This method will be called once per scheduler run
void Vision::Periodic() {}

double Vision::Align(){
    m_tx = m_tabLimelight->GetNumber("tx", 0.0);
    return m_tx;
}

void Vision::ToggleLight(){
    constexpr int ON = 3;
    //constexpr int BLINK = 2;
    constexpr int OFF = 1;

    if (m_tabLimelight->GetNumber("ledMode", ON) == OFF)
    {
        m_tabLimelight->PutNumber("ledMode", ON);
    } 
    else
    {
        m_tabLimelight->PutNumber("ledMode", OFF);
    }
}
#endif // ENABLE_VISION
