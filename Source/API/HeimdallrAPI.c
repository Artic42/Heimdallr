/*
File Name:   HeimdallrAPI.c
//
Compiler:    GCC
Author:      Artic42
Description: Heimdallr API to easily manage all the functionality of Heimdallr
Testd on:    Raspberry Pi 4
*/

/****************************************
*	Include                             *
****************************************/

#include "HeimdallrAPI.h"
#include "lib/Artic42.h"
#include "lib/Hermes.h"

/****************************************
*   Private variables                   *
****************************************/

char heimdallrPath [1024];

/****************************************
*   Private variables                   *
****************************************/

string getPath2PIN (string folderPath, int8b node, int8b GPIO);

/****************************************
*   Code general functions              *
****************************************/

// initHeimdallr
//
// It initilise necessary systems to comunicate with heimdallr,
// importat it doesn't start Heimdallr in the system

void initHeimdallr (string folderPath)
{
    sprintf(heimdallrPath, "%s", folderPath);
}

/****************************************
*   Code general functions              *
****************************************/

// GPIOSet
//
// This function puts the GPIO pin to HIGH

void GPIOSet (int8b node, int8b GPIO)
{
    char filePath [2048];
    sprintf (filePath,"%s/TRUE",getPath2PIN(heimdallrPath,node,GPIO));
    createFile (filePath);
}

// GPIOReset
//
// This function puts the GPIO pin to LOW

void GPIOReset (int8b node, int8b GPIO)
{
    char filePath [2048];
    sprintf (filePath,"%s/TRUE",getPath2PIN(heimdallrPath,node,GPIO));
    deleteFile (filePath);
}

// GPIOToggle
//
// This function toggles the GPIO pin

void GPIOToggle (int8b node, int8b GPIO)
{
    if (GPIORead (node, GPIO) == BFALSE) { GPIOSet(node, GPIO); }
    else                                 { GPIOReset (node, GPIO); }
}

// GPIOWrite
//
// This function toggles the GPIO pin

void GPIOWrite (int8b node, int8b GPIO, bool value)
{
    if (value) { GPIOSet(node, GPIO); }
    else       { GPIOReset (node, GPIO); }
}

// GPIORead
//
// This fucntion return a 1 if the pin was HIGH.

bool GPIORead (int8b node, int8b GPIO)
{
    char filePath [2048];
    sprintf (filePath,"%s/TRUE",getPath2PIN(heimdallrPath,node,GPIO));
    return file2bool (filePath);
}

// GPIOSetPWMDutyCycle
//
// This function changes the duty cycle of the PWM signal on the pin

void GPIOSetPWMDutyCycle (int8b node, int8b GPIO, int dutyCycle)
{
    char filePath [2048];
    sprintf (filePath,"%s/dutyCycle",getPath2PIN(heimdallrPath,node,GPIO));
    int2file (filePath, dutyCycle);
}

// GPIOGetPWMDutyCycle
//
// This function reads the value of the duty cycle of the PWM signal on the pin

int GPIOGetPWMDutyCycle (int8b node, int8b GPIO)
{
    char filePath [2048];
    sprintf (filePath,"%s/dutyCycle",getPath2PIN(heimdallrPath,node,GPIO));
    return file2int (filePath);
}

// GPIOSetPWMFrequency
//
// This function changes the frequency of the PWM signal on the pin

void GPIOSetPWMFrequency (int8b node, int8b GPIO, int Frequency)
{
    char filePath [2048];
    sprintf (filePath,"%s/Frequency",getPath2PIN(heimdallrPath,node,GPIO));
    int2file (filePath, Frequency);
}

// GPIOGetPWMFrequency
//
// This function reads the value of the frequency of the PWM signal on the pin

int GPIOGetPWMFrequency (int8b node, int8b GPIO)
{
    char filePath [2048];
    sprintf (filePath,"%s/Frequency",getPath2PIN(heimdallrPath,node,GPIO));
    return file2int (filePath);
}