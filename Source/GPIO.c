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

#include <GPIO.h>
#include <Artic42.h>

/****************************************
*	Private Function Prtotype           *
****************************************/

void readPin (char GPIO);
void deleteInputs (void);
void deleteOutputs (void);
void createInput (char number, bool risingEdge, bool fallingEdge, bool pullUp, bool pullDown);
void createOutput (char number, bool PWM, int PWMFrequency);
void readInput (char GPIO);
void writeOutput (char GPIO);

/****************************************
*	Private Definitions	                *
****************************************/

struct input {
    char number;
    bool risingEdge;
    bool fallingEdge;
    bool pullUpResistor;
    bool pullDownResistor;
    bool prvValue;
    struct input *nxt;
}

struct output {
    char number;
    bool PWM;
    int PWMFrequency;
    struct output *nxt;
}

/****************************************
*	Private Variables                   *
****************************************/

struct input *firstInput;
struct input *lastInput;
struct output *firstOutput;
struct output *lastOutput;

/****************************************
*	Code                                *
****************************************/

//  GPIOConfigurate
//
//  This function will read the node 0 folder and create the neccesary structures.
//  After doing this it will configure the hardware according to the needs on the file.

void GPIOConfigurate (void); 
{
    deleteInputs();
    deleteOutputs();

    for {int i = 2; i <= 32; i++}
    {
        readPin (i);
        // Eliminar flag the reconfiguración
    }
}

//  writeOutput
//
//  Goes through the list of output and execute writeOutput for every item in the list.

void writeOutputs (void);
{

}

//  readInputs
//
//  Goes through the list of input and execute readInput for every item in the list.

void readInputs (void);
{

}

//  readInput
//  
//  Read mode file and creates the necessary structures.

void readPin (char GPIO);
{

}

//  deleteInputs
//
//  Deletes all Input structures allowing to create new ones.

void deleteInputs (void);
{

}

//  deleteOutputs
//
//  Deletes all output structures.

void deleteOutputs (void);
{

}

//  createInput
//
//  Creates one input structure and configures the hardware appropietly.

void createInput (char number,
                  bool risingEdge,
                  bool fallingEdge,
                  bool pullUp,
                  bool pullDown);
{

}

//  createOutput
//
//  Creates one output structure and configures the hardware appropietly.

void createOutput (char number, bool PWM, int PWMFrequency);
{

}

//  readInput
//  
//  Reads the value of the input and changes the necessary files
void readInput (char GPIO);
{
    
}

//  writeOutput
//  
//  Read the files and writes the necessary output
void writeOutput (char GPIO);
{

}