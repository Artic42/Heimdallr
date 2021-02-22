# Heimdallr

Small program to drive, special hardware form Raspberry Pi. It allows for any other program to just have to modify a few files to drive all the function of GPIO. Initially there is an API avaible on C/C++, Python and bash scripts. The system will also have the avaibility to use the pins of another Pi via ssh. Only one master can exist in each network and has to have acces to all the slaves.

The system allow to attach other microcontrollers to the Pis via I2C. We call this component will be designated by peripherals. Firmwares for the processors and desings are avaible for the following peripherals.

uProcessor | ID | Description
-- | -- | --
ATmega328P | 328-DD01 | 8 Digital input or ourtputs with pull up resistors
ATmega328P | 328-AD01 | 6 Analogic inputs, 0-5 V 12 bits
ATmega328P | 328-DA01 | 2 Analogic output, PWM with low pass filters attach, 2KHz freq
ATmega328P | 328-PWM01 | 2 PWM outputs max freq 10KHz
ATmega328P | 328-FC01 | 2 counter inputs, 1Hz - 10KHz reading cycle
ATmega328P | 328-DSP01 | LCD display
ATmega328P | 328-ROM01 | 2kB EEPROM memory

## Configurator

The configurator take an excel file filled with all the necessary information and creates all the files and script necessary for the configuration and running of heimdallr

* Create a master general file
* Create ssh-key if a slave exist
* Create folder for every pin in master
* Create files with the conf of each slave
  * Create the conf file for chain, both local with all the output, and remote with all the inputs.
  * Create an image to be burn in the sd card of the slave
  * Create the folder for every pin in the slaves
* Create the reconfigurate file

### Variables

The following list will be read from the excel file to be used in the creation of the files by the program.

#### masterPins

Varaible name | Type
-- | --
GPIONumber  | Integer
output | Boolean
PWM | Boolean
risingEdge | Boolean
fallingEdge | Boolean
pullUpResistor | Boolean

#### slaves

Variable name | Substructure | Type
-- | -- | --
slaveNumber | no  | Integer
ipAdress | no | ipadress
slavePins | yes | masterPins

## File Structure

This part of the program uses the basic funtions of the GPIOs, other parts will use the comuniction buses and other special functions

### PINXX

Every pin in the system will have a directory in the file system, with the name pinXX. This directory will be inside a node directory, each node represent a different processor, *node00* is always the pi were is executing. All the nodes will be on the folder */temp/heimdallr*. The following files will exist in the pin folder.

Filename | SignalType | Description | User
-- | -- | -- | --
TRUE | Boolean | Value of the pin, if the file exist the value is TRUE | Application
edgeRead | Boolean | File used in edge mode to control the reading of the edge of a signal | Application
mode | Character | An 8 bit number that sets the mode of the pin (see below) | Configuration
Frequency | Integer | Frequency on PWM mode | Configuration
dutyCycle | Integer | Duty cycle for the PWM 0-1000 | Application
name | String | Name for the signal | Info
description | String | Description text for the signal | Info

### Modes

The mode is determined by a set of 8 bit, every bit activates a different functionality. Some functionalitys are not compatible with each other. This is the format of the bits X1234567.

1. This bit determine if the pin is active or not
2. This bit determine if the pin is in output or input mode, output = 1.
3. This bit activates the PWM mode when working as an output.
4. Reserve
5. This bit determines if the input is in rising edge mode. In edge mode the input will only read as one in rising edge.
6. This bit determines if the input is in rising edge mode. In edge mode the input will only read as one the falling edge.
7. This bit determines the resistor mode if using it as an input. The resistor will be on pull up mode if the bit is 1. In pull down if 0.

#### Valid modes

