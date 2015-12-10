/*
 * DONT TOUCH
 * Author : Jesus Gallegos
 * Sending mRF
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
#include "moving_average.h"
#include "mrf_lib.h"
#include "follow_puck.h"
#include "scoring_lib.h"
#include "defend.h"


#define CHANNEL         1
#define RXADDRESS       0x1C
#define PACKET_LENGTH   10
#define TXaddress       0x2C

unsigned char buffer1[PACKET_LENGTH];
char buffer[PACKET_LENGTH];

 volatile int testing;
 volatile int flag = 1;
volatile int flag1 = 0;
int rx_buffer;


int main(void)
{
    m_disableJTAG();    // Turn off JTAG
    m_clockdivide(0);   // clock speed 16 MHz
    m_bus_init();       // initialize m_bus communications
    m_usb_init();       // USB COM
    setup();            // motor setup
    ADC_setup();        // setup anlog conversions

    // start wireless communications
    m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);
    m_wii_open();       // and open wii camera
    sei();              // enable global interrups

    set(DDRC,7);
    set(DDRB,7);
    
    int position[3];        // array for robot position
    int x_curr;             // current x position
    int y_curr;             // current y position
    int theta_curr;         // current angle
    int i;
    int a;
    
    int side;
    int x1;
    // calculate initial positions

    int hasPuck = 0;
    
    
    // main LOOP
    while(1)
    {
        if (flag)
        {
            m_rf_read(buffer1, PACKET_LENGTH);
            testing = (unsigned char)buffer1[0];
            a = state(testing);
            
            if (flag1){
            for(i = 0; i<10; i++)
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
            }

            flag = 0;
        }
        
        current_location(position);
        
        // current position
        x_curr = position[0];
        y_curr = position[1];
        theta_curr = position[2];
        buffer[0] = (x_curr/10);
        buffer[1] = (y_curr/10);
        buffer[2] = (theta_curr/10);
        m_rf_send(TXaddress, buffer, PACKET_LENGTH);

        
        a = 2;
        // COMM TEST
        if (a == 1)
        {
            // ADD CODE
           // m_red(ON);
            if (side == 1)
            {
                set(PORTC,7);
            }
            else {
                set(PORTB,7);
            }
        }
        
        // PLAY GAME
        else if (a == 2) {
           // m_red(OFF);

            hasPuck = follow_puck();
        //hasPuck = 1;
            //goalie(x_curr, y_curr, theta_curr, side);
//            buffer[0] = (x_curr/10);
//            buffer[1] = (y_curr/10);
//            buffer[2] = (theta_curr/10);
//            buffer[3] = (hasPuck/10);
//            m_rf_send(TXaddress, buffer, PACKET_LENGTH);

            if(hasPuck)
            {
                //score_goal(x_curr, y_curr, theta_curr, side);
                turn_robot(0,0,0,0);

            }
        }
        
        // GOAL R
        else if (a == 3)
        {
            //side = 1;
            //m_green(TOGGLE);
        }
        
        // GOAL B
        else if ( a == 4)
        {
            //side = -1;
            //m_green(TOGGLE);
        }
        else if(a == 5)
        {
            turn_robot(0,0,0,0);
          //  m_red(ON);
        }
        
        // PAUSE, HALF TIME, GAME OVER
        else if (a == 6 || a == 7)
        {
            // STOP ROBOT
            turn_robot(0,0,0,0);
            m_red(ON);
        }
        else
        {}

    }
}


// Wireless interrupt
ISR(INT2_vect)
{
    // read in wireless info
    m_green(TOGGLE);

    flag = 1;
    flag1  = flag1 + 1;

}
