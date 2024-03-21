/*
 * motor.h
 *
 * Created: 2022-05-05 16:52:29
 *  Author: Anton Satow, Zainab Alfredji
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include <inttypes.h>

void motor_init(void);
void motor_speed_set(uint8_t speed);

#endif /* MOTOR_H_ */