Only the following modes are considered legal
Code | Binary | Character | Mode
--- | --- | ---- | ---
0x08 | 0b0000 1000 | Backspace | Pin deactivated
0x48 | 0b0100 1000 | H | Input mode, standard reading, pull down resistor
0x49 | 0b0100 1001 | I |Input mode, standard reading, pull up resistor
0x4A | 0b0100 1100 | J |Input mode, falling edge reading, pull down ressitor
0x4B | 0b0100 1101 | K | Input mode, falling edge reading, pull up ressitor
0x4C | 0b0100 1100 | L |Input mode, rising edge reading, pull down ressitor
0x4D | 0b0100 1101 | M | Input mode, rising edge reading, pull up ressitor
0x4E | 0b0100 1110 | N | Input mode, rising and falling edge reading, pull down ressitor
0x4F | 0b0100 1111 | O | Input mode, rising and falling edge reading, pull up ressitor
0x68 | 0b0110 1000 | h |Output mode, standard
0x78 | 0b0111 1000 | x | Output mode, PWM

### Master-Slave coms

Two binary files exist inside the *NodeXX* folder in both the master and the slave. Each cycle the master copys the outputs files from master to slave and the inputs file from slave to master. This files will be treated to change the values of the necessary files in the *PINXX* by each of the nodes.

### API

The methods of the different API are described here.

#### C API Methods

* GPIOSet (int8b node, int8b GPIO)
* GPIOReset (int8b node, int8b GPIO)
* GPIOToggle (int8b node, int8b GPIO)
* GPIOWrite (int8b node, int8b GPIO, bool value)
* bool GPIORead (int8b node, int8b GPIO)
* GPIOSetPWMDutyCycle (int8b node, int8b GPIO, int dutyCycle)
* int GPIOGetPWMDutyCycle (int8b node, int8b GPIO)
* GPIOSetPWMFrequency (int8b node, int8b GPIO, int frequency)
* int GPIOGetPWMFrequency (int8b node, int8b GPIO, int frequency)

##### GPIOSet

This function puts the GPIO pin to HIGH.

##### GPIOReset

This function puts the GPIO pin to LOW.

##### GPIOToggle

This function toggles the GPIO pin.

##### GPIOWrite

This function writes the value on the GPIO pin.

##### char GPIORead

This fucntion return a 1 if the pin was HIGH.

##### GPIOSetPWMDutyCycle

This function changes the duty cycle of the PWM signal on the pin.

##### GPIOGetPWMDutyCycle

This function reads the duty cycle of the PWM signal on the pin.

##### GPIOSetPWMFrequency

This function changes the frequency of the PWM signal on the pin.

##### GPIOGetPWMFrequency

This function reads the frequency of the PWM signal on the pin.

## Driver code

This section describe the code of the driver program, the code is separated in multiple parts. One control the GPIO functions the rest control more advance options. The code is separated into the following files.

* GPIO.c
* I2C.c
* SPI.c
* Nodes.c

### main

* if *$PATH/MASTER*
  * **nodesConfigurate**
* **GPIOConfigurate**
* while *$PATH/KILL* doesn't exist
  * if *$PATH/SLAVE*
    * **readMasterData*
  * if *$PATH/RECONFIGURATE*
    * if *$PATH/MASTER*
      * **nodesConfigurate**
    * **GPIOConfigurate**
  * **readInputs**
  * **readNodes**
  * **writeOutputs**
  * **writeNodes**

### Global variables

Variable | Type | Description
-- | -- | ---
folderPath | string | Path to the node directories (Part of the arguments of main)

### GPIO

In this file all the function necessary to handle the GPIO of the board will be avaible, main function will call to the differente functions.

#### Private variables

Variable | Type | Description
-- | -- | ---
firstInput | pointer to input | NULL
lastInput | pointer to input | NULL
firstOutput| pointer to output | NULL
lastOutput | pointer to output | NULL

The file has the following function in it.

* Public
  * GPIOConfigurate (string path)
  * writeOutputs (string path)
  * readInputs (string path)
* Private
  * readPin (string path, char GPIO)
  * deleteInputs (void)
  * deleteOutputs (void)
  * createInput (char GPIO, bool risingEdge, bool fallingEdge, bool pullUp, bool pullDown)
  * createOutput (char GPIO, bool PWM, int PWMFrequency)
  * readInputs (string path, char GPIO)
  * readOutputs (string path, cha GPIO)

#### Structures

##### Input

