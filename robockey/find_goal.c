//
//  find_goal.c
//  
//
//  Created by Jesus Gallegos  on 11/24/15.
//
//

#include "find_goal.h"
#include <avr/io.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"
#include "LOCOlization.h"
#include "m_wii.h"
#include "m_usb.h"
#include "motor_driver.h"
#include "mrf_lib.h"
#include "math.h"


void goal(void) {
    
    // current position and angle
    int position[3];
    current_location(position);
    double beta;
    double x;
    double y;
    double angle;
    int alpha;

    int i;
    for (i = 0; i < 30000; i++)
    {
     x = (double) position[0];
     y = (double) position[1];
     angle = (double)position[2];
    
        m_green(ON);
    
    if (y>0)
    {
        beta = atan2((double)(-115-x), -y) ;
    }
    else
    {
        beta = -M_PI +atan2((double)(-115 - x), -y);
    }
    }
    
    beta = beta*(180/M_PI);
    alpha = (int) beta;
    
    m_green(OFF);
    
    while (1)
    {
        if (abs(angle - beta) < 5)
        {
            m_red(ON);
        }
        current_location(position);
        angle = (double)position[2];
        m_usb_tx_string("   ");
        m_usb_tx_string("Angle: ");
        m_usb_tx_int((position[2]));
        m_usb_tx_string("   ");
        m_usb_tx_string("   ");
        m_usb_tx_string("Beta: ");
        m_usb_tx_int(beta);
        m_usb_tx_string("   ");
        
        //        m_usb_tx_string("ADC: ");
        //        m_usb_tx_int(ADC);
        m_usb_tx_string("\n");
    }
}

