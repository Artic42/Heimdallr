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

#include <stdlib.h>

#include "GPIO.h"
#include "lib/Artic42.h"
#include "lib/Hermes.h"

/****************************************
*	Private Function Prtotype           *
****************************************/

void readPin (string  path, char GPIO);
void deleteInputs (void);
void deleteOutputs (void);
void createInput (char GPIO, bool risingEdge, bool fallingEdge, bool pullUp, bool pullDown);
void createOutput (char GPIO, bool PWM, int PWMFrequency);
void readInput (string path, char GPIO);
void writeOutput (string path, char GPIO);

/****************************************
*	Private Definitions	                *
****************************************/

struct input {
    int8b number;
    bool risingEdge;
    bool fallingEdge;
    bool pullUpResistor;
    bool pullDownResistor;
    bool prvValue;
    struct input *nxt;
};

struct output {
    int8b number;
    bool PWM;
    int PWMFrequency;
    struct output *nxt;
};

/****************************************
*	Private Variables                   *
****************************************/

struct input *firstInput = NULL;
struct input *lastInput = NULL;
struct output *firstOutput = NULL;
struct output *lastOutput = NULL;

/****************************************
*	Code                                *
****************************************/

//  GPIOConfigurate
//
//  This function will read the node 0 folder and create the neccesary structures.
//  After doing this it will configure the hardware according to the needs on the file.

void GPIOConfigurate (string path)
{
    char buffer [2048];

    deleteInputs();
    deleteOutputs();

    for (int8b i = 2; i <= 32; i++)
    {
        readPin (path, i);
    }

    sprintf (buffer, "%s%s", path, "/RECONFIGURATE");
    deleteFile (buffer);
}

//  writeOutput
//
//  Goes through the list of output and execute writeOutput for every item in the list.

void writeOutputs (string path)
{
    struct output* _tempOutput = firstOutput;

    while (_tempOutput != NULL)
    {
        writeOutput (path, _tempOutput->number);
        _tempOutput = _tempOutput->nxt;
    }
}

//  readInputs
//
//  Goes through the list of input and execute readInput for every item in the list.

void readInputs (string path)
{
    struct input* _tempInput = firstInput;

    while (_tempInput != NULL)
    {
        readInput (path, _tempInput->number);
        _tempInput = _tempInput->nxt;
    }
}

//  readPin
//  
//  Read mode file and creates the necessary structures.

void readPin (string path, char GPIO)
{

}

//  deleteInputs
//
//  Deletes all Input structures allowing to create new ones.

void deleteInputs (void)
{
    struct input* _tempNextInput = firstInput;

    while (_tempNextInput != NULL)
    {
        firstInput = _tempNextInput->nxt;
        free (_tempNextInput);
        _tempNextInput = firstInput;
    }

    lastInput = NULL;
}

//  deleteOutputs
//
//  Deletes all output structures.

void deleteOutputs (void)
{
    struct output* _tempNextOutput = firstOutput;

    while (_tempNextOutput != NULL)
    {
        firstOutput = _tempNextOutput->nxt;
        free (_tempNextOutput);
        _tempNextOutput = firstOutput;
    }

    lastOutput = NULL;
}

//  createInput
//
//  Creates one input structure and configures the hardware appropietly.

void createInput (char number,
                  bool risingEdge,
                  bool fallingEdge,
                  bool pullUp,
                  bool pullDown)
{
    if (firstInput == NULL)
    {
        firstInput = malloc (sizeof(struct input));
        firstInput->nxt = NULL;
        lastInput = firstInput;
    }
    else
    {
        lastInput->nxt = malloc(sizeof(struct input));
        lastInput = lastInput->nxt;
    }
    
    lastInput->number = number;
    lastInput->risingEdge = risingEdge;
    lastInput->fallingEdge = fallingEdge;
    lastInput->pullDownResistor = pullDown;
    lastInput->pullUpResistor = pullUp;
    lastInput->prvValue = BFALSE; //Read the pin and store later adition
}

//  createOutput
//
//  Creates one output structure and configures the hardware appropietly.

void createOutput (char number, bool PWM, int PWMFrequency)
{
    if (firstOutput == NULL)
    {
        firstOutput = malloc (sizeof (struct output));
        firstOutput->nxt = NULL;
        lastOutput = firstOutput;
    }
    else
    {
        lastOutput->nxt = malloc (sizeof (struct output));
        lastOutput->nxt->nxt = NULL;
        lastOutput = lastOutput->nxt;
    }

    lastOutput->number = number;
    lastOutput->PWM = PWM;
    lastOutput->PWMFrequency = PWMFrequency;
}

//  readInput
//  
//  Reads the value of the input and changes the necessary files
void readInput (string path, char GPIO)
{
    
}

//  writeOutput
//  
//  Read the files and writes the necessary output
void writeOutput (string path, char GPIO)
{

}