/*
File Name:   GPIO.h
//
Compiler:    gcc
Author:      Artic42
Description: Header file for GPIO.c
Testd on:    Raspberry Pi 4 B // 4Gb RAM
*/

#ifndef GPIO_H
#define GPIO_H

/****************************************
*	Include                             *
****************************************/

/****************************************
*	Public Function Prototype           *
****************************************/

void GPIOConfigurate (void);
void writeOutputs (void);
void readInputs (void);

/****************************************
*	Public Constants                    *
****************************************/

#endif