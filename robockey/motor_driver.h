//
//  motor_driver.h
//  
//
//  Created by Jesus Gallegos  on 11/21/15.
//
//

#ifndef ____motor_driver__
#define ____motor_driver__

#include "m_general.h"
#include <stdio.h>

void setup(void);
// FUNCTIONALITY
// sets up timer 1, mode 15 on M2 for PWM motor control
// initializes  pins and settings necessary
// to run 2 motors bi-directionaly
//
// TAKES:
// nothing
//
// RETURNS:
// nothing

void drive_robot(int motor, int direction, float speed);
// FUNCTIONALITY
// drives left or right motor
//
// TAKES:
// int motor: 0 for left motor, 1 for right motor
// int direction: 1 for forward, 0 for backward
// double speed: PWM duty cycle  
//
// RETURNS:
// nothing

void turn_robot(int turn_direction, int motor_direction, float speed, float ratio);
// FUNCTIONALITY
// turns robot
//
// TAKES:
// int turn_direction: 0 for left, 1 for right
// int motor_direction: 1 for forward, 0 for backward
// double speed: PWM duty cycle
// double ratio: ratio of motor1 to motor2 speed
//
// RETURNS:
// nothing
#endif /* defined(____motor_driver__) */
