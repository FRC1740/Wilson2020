/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"

Vision::Vision() {
    m_nt_Limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
#ifdef ENABLE_VISION
    Vision::LightOff();
#endif
}

#ifdef ENABLE_VISION
// This method will be called once per scheduler run
void Vision::Periodic() {}

double Vision::Align() {
    m_nte_tx = m_nt_Limelight->GetNumber("tx", 0.0);
    return m_nte_tx;
}

void Vision::ToggleLight() {
    if (m_nt_Limelight->GetNumber("ledMode", ConVision::ON) == ConVision::OFF) {
        m_nt_Limelight->PutNumber("ledMode", ConVision::ON);
    } 
    else {
        m_nt_Limelight->PutNumber("ledMode", ConVision::OFF);
    }
}

void Vision::LightOn() {
    m_nt_Limelight->PutNumber("ledMode", ConVision::ON);
}

void Vision::LightOff() {
    m_nt_Limelight->PutNumber("ledMode", ConVision::OFF);
}

void Vision::SelectPlayerStationPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 0);
}

void Vision::SelectNearGoalPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 1);
}

void Vision::SelectFarGoalPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 2);
}
#endif // ENABLE_VISION
