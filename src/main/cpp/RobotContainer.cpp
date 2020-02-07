/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Button.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/AutoDrive.h"
#include "commands/TeleOpDrive.h"
#include "commands/ExtendClimber.h"
#include "commands/RetractClimber.h"
#include "commands/SpinUpShooter.h"
#include "commands/ActivateShooter.h"
#include "commands/AlignToPlayerStation.h"
#include "commands/AlignToPowerPort.h"
#include "commands/SwitchCamera.h"
#include "commands/ToggleVisionLight.h"
#include "commands/RotateThreeCPM.h"
#include "commands/GoToColorCPM.h"
#include "commands/RotateManualCPM.h"

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_autoDrive(&m_driveTrain) {
  // ANOTHER WAY OF CONSTRUCTING: m_autoDriveDistance = AutoDriveDistance(&m_driveTrain);
  
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

#ifdef ENABLE_DRIVETRAIN
  // Set up default drive command
  m_driveTrain.SetDefaultCommand(TeleOpDrive(
    &m_driveTrain,
    [this] { return driver_control.GetRawAxis(ConXBOXControl::RIGHT_TRIGGER) - driver_control.GetRawAxis(ConXBOXControl::LEFT_TRIGGER); },
    [this] { return driver_control.GetRawAxis(ConXBOXControl::RIGHT_JOYSTICK_X); }));
#endif // ENABLE_DRIVETRAIN
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

#ifdef ENABLE_CLIMBER
  // Climber
  //FIXME: Test these
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::X); }).WhenHeld(new ExtendClimber(&m_climber));
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::Y); }).WhenHeld(new RetractClimber(&m_climber));
#endif // ENABLE_CLIMBER

  // Shooter
  //FIXME: Test these
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::LEFT_BUMPER); }).WhenHeld(new SpinUpShooter(&m_shooter));
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::RIGHT_BUMPER); }).WhenHeld(new ActivateShooter(&m_shooter));

  // Vision
  frc2::Button([this] {return driver_control.GetRawButton(ConXBOXControl::SELECT); }).WhenHeld(new AlignToPlayerStation(&m_vision));
  frc2::Button([this] {return driver_control.GetRawButton(ConXBOXControl::START); }).WhenHeld(new AlignToPowerPort(&m_vision));
  frc2::Button([this] {return driver_control.GetRawButton(ConXBOXControl::X); }).WhenHeld(new SwitchCamera(&m_vision));
  frc2::Button([this] {return driver_control.GetRawButton(ConXBOXControl::Y); }).WhenHeld(new ToggleVisionLight(&m_vision));

  // ControlPanelManipulator
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::A); }).WhenPressed(new RotateThreeCPM(&m_controlPanelManipulator));
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::B); }).WhenPressed(new GoToColorCPM(&m_controlPanelManipulator), false);
  // FIXME: Combine these two?
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::LEFT_TRIGGER); }).WhenHeld(new RotateManualCPM(&m_controlPanelManipulator));
  frc2::Button([this] {return codriver_control.GetRawButton(ConXBOXControl::RIGHT_TRIGGER); }).WhenHeld(new RotateManualCPM(&m_controlPanelManipulator));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autoDrive;
}
