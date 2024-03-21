/*
 * Regulator.h
 *
 * This is the device driver for the motor.
 *
 * Author:	Author: Anton Satow, Zainab Alfredji
 *
 * Date:	2022-05-05
 */ 

#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

void reg_init(void);
uint8_t reg_power_read(void);

#endif /* TEMP_H_ */