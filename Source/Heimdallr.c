/*
File Name:   GPIO.c
//
Compiler:    GCC
Author:      Artic42
Description: In this file all the function necessary to handle the GPIO of the board will be avaible, main function will call to the differente functions.
Testd on:    Raspberry Pi 4
*/

/****************************************
*	Include                             *
****************************************/

#include <pigpio.h>

/****************************************
*	Global variables                    *
****************************************/

char folderPath [1024];

/****************************************
*   Code                                *
****************************************/

int main (void)
{
    //Initialise gpio
    gpioInitialise();
}