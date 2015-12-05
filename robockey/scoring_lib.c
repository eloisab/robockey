//
//  scoring_lib.c
//
//
//  Created by Jesus Gallegos  on 12/3/15.
//
//
#include <avr/io.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"
#include "LOCOlization.h"
#include "m_wii.h"
#include "m_usb.h"
#include "motor_driver.h"
#include "ADC_lib.h"
#include "moving_average.h"
#include "mrf_lib.h"
#include "follow_puck.h"
#include "scoring_lib.h"


void score_goal(int x1, int y1, int theta, int side)
{
    float constants[3];
    
    
    // get constants
    if (side>0){
        get_constants(constants, -115, -30, x1, y1, theta, side);
    }
    else
    {
        get_constants(constants, 115, -30, x1, y1, theta, side);
    }
    
    float p = constants[0]; // speed constant
    int d = constants[1]; // direction constant
    float j = constants[2]; // how much turn constant
    float d2 = constants[3];
    
    turn_robot( d, d2, p, j); // DRIVE THE BOT
}

char get_constants(float* constants, int x_final, int y_final, int x_pos, int y_pos, int theta, int side)
{
    // calculate distance between current location and desired location
    int dist = calc_dist(x_pos,y_pos,x_final,y_final);
    // define drive constants
    float p;
    float d;
    float j;
    float d2;
   
    // Calculate drive constants
    
    
    int beta = side*90; // final angle
    
    int delta_angle = abs(beta - theta);
    if (theta>beta && y_pos>y_final){
        d = 0;
    }
    else if(theta>beta && y_pos<y_final)
    {
        d = 0;
    }
    else if (theta<beta && y_pos>y_final)
    {
        d = 1;
    }
    else
    {
        d = 1;
    }

    
    
    if (dist < 20)
    {
        //p = 0;
    }
    
    j = abs(-1 + abs(theta-beta/180));
    //p =abs(.95 - abs(theta/90))/2;
    p = 1 - abs((y_pos-y_final)/200);
    d2 = 1;
    p = .7;
    if( y_pos > 70)
    {
        d = 1;
        d2 = 1;
        p = .4;
        j = 1;
    }
    else if(y_pos< -70)
    {
        d = 0;
        d2 = 1;
        p = .4;
        j = 1;
    }
    constants[0] = p;
    constants[1] = d;
    constants[2] = j;
    constants[3] = d2;
}