/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//On error, create env.h from env-default.h and modify ROBOT_VERSION_STRING
#include "env-default.h"  //FIXME: change to env.h and add env.h to .gitignore

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

namespace ConMath {
    constexpr double PI = 3.141592;
    constexpr double METERS_2_INCH = .0254; // m/in
    constexpr double MINUTES_2_SECONDS = 1/60.; // sec/min
}

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
    constexpr double MOTOR_SPEED = 810; // 30 RPM x 27:1 = 810 motor RPM, 1 rotation every 2 seconds
    // PID Constants for TalonSRX
    enum Constants {
        /**
         * Which PID slot to pull gains from.  Starting 2018, you can choose
         * from 0,1,2 or 3.  Only the first two (0,1) are visible in web-based configuration.
         */
        kSlotIdx = 0,

        /* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
        * For now we just want the primary one.
        */
        kPIDLoopIdx = 0,

        /*
        * set to zero to skip waiting for confirmation, set to nonzero to wait
        * and report to DS if action fails.
        */
        kTimeoutMs = 30
    };
}

namespace ConDriveTrain {
    // Motors
    constexpr int RIGHT_MOTOR_A_ID = 2;
    constexpr int RIGHT_MOTOR_B_ID = 4;
    constexpr int LEFT_MOTOR_A_ID = 3;
    constexpr int LEFT_MOTOR_B_ID = 5;
    constexpr double ROTATION_FACTOR = 1/1.3;

    //Spark Max Settings
    constexpr int RAMP_RATE = 0.100; //seconds
    constexpr bool INVERSION = false; //
    //Conversions
    constexpr double IN_2_ENCODER = (10.71*42)/(6*ConMath::PI); //encoder to motor 42 counts/rev, motor to shaft 10.71:1, 6in wheel
    constexpr double ENCODER_2_IN = 1/IN_2_ENCODER; 
}

namespace ConLimelight {
    constexpr int VISION_MODE = 0;
    constexpr int CAMERA_MODE = 1;

    constexpr int LED_PIPLINE_DEFAULT = 0;
    constexpr int LED_OFF = 1;
    constexpr int LED_BLINK = 2;
    constexpr int LED_ON = 3;

    constexpr int SNAPSHOT_STOP = 0;
    constexpr int SNAPSHOT_START = 1;

    constexpr double HORIZONTAL_TOLERANCE = 1.0;  //degrees
    constexpr double TARGET_HEIGHT = 38.5; //in to center of target
    constexpr double CAMERA_HEIGHT = 19.5; //in to center of camera
    constexpr double MAX_HORIZONTAL_OFFSET = 29.8; //degrees

    // constexpr cv::Matx33d cameraMatrix = cv::Matx33d(
    //                     772.53876202, 0., 479.132337442,
    //                     0., 769.052151477, 359.143001808,
    //                     0., 0., 1.0);
    // constexpr std::vector istortionCoefficient =  std::vector<double> {
    //                     2.9684613693070039e-01, -1.4380252254747885e+00,-2.2098421479494509e-03,
    //                     -3.3894563533907176e-03, 2.5344430354806740e+00};

    constexpr double focalLength = 2.9272781257541; //mm
}

namespace ConNEO {
    constexpr int MAXIMUM_RPM = 5676;
    constexpr int GEAR_RATIO = 10.71;
}

namespace ConShooter {
    namespace Top {
        constexpr int MOTOR_ID = 9;
        constexpr int WHEEL_SIZE = 4; //in inches
        constexpr double VELOCITY_FACTOR = 1; //(ConMath::PI*WHEEL_SIZE) * ConMath::METERS_2_INCH * ConMath::MINUTES_2_SECONDS; //(velocity) y [m/s] = PI*WHEEL_SIZE * m/in * 1/60 * x [RPM]
        constexpr double MOTOR_SPEED = 0.5;
        //PID gains
        constexpr double P = 2e-4;
        constexpr double I = 0.0;
        constexpr double D = 2e-3;
        constexpr double FF = 1.7e-4;
    }
    namespace Bottom {
        constexpr int MOTOR_ID = 12;
        constexpr int WHEEL_SIZE = 6; //in inches
        constexpr double VELOCITY_FACTOR = 1; //(ConMath::PI*WHEEL_SIZE) * ConMath::METERS_2_INCH * ConMath::MINUTES_2_SECONDS; //(velocity) y [m/s] = PI*WHEEL_SIZE * m/in * 1/60 * x [RPM]
        constexpr double MOTOR_SPEED = 0.5;
         //PID gains
        constexpr double P = 2e-4;
        constexpr double I = 0.0;
        constexpr double D = 2e-3;
        constexpr double FF = 1.7e-4;
    }
    namespace Feeder {
        constexpr int MOTOR_ID = 1;
        constexpr double MOTOR_SPEED = 0.5;
    }
    namespace Hopper {
        constexpr int MOTOR_ID = 0;
    }
}

namespace ConShuffleboard {
    constexpr char RobotTab[] = "Robot";
    constexpr char ClimberTab[] = "Climber";
    constexpr char ControlPanelManipulatorTab[] = "CPM";
    constexpr char DriveTrainTab[] = "DriveTrain";
    constexpr char ShooterTab[] = "Shooter";
    constexpr char VisionTab[] = "Vision";
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
