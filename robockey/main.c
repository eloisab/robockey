
//  Created by Eloisa Baez Jones.
//
//
/* Name: main.c
 */

#include <avr/io.h>
#include <stdio.h>
#include "m_general.h"
#include "m_bus.h"
#include "m_rf.h"

#define PKT 3 //packet length
#define RF_add 0x51 //address
#define wchan 1 //channel

volatile int counter = 0;
int resolution = 30;
double sine[30];
volatile int dcounter = 0;
double freq = 200;
int wtime = 0;
char buffer[PKT];
bool durationflag = 0;

int main(void)
{
	m_bus_init();
	//m_usb_init();

	// system clock speed
	m_clockdivide(0);

	// prescalar for timer 1 clock /1
	set(TCCR1B,CS10);
	clear(TCCR1B,CS12);
	clear(TCCR1B,CS11);

	// (mode 15) UP to OCR1A, PWM mode
	set(TCCR1B,WGM13);
	set(TCCR1B,WGM12);
	set(TCCR1A,WGM11);
	set(TCCR1A,WGM10);

	// timer 1 initial value
	OCR1A = 16000000/(440*30);

	// set to output
	set(DDRB,6);

	// set at OCR1B, clear at rollover 
	set(TCCR1A,COM1B1);
	set(TCCR1A,COM1B0); 

	//TIMER3 MODE14
	set(TCCR3B,WGM33);
	set(TCCR3B,WGM32);
	set(TCCR3A,WGM31);
	clear(TCCR3A,WGM30);

	// clock source timer3 \8
	clear(TCCR3B,CS32);
	set(TCCR3B,CS31);
	clear(TCCR3B,CS30);

	//C6 output
	set(DDRC,6);

	//  set at OCR3A, clear at rollover
	set(TCCR3A,COM3A1);
	set(TCCR3A,COM3A0);

	// timer 3 values
	ICR3 = 20000;
	OCR3A = 10000;

	//D4 input
	clear(DDRD,4);
	
	// computer sine table to vary duty cycle to make sine wave
	int i;
	for(i=0; i < resolution; i++)
	{
		sine[i] = (1+sin(i*2*M_PI/resolution))/2;
	}
	
	//timer1 compb interrupt
	set(TIMSK1,OCIE1B);
	//timer1 capt interrupt
	set(TIMSK1,ICIE1);

	//open wifi interrupt
	m_rf_open(wchan,RF_add,PKT);

	// LED pin
	set(DDRB,5);
	set(PORTB,5);

	sei();	

	while(1)
	{
		// if playing, turn LED ON
		if(check(PINB,6))
		{
			set(PORTB,5);
			m_green(ON);
		}
		else
		{
			clear(PORTB,5);
			m_green(OFF);
		}
		
		if(dcounter>=wtime)
		{
			//m_red(ON);
			//turn signal off 
			clear(TIMSK1,OCIE1B);
			OCR1A = 0;
			set(TIMSK1,OCIE1B);
			dcounter = 0;
		}

	}

}

ISR(TIMER1_COMPB_vect)
{
	//m_green(TOGGLE);
	// makes duty cycle varying square wave for sine wave
	OCR1B = sine[counter]*OCR1A;
	counter++;
	if(counter>=resolution)
	{
		counter = 0;
	}
}

ISR(TIMER1_CAPT_vect)
{
	dcounter++;
}

ISR(INT2_vect)
{
	//m_red(ON); 
	m_rf_read(buffer,PKT);
	freq = (unsigned char)buffer[1]*256+(unsigned char)buffer[0];
	wtime = (unsigned char)buffer[2];
	clear(TIMSK1,OCIE1B);
	OCR1A = 16000000/(freq*.1*30);
	set(TIMSK1,OCIE1B);
}