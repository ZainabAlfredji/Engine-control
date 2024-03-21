/*
 * motor.c
 *
 * Created: 2022-05-05 16:52:13
 *  Author: Anton Satow, Zainab Alfredji
 */ 

#include <avr/io.h>

motor_init(void) 
{
	DDRC |= (1 << 6); // set PC6 as output
	
	TCCR3A |= (1 << COM3A1); // Set OC3A (PC6) to be cleared on compare match //Channel A
	TCCR3A |= (1 << WGM30); // Waveform generation mode 5, Fast PWM (8-bit)
	TCCR3B |= (1 << WGM32); 
	TCCR3B |= (1 << CS31) | (1 << CS30); //Timer clock, 16/64 MHz = 1/4 MHz
}


/*
 *Used to set the speed of the motor. Takes in a value from the ISR in Regulator which is from the ADC.                                                                      
 */

void motor_speed_set(uint8_t speed)
{
	OCR3AH = 0;
	OCR3AL = (speed * 255) / 100; // Takes speed and multiplies to avoid zeor value!
}