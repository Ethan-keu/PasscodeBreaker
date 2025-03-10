/* 
 * File:   Stepper_main.h
 * Author: dtbnl
 *
 * Created on May 1, 2023, 11:19 AM
 */

#ifndef STEPPER_MAIN_H
#define	STEPPER_MAIN_H

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

void stepper_setup(void);
void drive_motor1(void);
void drive_motor2(void);
void reset_motor1(void);
void reset_motor2(void);
void delay(unsigned int ms);
void sleep(void);

#ifdef	__cplusplus
}
#endif

#endif	/* STEPPER_MAIN_H */

