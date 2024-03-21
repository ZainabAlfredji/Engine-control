/*
 * state.h
 *
 * Created: 2022-02-13 19:40:00
 *  Author: Author: Anton Satow, Zainab Alfredji
 */ 


#ifndef STATE_H_
#define STATE_H_

enum state
{
	// Show temp in Celsius. First row "Temperature:". Second row x °C
	
	MOTOR_OFF,
	
	//Show temp in Fahrenheit. First row "Temperature:". Second row x °F
	
	MOTOR_ON,
	
	//Show temp in both Celsius and Fahrenheit. First row "Temperature:". Second row x °C, y °F
	
	MOTOR_RUNNING
};




#endif /* STATE_H_ */