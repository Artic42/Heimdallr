/*
File Name:	GPIO.h
//
Compiler:	gcc
Author:		Artic42
Description:	Header file for the GPIO.c, contains the necessary offset for the GPIO of Raspberry Pi Zero and Raspberry Pi 4. Important the initial adress of the different Pi models aren't the same, during compilation target must be selected.
Testd on:	Raspberry Pi 4 B // 2Gb RAM
*/

/****************************************
*	Include				*
*****************************************/

#include "io.h" //This is the file that defines the constant that are diferent depending on the model of Raspberry Pi 4

/****************************************
*	Public Function Prtotype	*
****************************************/

void gpioModeSelect (int gpioNumber, int Mode);

void gpioSet (int gpioNumber);
void gpioClear (int gpioNumber);
void gpioWriteValue (int gpioNumber, char value);

char gpioRead (int gpioNumber);


/****************************************
*	Public Constants		*
****************************************/

#define GPIO0 0
#define GPIO1 1
//Completar con todos los GPIO más adelante

#define BTRUE 1
#define BFALSE 0

#define INPUT_MODE 0
#define OUTPUT_MODE 1
#define FUNC_0 4
#define FUNC_1 5
#define FUNC_2 6
#define FUNC_3 7
#define FUNC_4 3
#define FUNC_5 2


/****************************************
*	Adress offset		*
****************************************/
