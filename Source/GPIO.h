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

#include "lib/Artic42.h"

/****************************************
*	Public Function Prototype           *
****************************************/

void GPIOConfigurate (string path);
void writeOutputs (string path);
void readInputs (string path);

/****************************************
*	Public Constants                    *
****************************************/

#endif