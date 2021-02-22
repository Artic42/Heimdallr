/*
File Name:   HeimdallrAPI.h
//
Compiler:    gcc
Author:      Artic42
Description: Header file for HeimdallrAPI.c
Testd on:    Raspberry Pi 4 B // 4Gb RAM
*/

#ifndef HEIMDALLRAPI_H
#define HEIMDALLRAPI_H

/****************************************
*   Include                             *
****************************************/

#include "lib/Artic42.h"

/****************************************
*   Public functions                    *
****************************************/

// General function
void initHeimdallr (string folderPath);

// GPIO function
void GPIOSet (int8b node, int8b GPIO);
void GPIOReset (int8b node, int8b GPIO);
void GPIOToggle (int8b node, int8b GPIO);
void GPIOWrite (int8b node, int8b GPIO, bool value);
bool GPIORead (int8b node, int8b GPIO);
void GPIOSetPWMDutyCycle (int8b node, int8b GPIO, int dutyCycle);
int  GPIOGetPWMDutyCycle (int8b node, int8b GPIO);
void GPIOSetPWMFrequency (int8b node, int8b GPIO, int freqency);
int  GPIOGetPWMFrequency (int8b node, int8b GPIO);

#endif