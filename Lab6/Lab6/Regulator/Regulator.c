/*
 * temp.c
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius
 * Co- author: Anton Satow, Zainab Alfredji
 * Date:	2014-12-07
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Regulator.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint8_t adc = 221;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	adc = ADCH;
}

/*
 * Initialize the ADC and ISR.
 */
void reg_init(void)
{
	
	//ADC conversion  ADC = Vin * 1023 / Vref
	
	ADMUX |= (1 << REFS0);		// set reference voltage (internal 5V)
	ADMUX |= (1 << MUX0); // select diff.amp 10x on ADC0 & ADC1
								// right adjustment of ADC value
	ADMUX |= (1 << ADLAR);
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// prescaler 128
	ADCSRA |= (1 << ADATE);		// enable Auto Trigger
	ADCSRA |= (1 << ADIE);		// enable Interrupt
	ADCSRA |= (1 << ADEN);		// enable ADC

	// disable digital input on ADC0 and ADC1
	DIDR0 = 3;
		
	// disable USB controller (to make interrupts possible)
	USBCON = 0;	
	// enable global interrupts
	sei();

	// start initial conversion
	ADCSRA |= (1 << ADSC);	// UPPGIFT: gör så att den initiala A/D-omvandlingen sker
}

/*
 * Reads value from adc, corrects value to avoid zero value.
 * Returns 8-bit int which is a value between 0 - 100;
 */
uint8_t reg_power_read(void)
{
	uint16_t temp = adc * 100;
	uint16_t adc_correction = temp / 255;
	
	return (uint8_t)adc_correction;
}