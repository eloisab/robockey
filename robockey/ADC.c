//  Created by Eloisa Baez Jones.
//
//
/* Name: ADC.c
 */

// read in clockdivide speed, desired mode, OCR1A and OCR1B desired

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