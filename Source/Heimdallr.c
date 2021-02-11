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

#include "Hermes.h"
#include "Artic42.h"

#include "GPIO.h"

/****************************************
*   Function prototype                  *
****************************************/

int main (int argc, char *argv[]);

/****************************************
*   Definitions                         *
****************************************/

#define T_SAMPLE 50000 //Microseconds
#define DEFAULT_FOLDER "/var/tmp"

/****************************************
*   Macro                               *
****************************************/

#define KILL_CMD file2bool (killPath)
#define CONFIG_CMD file2bool (configPath)
#define MASTER file2bool (masterPath)

/****************************************
*   Code                                *
****************************************/

int main (int argc, char *argv[])
{
    char folderPath [512], killPath [1024], configPath[1024], masterPath [1024];

    if (argc > 2) 
    {
        pritnf ("Paremeter quantity incorrect\n");
        return 1;
    }
    if (argc == 2) { sprintf(&folderPath,"%s",argv[1]); }
    else           { sprintf(&folderPath,DEFAULT_FOLDER); }
    //Create path dependant on folder path
    sprintf(&killPath, "%s/KILL", folderPath);
    sprintf(&configPath,"%s/RECONFIGURATE", folderPath);
    sprintf(&masterPath, "%s/MASTER", folderPath);

    //Initialise gpio
    gpioInitialise();

    if (MASTER) {/*configurate slave nodes and start Heimdallr in those nodes*/}
    GPIOConfigurate (folderPath);
    while (KILL_CMD == BFALSE)
    {
        if (CONFIG_CMD)
        {
            if (MASTER) {/*configurate slave nodes and start Heimdallr in those nodes*/}
            GPIOConfigurate (folderPath);
        }
        // Read and wrtie GPIOs
        readInputs (folderPath);
        writeOutputs (folderPath);

        usleep (T_SAMPLE);
    }
}

