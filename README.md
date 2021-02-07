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

There is avaible and script that takes a few json files and fills up all the necessary folder on the Pi with the configuration for every pin, and every node in the system. There will be one Json file for every node in the system, and one general file for the system itself. The general data is the same for all the system. The general file will contain the following information.
Parameter | Data type | Description | Default
-- | -- | -- | --
directoryPath | Path | Path to the directory were all the information will be store | /temp/heimdallr
name | string | Name of the system
description | string | Description of the system
netAdress | IP | Ip adress of the master node in the system | empty
configPath | Path | Path to the json file with the master configuration |
nodes | array of nodes | There will be an array of nodes, with the data for every node | empty

### IP data type

Parameter | Data type | Description | Default
-- | -- | -- | --
adress | adress | The ip of the master node | empty
subnetmask | adress | The subnet mask of the system network | 255.255.255.0

### nodes data type

Parameter | Data type | Description | Default
-- | -- | -- | --
number | integer | the number of the node 1 to 99 |
name | string | name of the node only for information |
description | string | description of the node |
netAdress | IP | IP adress of the node |
configPath | Path | Path to the json file with the node configuration |

## File Structure

This part of the program uses the basic funtions of the GPIOs, other parts will use the comuniction buses and other special functions

### PINXX

Every pin in the system will have a directory in the file system, with the name pinXX. This directory will be inside a node directory, each node represent a different processor, *node00* is always the pi were is executing. All the nodes will be on the folder */temp/heimdallr*. The following files will exist in the pin folder.

Filename | SignalType | Description | User
-- | -- | -- | --
TRUE | Boolean | Value of the pin, if the file exist the value is TRUE | Application
edgeRead | Boolean | File used in edge mode to control the reading of the edge of a signal | Application
mode | Character | An 8 bit number that sets the mode of the pin (see below) | Configuration
Frequency | DInt | Frequency on PWM mode | Configuration
dutyCycle | Int | Duty cycle for the PWM 0-1000 | Application
name | String | Name for the signal | Info
description | String | Description text for the signal | Info

### Modes

The mode is determined by a set of 8 bit, every bit activates a different functionality. Some functionalitys are not compatible with each other. This is the format of the bits X1234567.

1. This bit determine if the pin is active or not
2. This bit determine if the pin is in output or input mode, output = 1.
3. This bit activates the PWM mode when working as an output.
4. Reserve
5. This bit determines if the input is in edge mode. In edge mode the input will only read as one in either the falling or raising edge.
6. This bit determines the edge mode. Raising = 1 and falling = 0.
7. This bit determines the resistor mode if using it as an input. The resistor will be on pull up mode if the bit is 1. In pull down if 0.

#### Valid modes

Only the following modes are considered legal
Code | Binary | Mode
--- | --- | ----
0x00 | 0b0000 0000 | Pin deactivated
0x40 | 0b0100 0000 | Input mode, standard reading, pull down resistor
0x41 | 0b0100 0001 | Input mode, standard reading, pull up resistor
0x44 | 0b0100 0100 | Input mode, falling edge reading, pull down ressitor
0x45 | 0b0100 0101 | Input mode, falling edge reading, pull up ressitor
0x46 | 0b0100 0110 | Input mode, rising edge reading, pull down ressitor
0x47 | 0b0100 0111 | Input mode, rising edge reading, pull up ressitor
0x60 | 0b0110 0000 | Output mode, standard
0x70 | 0b0111 0000 | Output mode, PWM

### Master-Slave coms

Two binary files exist inside the *NodeXX* folder in both the master and the slave. Each cycle the master copys the outputs files from master to slave and the inputs file from slave to master. This files will be treated to change the values of the necessary files in the *PINXX* by each of the nodes.

### API

The methods of the different API are described here.

#### C API Methods

* GPIOSet (int node, int GPIO)
* GPIOReset (int node, int GPIO)
* GPIOToggle (int node, int GPIO)
* GPIOWrite (int node, int GPIO, bool value)
* bool GPIORead (int node, int GPIO)
* GPIOSetPWMDutyCycle (int node, int GPIO, int dutyCycle)
* GPIOSetPWMFrequency (int node, int GPIO, int dutyCycle)

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

##### GPIOSetPWMValue

This function changes the duty cycle of the PWM signal on the pin.

## Driver code

This section describe the code of the driver program, the code is separated in multiple parts. One control the GPIO functions the rest control more advance options. The code is separated into the following files.

* GPIO.c
* I2C.c
* SPI.c
* Nodes.c

### main

* read path
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
folderPath | string | Path to the node directories

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

Read mode file and creates the necessary structures

* Read value of mode, and store
* Mask mode and check if active
  * Return
* Check if output
  * **createOutput**, setting flags according to mode
* If input
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
    * change frequency
  * write dutycycle from file into hardware
* else
  * if TRUE exists
    * write a HIGH
  * else
    * write a LOW
