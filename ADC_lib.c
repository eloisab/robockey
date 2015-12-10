//
//  ADC_lib.c
//  
//
//  Created by Jesus Gallegos  on 11/23/15.
//
//

// Back: F1
// Left: F4
// Left Angle" F6
// Inner Left: F5
// Inner right: F7
// Right Angle: D6
// Right: D7

#include "ADC_lib.h"
#include "m_general.h"

void ADC_setup(void)
{
    // Set ARF to reference
    clear(ADMUX,REFS1);
    set(ADMUX,REFS0);
    
    // set prescalar to 1/128
    set(ADCSRA,ADPS2);
    set(ADCSRA,ADPS1);
    set(ADCSRA,ADPS0);
    
    set(ADCSRA,ADATE);
}

void ADC0(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR2, ADC9D);
    
    set(ADCSRB, MUX5);        // set D6
    clear(ADMUX, MUX2);
    clear(ADMUX, MUX1);
    set(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC1(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR0, ADC1D);
    
    clear(ADCSRB, MUX5);        // set F1
    clear(ADMUX, MUX2);
    clear(ADMUX, MUX1);
    set(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC4(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR0, ADC4D);
    
    clear(ADCSRB, MUX5);        // set F4
    set(ADMUX, MUX2);
    clear(ADMUX, MUX1);
    clear(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC5(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR0, ADC5D);
    
    clear(ADCSRB, MUX5);        // set F5
    set(ADMUX, MUX2);
    clear(ADMUX, MUX1);
    set(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC6(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR0, ADC6D);
    
    clear(ADCSRB, MUX5);        // set F6
    set(ADMUX, MUX2);
    set(ADMUX, MUX1);
    clear(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC7(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR0, ADC7D);
    
    clear(ADCSRB, MUX5);        // set F7
    set(ADMUX, MUX2);
    set(ADMUX, MUX1);
    set(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}

void ADC8(void) {
    clear(ADCSRA, ADEN);
    
    set(DIDR2, ADC10D);
    
    set(ADCSRB, MUX5);        // set D7
    clear(ADMUX, MUX2);
    set(ADMUX, MUX1);
    clear(ADMUX, MUX0);
    
    set(ADCSRA, ADEN);          // Enable Conversion
    set(ADCSRA, ADSC);          // Begin Conversion
    while(!check(ADCSRA, ADIF)){}
    set(ADCSRA, ADIF);
}




