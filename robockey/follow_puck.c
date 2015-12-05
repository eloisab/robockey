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
    
    
    if (F5 > 900 && F7 > 900)
    {
        hasPuck = 1;
        return hasPuck;
    }
    // move forward
    if (abs(F6-D6) < 300 && F6>F4 && D6>D7)
    {
        tD = 1;
        mD = 1;
        s = .8;
        r = 1;
        hasPuck = 0;
    }
    
    // turn left hard
    else if (F4>700 && F4>F6)
    {
        tD = 1;
        mD = 1;
        s = .9;
        r = 0;
        hasPuck = 0;
    }
    else if (F6>700 && F6>F4)
    {
        tD = 1;
        mD = 1;
        s = .8;
        r = .4;
        hasPuck = 0;
    }
    
    // turn Right hard
    else if (D7>800 && D7>D6)
    {
        tD = 0;
        mD = 1;
        s = .9;
        r = 0;
        hasPuck = 0;
    }
    // turn Right hard
    else if (D6>800 && D6>D7)
    {
        tD = 0;
        mD = 1;
        s = .8;
        r = .4;
        hasPuck = 0;
    }
    
    // if its behind
    else if (F1>1000 && F1>D7 && F1>F4)
    {
        tD = 1;
        mD = 1;
        s = .4;
        r = 0;
        hasPuck = 0;
    }
     
    
    turn_robot( tD,  mD,  s,  r);

    return hasPuck;
    
}



