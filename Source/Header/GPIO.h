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


#define BTRUE 1
#define BFALSE 0

#define INPUT_MODE 0x0
#define OUTPUT_MODE 0x1
#define FUNC_0 0x4
#define FUNC_1 0x5
#define FUNC_2 0x6
#define FUNC_3 0x7
#define FUNC_4 0x3
#define FUNC_5 0x2

#define GPIO0 0
#define GPIO1 1
#define GPIO2 2
#define GPIO3 3
#define GPIO4 4
#define GPIO5 5
#define GPIO6 6
#define GPIO7 7
#define GPIO8 8
#define GPIO9 9
#define GPIO10 10
#define GPIO11 11
#define GPIO12 12
#define GPIO13 13
#define GPIO14 14
#define GPIO15 15
#define GPIO16 16
#define GPIO17 17
#define GPIO18 18
#define GPIO19 19
#define GPIO20 20
#define GPIO21 21
#define GPIO22 22
#define GPIO23 23
#define GPIO24 24
#define GPIO25 25
#define GPIO26 26
#define GPIO27 27
#define GPIO28 28
#define GPIO29 29
#define GPIO30 30
#define GPIO31 31
#define GPIO32 32
#define GPIO33 33
#define GPIO34 34
#define GPIO35 35
#define GPIO36 36
#define GPIO37 37
#define GPIO38 38
#define GPIO39 39
#define GPIO40 40
#define GPIO41 41
#define GPIO42 42
#define GPIO43 43
#define GPIO44 44
#define GPIO45 45
#define GPIO46 46
#define GPIO47 47
#define GPIO48 48
#define GPIO49 49
#define GPIO50 50
#define GPIO51 51
#define GPIO52 52
#define GPIO53 53
#define GPIO54 54
#define GPIO55 55
#define GPIO56 56
#define GPIO57 57
#define GPIO58 58
#define GPIO59 59
#define GPIO60 60
#define GPIO61 61
#define GPIO62 62
#define GPIO63 63


/****************************************
*	Adress offset		*
****************************************/
