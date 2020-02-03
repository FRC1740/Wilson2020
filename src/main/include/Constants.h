/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

//THESE ARE ALL DUMMY VALUES FOR A SIMPLE AUTO
namespace ConAuto {

}

namespace ConClimber {
    //Motors
    constexpr int CLIMB_MOTOR = 9;
}

namespace ConControlPanelManipulator {
    // Motor
    constexpr int MOTOR = 3;
    constexpr double MOTOR_SPEED = 0.324; // FIXME: Guess & Check
}

namespace ConDrivetrain {
    //Motors
    constexpr int RIGHT_MOTOR = 4;
    constexpr int LEFT_MOTOR = 5;
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
   
}

namespace ConXBOXControl {
    //Axis inputs
    constexpr int LEFT_JOYSTICK_X = 0;    
    constexpr int LEFT_JOYSTICK_Y = 1;
    constexpr int LEFT_TRIGGER = 2;
    constexpr int RIGHT_TRIGGER = 3;
    constexpr int RIGHT_JOYSTICK_X = 4;    
    constexpr int RIGHT_JOYSTICK_Y = 5;
    //Buttons
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

    // FIXME: CREATE A TEMPLATE TO ENABLE THIS
    //Dead zone
    constexpr double DEAD_ZONE = 0.5; //approximate value

    //Driver controller Port
    constexpr int DRIVER_CONTROLLER_PORT = 0;
    constexpr int CODRIVER_CONTROLLER_PORT = 1;
}

