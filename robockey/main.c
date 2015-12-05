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
#include "moving_average.h"
#include "mrf_lib.h"
#include "follow_puck.h"
#include "scoring_lib.h"


//
#define CHANNEL         1
#define RXADDRESS       0x1C
#define PACKET_LENGTH   10

#define TXaddress       0x2C
#define PACKET_LENGTH2   3

unsigned char buffer1[PACKET_LENGTH];
unsigned char buffer[PACKET_LENGTH2];

 volatile int testing;
 volatile int flag = 0;

int main(void)
{
    m_disableJTAG();    // Turn off JTAG
    m_red(ON);          // check code runs
    m_clockdivide(0);   // clock speed 16 MHz
    m_bus_init();       // initialize m_bus communications
    m_usb_init();       // USB COM
    setup();            // motor setup
    ADC_setup();        // setup anlog conversions

    // start wireless communications
    m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);
    m_wii_open();       // and open wii camera
    sei();              // enable global interrups

    
    int position[3];        // array for robot position
    int x_curr;             // current x position
    int y_curr;             // current y position
    int theta_curr;         // current angle
    int i;
    int a;
    
    // x, y and theta values
    int x_pos[11];
    int y_pos[11];
    int theta[11];
    
    char send[10];
    
    int side;
    int x1;
    // calculate initial positions

    int status;
//    int x;
//    int y;
//    int theta1;
    int hasPuck = 0;
    // main LOOP
    while(1)
    {
        if (flag)
        {
            m_rf_read(buffer1, PACKET_LENGTH);
            testing = (unsigned char)buffer1[0];
            a = state(testing);
//            m_rf_read(buffer, PACKET_LENGTH);

//            x = (unsigned char)buffer[0];
//            y = (unsigned char)buffer[1];
//            theta1 = (unsigned char)buffer[2];
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

            flag = 0;
        }
      //  m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);

        // store 10 most recent position readings
        for (i=0; i < 11; i++)
        {
            current_location(position);
            x_pos[i] = position[0];
            y_pos[i] = position[1];
            theta[i] = position[2];
        }
        
        // filter position
        filter(x_pos,y_pos,theta);
        
        // current position
        x_curr = x_pos[11];
        y_curr = y_pos[11];
        theta_curr = theta[11];
        
//        send[0] = x_curr;//(char) x_curr;
//        send[1] = y_curr;//(char) y_curr;
//        send[2] = theta_curr;//(char) theta_curr;
//        status = m_rf_send(TXaddress, send, PACKET_LENGTH);
//        if (status){m_red(TOGGLE)};

//        m_usb_tx_string("X Pos: ");
//        m_usb_tx_int(x);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("Y POSITION: ");
//        m_usb_tx_int(y);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("ANGLE: ");
//        m_usb_tx_int(theta1);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("\n");
        
        // COMM TEST
        if (a == 1)
        {
            // ADD CODE
        }
        
        // PLAY GAME
        if (a == 2) {
            m_red(ON);

            int hasPuck = follow_puck();
            //hasPuck = 1;
            if(hasPuck)
            {
                score_goal(x_curr, y_curr, theta_curr, side);
            }
        }
        
        // GOAL R
        if (a == 3)
        {
            //side = 1;
            //m_green(TOGGLE);
        }
        
        // GOAL B
        if ( a == 4)
        {
            //side = -1;
            //m_green(TOGGLE);
        }
        
        // PAUSE, HALF TIME, GAME OVER
        if (a == 5 || a == 6 || a == 7)
        {
            // STOP ROBOT
            turn_robot(0,0,0,0);
            m_red(ON);
        }
        else
        {}
//        // COMM PROTOCOL INSTRUCTIONS
//        m_usb_tx_string("STATE: ");
//        m_usb_tx_int(a);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("FLAG: ");
//        m_usb_tx_int(flag);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("TESTING: ");
//        m_usb_tx_int(testing);
//        m_usb_tx_string("   ");
//        m_usb_tx_string("\n");
    }
}


// Wireless interrupt
ISR(INT2_vect)
{
    // read in wireless info
    m_green(TOGGLE);

    flag = 1;

}
