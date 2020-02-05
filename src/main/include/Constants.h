/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <cmath>  // for std::fabs

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace ConAuto {
    // Conversion factor Ticks -> Inches
    constexpr double ENCODER_TICKS_TO_INCHES = 2.0 + (2/9); // 0.58
    constexpr double ENCODER_TICKS_OFFSET = -6.0 - (2/3);
}

namespace ConClimber {
    // Motor
    constexpr int MOTOR_ID = 9;
    constexpr double EXT_SPEED = 1.0;
    constexpr double RET_SPEED = -1.0;
}

namespace ConControlPanelManipulator {
    // Motor
    constexpr int MOTOR_ID = 3;
    constexpr double MOTOR_SPEED = 0.324; // FIXME: Guess & Check
}

namespace ConDriveTrain {
    // Motors
    constexpr int RIGHT_MOTOR_A_ID = 4;
    constexpr int RIGHT_MOTOR_B_ID = 5;
    constexpr int LEFT_MOTOR_A_ID = 6;
    constexpr int LEFT_MOTOR_B_ID = 7;
    constexpr double ROTATION_FACTOR = 1/1.3;
}

namespace ConMath {
    constexpr double PI = 3.141592;
    constexpr double METERS_2_INCH = .0254; // m/in
    constexpr double MINUTES_2_SECONDS = 1/60.; // sec/min
}

namespace ConNEO {
    constexpr int MAXIMUM_RPM = 5676;
    constexpr int GEAR_RATIO = 10.71;
}

namespace ConShooter {
    // Motors
    constexpr int FEED_MOTOR_ID = 1;
    constexpr int TOP_MOTOR_ID = 6;
    constexpr int TOP_MOTOR_WHEEL_SIZE = 6;
    constexpr int BOTTOM_MOTOR_ID = 4;
    constexpr int BOTTOM_MOTOR_WHEEL_SIZE = 4;
    constexpr double FEED_MOTOR_SPEED = 0.75;
    constexpr double TOP_MOTOR_SPEED = 0.25;
    constexpr double BOTTOM_MOTOR_SPEED = 0.25;
    constexpr double P = 2e-4;
    constexpr double I = 0.0;
    constexpr double D = 2e-3;
    constexpr double FF = 1.7e-4;
}

namespace ConXBOXControl {
    // Axis inputs
    constexpr int LEFT_JOYSTICK_X = 0;
    constexpr int LEFT_JOYSTICK_Y = 1;
    constexpr int LEFT_TRIGGER = 2;
    constexpr int RIGHT_TRIGGER = 3;
    constexpr int RIGHT_JOYSTICK_X = 4;
    constexpr int RIGHT_JOYSTICK_Y = 5;
    // Buttons
    constexpr int A = 1;
    constexpr int B = 2;
    constexpr int X = 3;
    constexpr int Y = 4;
    constexpr int LEFT_BUMPER = 5;
    constexpr int RIGHT_BUMPER = 6;
    constexpr int SELECT = 7;
    constexpr int START = 8;
    constexpr int LEFT_JOYSTICK = 9;
    constexpr int RIGHT_JOYSTICK = 10;

    // Dead zone
    constexpr double DEAD_ZONE = 0.5; //approximate value

    // Driver controller Port
    constexpr int DRIVER_CONTROLLER_PORT = 0;
    // CoDriver controller port
    constexpr int CODRIVER_CONTROLLER_PORT = 1;
}

// DeadZone lambda function
auto DeadZone = [] (double a) { return (std::fabs(a) > ConXBOXControl::DEAD_ZONE) ? a : 0.0; };
