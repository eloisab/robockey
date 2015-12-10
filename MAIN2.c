//
//  MAIN2.c
//  
//
//  Created by Jesus Gallegos  on 11/28/15.
//
//

#include <stdio.h>
/*
 * DONT TOUCH
 * Author : Jesus Gallegos
 */

#include <avr/io.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"
#include "LOCOlization.h"
#include "m_wii.h"
#include "m_usb.h"
#include "motor_driver.h"
#include "ADC_lib.h"


#define CHANNEL         1
#define RXADDRESS       0x1C
#define PACKET_LENGTH   10
unsigned char buffer1[PACKET_LENGTH];
volatile int testing;

// helper function
char get_constants1(float* constants, int x_final, int y_final, int x_pos, int y_pos, int theta, int side, int derivative);

int main(void)
{
    m_clockdivide(0); // clock speed 16 MHz
    sei(); // enable global interrups
    int derivative = 0;
    
    // initialize m_bus communications
    // start wireless communications
    // and open wii camera
    m_bus_init();
    m_wii_open();
    m_usb_init();
    m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);
    
    setup();    // motor setup
    
    int side;   // integer to figure out which side we're on
    
    while (1)
    {
        // USB print testing
        m_usb_tx_string("testing: ");
        m_usb_tx_int(testing);
        m_usb_tx_string("   ");
        m_usb_tx_string("\n");
        
        // continue code if ply command is issued
        if ((unsigned char)buffer1[0] == 0xA1){
            break;
        }
    }
    
    // turn red light on if play command is issued
    m_red(ON);
    
    // wait 10 seconds to let M_Wii start recording stars
    m_wait(1000);
    
    int position[3];        // array for robot position
    int x1;                 // x position
    int i;
    
    // calculate initial positions
    for(i = 0; i<1000; i++)
    {
        current_location(position);
        x1 = position[0];
    }
    
    // figure out what side robot starts on
    if (x1 > 0)
    {
        side = -1;
    }
    else
    {
        side = 1;
    }
    
    // array to hold constants
    float constants[4];
    //goal();
    
    // main LOOP
    while(1)
    {
        // calculate positions
        int b = current_location(position);
        int x1 = position[0];
        int y1 = position[1];
        int angle = position[2];
        
        // usb prinitng
        m_usb_tx_string("LOCALIZATION: ");
        m_usb_tx_int(b);
        m_usb_tx_string("   ");
        m_usb_tx_string("X Position: ");
        m_usb_tx_int(x1);
        m_usb_tx_string("   ");
        m_usb_tx_string("Y Position: ");
        m_usb_tx_int(y1);
        m_usb_tx_string("   ");
        m_usb_tx_string("Angle: ");
        m_usb_tx_int(angle);
        m_usb_tx_string("   ");
        m_usb_tx_string("\n");
        
        // get constants
        if (side>0){
            get_constants1(constants, -115, 0, x1, y1, angle, side, derivative);
        }
        else
        {
            get_constants1(constants, 115, 0, x1, y1, angle, side, derivative);
        }
        
        
        float p = constants[0]; // speed constant
        int d = (int)constants[1]; // direction constant
        float j = constants[2]; // how much turn constant
        derivative = constants[3];
        
        turn_robot( d, 1, .9, j); // DRIVE THE BOT
    }
}

// Helper function to find drive constants
char get_constants1(float* constants, int x_final, int y_final, int x_pos, int y_pos, int theta, int side, int derivative)
{
    // calculate distance between current location and desired location
    int dist = calc_dist(x_pos,y_pos,x_final,y_final);
    // define drive constants
    float p;
    float d;
    float j;
    
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
    
    j = abs(-1 - abs(theta-beta/180));
    //p =abs(.95 - abs(theta/90))/2;
    p = 1 - abs((y_pos-y_final)/200);
    constants[0] = p;
    constants[1] = d;
    constants[2] = j;
    constants[3] = delta_angle;
    return 1;
}

// Wireless interrupt
ISR(INT2_vect)
{
    // read in wireless info
    m_green(TOGGLE);
    m_rf_read(buffer1, PACKET_LENGTH);
    testing = (unsigned char)buffer1[0];
    
}
