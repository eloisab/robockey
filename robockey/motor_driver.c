//
//  motor_driver.c
//  
//
//  Created by Jesus Gallegos  on 11/21/15.
//
//

#include "motor_driver.h"
#include "m_general.h"

void setup(void)
{
    // set pins for output
    
    set(DDRB,4); // left motor enable
    set(DDRB,5); // right motor enable
    set(DDRB,6); // left motor PWM (speed) output
    set(DDRC,6); // right motor Pwm (speed) output
    
    set(DDRB,0); // left motor in1
    set(DDRB,1); // left motor in2
    set(DDRB,2); // right motor in1
    set(DDRB,3); // right motor in2
    
    // set the system clock source:
    // timer 1 clockspeed/1
    clear(TCCR1B,CS12);
    clear(TCCR1B,CS11);
    set(TCCR1B,CS10);
    // timer 3 clockspeed/1
    clear(TCCR3B,CS32);
    clear(TCCR3B,CS31);
    set(TCCR3B,CS30);
    
    // set mode:
    // (mode 15) UP to OCR1A, PWM mode
    set(TCCR1B,WGM13);
    set(TCCR1B,WGM12);
    set(TCCR1A,WGM11);
    set(TCCR1A,WGM10);
    // (mode 14) UP to ICR3, PWM mode
    set(TCCR3B,WGM33);
    set(TCCR3B,WGM32);
    set(TCCR3A,WGM31);
    clear(TCCR3A,WGM30);
    
    // set Channel B Compare Output (OC1B) Options:
    // clear at OCR1B, set at rollover
    set(TCCR1A,COM1B1);
    clear(TCCR1A,COM1B0);
    // set Channel C Compare Output (OC1C) Options:
    // clear at OCR3A, set at rollover
    set(TCCR3A,COM3A1);
    clear(TCCR3A,COM3A0);
    
    // set signal frequency
    OCR1A = 3000;
    OCR1B = 5;
    
    ICR3 = 3000;
    OCR3A = 5;
    }

void drive_robot(int motor, int motor_direction, float speed)
{
    // left motor (0)
    if (!motor){
        // set speed
        OCR1B = speed*OCR1A;
        
        // set direction
        set(PORTB,motor_direction);
        clear(PORTB,!motor_direction);
        
        // set which motor to turn
        set(PORTB,4); // turns this motor on
    }
    // right motor(1)
    else
    {
        // set speed
        OCR3A = ICR3*speed;
        
        // set direction
        set(PORTB, (!motor_direction)*2 + (motor_direction)*3);
        clear(PORTB, (motor_direction)*2 + (!motor_direction)*3);
        
        // set which motor to turn
        set(PORTB,5);
    }
}

void turn_robot(int turn_direction, int motor_direction, float speed, float ratio)
{
    // 0 = turn left, 1 = turn right
    // turn left, right motor faser
    // turn right, left motor faster

    float speed_1 = speed;
    float speed_2 = speed*ratio;
    
    // turn motor 1
    drive_robot(!turn_direction, motor_direction, speed_1);
    // turn motor 2
    drive_robot(turn_direction, motor_direction, speed_2);
}