Variable | Type | Default value
-- | -- | --
number | Interger |
raisingEdge | Boolean |
fallingEdge | Boolean |
pullUpResistor | Boolean |
pullDownResistor | Character |
prvValue | Character |
nxt | pointer to input | NULL

##### Output

Variables | Type | Default value
-- | -- | --
number | Integer |
PWM | Boolean |
PWMFrequency | Integer |
nxt | pointer to output | NULL

#### GPIOConfigurate

This function will read the node 0 folder and create the neccesary structures. After doing this it will configure the hardware according to the needs on the file. It will be compose by various auxiliary smaller functions.

* **deleteInputs()**
* **deleteOutputs()**
* for i in 2-32
  * **readPin(i)**
  * delete configuration command

#### writeOutputs

Goes through the list of output and execute writeOutput for every item in the list.

* store *firstOutput* in *_tempOutput*
* while *_tempOutput* is not null
  * **writeOutput** (*_tempOutput.number*)
  * store *_tempOutput.nxt* in *_tempOutput*

#### readInputs

Goes through the list of input and execute readInput for every item in the list.

* store *firstInput* in *_tempInput*
* while *_tempInput* is not null
  * **readInput** (*_tempInput.number*)
  * store *_tempInput.nxt* in *_tempInput*

#### readPin

Read mode file and creates the necessary structures. This are the masks necessary for read the mode file.

Mask name | Binary | Hexadecimal
-- | -- | --
ACTIVE | 0b0100 0000 | 0x40
OUTPUT | 0b0010 0000 | 0x20
PWM | 0b0001 0000 | 0x10
RISINGEDGE | 0b0000 0100 | 0x04
FALLINGEDGE | 0b0000 0010 | 0x02
PULLUP | 0b0000 0001| 0x01

* Read value of mode, and store
* Mask mode and check if active
  * Return
* Check if output
  * Set PWM flag if necessary
  * **createOutput**, setting flags according to mode
* If input
  * Set necessary flags
  * **createInput**, setting flags according to mode

#### deleteInputs

Deletes all Input structures allowing to create new ones

* store in *_tempNextInput* the value of *firstInput*
* while *_tempNextInput* not null
  * store in *firstInput* the value of *_tmpNextInput.nxt*
  * dealocate *_tempNextInput*
  * store in *_tempNextInput* the value of *firstInput*
* *lastInput* = null

#### deleteOutputs

Deletes all output structures

* store in *_tempNextOutput* the value of *firstOutput*
* while *_tempNextOutput* not null
  * store in *firstOutput* the value of *_tmpNextOutput.nxt*
  * dealocate *_tempNextOutput*
  * store in *_tempNextOutput* the value of *firstOutput*
* *lastOutput* = null

#### createInput

Creates one input structure and configures the hardware appropietly

* if firstInput == null
  * allocate input and store pointer in *firstInput* and *lastInput*
* else
  * allocate input and store pointer in *lastInput.nxt*
  * sotre pointer in *lastInput*
* *lastInput.risingEdge* = *risingEdge*
* *lastInput.fallingEdge* = *fallingEdge*
* *lastInput.pullUpResistor* = *pullUp*
* *lastInput.pullDownResistor* = *pullDown*

#### createOutput

Creates one output structure and configures the hardware appropietly

* if firstOutput == null
  * allocate output and store pointer in *firstOutput* and *lastOutput*
* else
  * allocate output and store pointer in *lastOutput.nxt*
  * sotre pointer in *lastOutput*
* *lastOutput.PWM* = *PWM*
* *lastOutput.PWMFrequency* = *PWMFrequency*

#### readInput

* Read input value
* If TRUE
  * If rising edge mode and prv = FALSE
    * Create file TRUE
  * If not in edge mode
    * Create file TRUE
* else
  * If falling edge mode and prv = TRUE
    * Create file TRUE
  * If not in edge mode
    * Delete file TRUE  

#### writeOutput

* if PWM
  * if pwm frquency in file and struct different
    * change frequency in hardware and struct
  * write dutycycle from file into hardware
* else
  * if TRUE exists
    * write a HIGH
  * else
    * write a LOW
