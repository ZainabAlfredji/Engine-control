/*
 * Lab6.c
 *
 * Created: 2022-02-12 15:12:07
 * Author: Anton Satow, Zainab Alfredji
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "delay/delay.h"
#include "Regulator/Regulator.h"
#include "hmi/hmi.h"
#include "state.h"
#include "Motor/motor.h"

typedef enum state state_t; // Creates a enum variable
state_t current_state;
state_t next_state;
state_t buttonPressed(); // Method that reads a key

char reg_str[17];
char mode_str[17];
char key;

//The keys 1, 2 should be used to change state. The different states can be seen on lab instruction

int main(void)
{	
	hmi_init();
	reg_init();
	motor_init();
	//Create a variable that takes 	
	//NO_KEY should never change state, nor if same button as current state has been pressed
	current_state = MOTOR_OFF;
		
    while (1) 
    {			
		switch(current_state) {
			
			case MOTOR_OFF:				
				sprintf(mode_str, "MOTOR OFF");	
				motor_speed_set(0);
				break;
			
			case MOTOR_ON:			
				sprintf(mode_str, "MOTOR ON");
				break;
				
			case MOTOR_RUNNING:
				motor_speed_set(reg_power_read());
				sprintf(mode_str, "Motor running");
						
				break;			
		}
		sprintf(reg_str, "%u%c", reg_power_read(), '%');
		output_msg(mode_str, reg_str, 0); // writes out Temperature on first row, actual temp on second row		
		current_state = buttonPressed();
    }	
}

	/*
	*Reads key. If key for current_state is pressed, ignore.	
	*/
state_t buttonPressed()
{
	key = numkey_read();
	if(key == '1' && current_state != MOTOR_OFF)
	{				
		return MOTOR_OFF;   			   		   
    }
	else if(key == '2' && current_state != MOTOR_ON &&
			reg_power_read() == 0 &&
			current_state != MOTOR_RUNNING)
	{
		return MOTOR_ON;						   
	}		   
	else if(reg_power_read() > 0 && current_state != MOTOR_OFF && current_state != MOTOR_RUNNING)
	{
		return MOTOR_RUNNING;						   
	}
	return current_state;
}



