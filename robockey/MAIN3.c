
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



#define CHANNEL         1
#define RXADDRESS       0x1C
#define PACKET_LENGTH   10
unsigned char buffer1[PACKET_LENGTH];
volatile int testing;

int main(void)
{
    m_disableJTAG();
    m_red(ON);
    m_clockdivide(0); // clock speed 16 MHz
    sei(); // enable global interrups
    
    
    // initialize m_bus communications
    // start wireless communications
    // and open wii camera
    m_bus_init();
    m_wii_open();
    m_usb_init();
    m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);
    
    setup();    // motor setup
    ADC_setup();
    
    int position[3];        // array for robot position
    int x_curr;
    int y_curr;
    int theta_curr;
    int i;
    int a;
    
    int x_pos[11];
    int y_pos[11];
    int theta[11];
    
    // main LOOP
    while(1)
    {
        
        //        for (i=0; i < 11; i++)
        //        {
        //            current_location(position);
        //            x_pos[i] = position[0];
        //            y_pos[i] = position[1];
        //            theta[i] = position[2];
        //        }
        
        //        // calculate positions
        //        filter(x_pos,y_pos,theta);
        //        x_curr = x_pos[11];
        //        y_curr = y_pos[11];
        //        theta_curr = theta[11];
        
        // Read in values
        //        ADC0();
        //        int D6 = ADC;
        //
        //        ADC1();
        //        int F1 = ADC;
        //
        //        ADC4();
        //        int F4 = ADC;
        //
        //        ADC5();
        //        int F5 = ADC;
        //
        //        ADC6();
        //        int F6 = ADC;
        //
        //        ADC7();
        //        int F7 = ADC;
        //
        //        ADC8();
        //        int D7 = ADC;
        
        //
        follow_puck();
        m_green(TOGGLE);
        
        
        //        // usb prinitng
        //        m_usb_tx_string("D6: ");
        //        m_usb_tx_int(D6);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("F1: ");
        //        m_usb_tx_int(F1);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("F4: ");
        //        m_usb_tx_int(F4);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("F5: ");
        //        m_usb_tx_int(F5);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("F6: ");
        //        m_usb_tx_int(F6);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("F7: ");
        //        m_usb_tx_int(F7);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("D7: ");
        //        m_usb_tx_int(D7);
        //        m_usb_tx_string("   ");
        //        m_usb_tx_string("\n");
        
        a = state(buffer1);
        a = 2;
        
        // COMM TEST
        if (a == 1)
        {
            // ADD CODE
        }
        
        // PLAY
        if (a == 2) {
        }
        
        // PAUSE, HALF TIME, GAME OVER
        if (a == 5 || a == 6 || a == 7)
        {
            // STOP ROBOT
            turn_robot(0,0,0,0);
            m_red(OFF);
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
    m_rf_read(buffer1, PACKET_LENGTH);
    testing = (unsigned char)buffer1[0];
    
}
