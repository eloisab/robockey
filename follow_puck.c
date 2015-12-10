//
//  follow_puck.c
//  
//
//  Created by Jesus Gallegos  on 11/28/15.
//
//

#include "follow_puck.h"
#include "ADC_lib.h"
#include "motor_driver.h"

int follow_puck(void)
{
    // Read in values
    ADC0();
    int D6 = ADC;
    
    ADC1();
    int F1 = ADC;
    
    ADC4();
    int F4 = ADC;
    
    ADC5();
    int F5 = ADC;
    
    ADC6();
    int F6 = ADC;
    
    ADC7();
    int F7 = ADC;
    
    ADC8();
    int D7 = ADC;
    
    // IF ADC VALUE ON A CERTAIN SIDE IS BIGGER, TURN IN THAT DIRECTION
    // IF ADC VALUE FROM BACK PT IS BIGGER TURN CLOCKWISE THAT WAY
    // IF ADC VALUE FROM FRONT PR IS LARGER DRIVE FORWARD
    // FIGURE OUT DRIVE CONSTANTS
    
    int tD; // turn dirrection constant
    int mD; // motor dirrection constants
    float s; // speed constant
    float r; // wheel speed ratio constant
    int hasPuck;
    // Back: F1
    // Left: F4
    // Left Angle" F6
    // Inner Left: F5
    // Inner right: F7
    // Right Angle: D6
    // Right: D7
    
    if (F5 > 800 && F7 > 800)
    {
        hasPuck = 1;
        return hasPuck;
        m_green(ON);    }
    else if (F4>D7)
    {
        tD = 1; // turn direction
        mD = 1; // motor direction
        s = .8*(1 - D6/1023); // speed constant
        r = D6/900 - (D6-F6)/300; // wheel speed ratio constant
    }

    else if (D7>F4)
    {
        tD = 0;
        mD = 1;
        s = .8*(1 - F6/1023);
        r = F6/900 - (F6 - D6)/300;
    }
    else
    {
        tD = 0;
        mD = 1;
        s = 0;
        r = F6/1023;
    }

    
    hasPuck = 0;

    turn_robot( tD,  mD,  s,  r);

    return hasPuck;
    
}



