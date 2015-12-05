//
//  robo_com.c
//  
//
//  Created by Jesus Gallegos  on 12/4/15.
//
//

#include <stdio.h>
#include <avr/io.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"
#include "m_usb.h"

#define CHANNEL         12
#define RXADDRESS       0xC8
#define PACKET_LENGTH   3

unsigned char buffer[PACKET_LENGTH];
volatile int flag = 0;

int main(void)
{
    m_clockdivide(0);   // clock speed 16 MHz
    m_bus_init();       // initialize m_bus communications
    m_usb_init();       // USB COM
    
    
    // start wireless communications
    m_rf_open(CHANNEL, RXADDRESS, PACKET_LENGTH);
    sei();              // enable global interrups
    
    
    int x;
    int y;
    int theta;
    while(1)
    {
        if (flag)
        {
            m_rf_read(buffer, PACKET_LENGTH);
            flag = 0;
        }
        
        x = (unsigned char) buffer[0];
        y = (unsigned char) buffer[1];
        theta = (unsigned char) buffer[2];
        
        m_usb_tx_string("X POSITION: ");
        m_usb_tx_int(x);
        m_usb_tx_string("   ");
        m_usb_tx_string("Y POSITION: ");
        m_usb_tx_int(y);
        m_usb_tx_string("   ");
        m_usb_tx_string("ANGLE: ");
        m_usb_tx_int(theta);
        m_usb_tx_string("   ");
        m_usb_tx_string("\n");
        
    }

}


// Wireless interrupt
ISR(INT2_vect)
{
    // read in wireless info
    m_green(TOGGLE);
    
    flag = 1;
}