# Heimdallr
Small program to drive, special hardware form Raspberry Pi. It allows for any other program to just have to modify a few files to drive all the function of GPIO. Initially there is an API avaible on C/C++, Python and bash scripts. The system will also have the avaibility to use the pins of another Pi via ssh. Only one master can exist in each network and has to have acces to all the slaves.
# Configurator
There is avaible and script that takes a json file and fills up all the necessary folder on the Pi with the configuration for every pin in the system
# GPIO
This part of the program uses the basic funtions of the GPIOs, other parts will use the comuniction buses and other special functions
## File Structure
Every pin in the system will have a directory in the file system, with the name pinXX. This directorie will be inside a node folder, *node00* is always the pi were is executing. All the nodes will be on the folder */temp/heimdallr*. If the raspberry is meant to be the master in the system then */temp/heimdallr/MASTER* will exist. The following files will exist in the pin folder.
Filename | SignalType | Description | User
-- | -- | -- | --
TRUE | Boolean | Value of the pin, if the file exist the value is TRUE | Application
edgeRead | Boolean | File used in edge mode to control the reading of the edge of a signal | Application
mode | Character | An 8 bit number that sets the mode of the pin (see below) | Configuration
Ton | Int | In tenths of second on delay for the signal | Configuration
Toff | Int | In tenths of second off delay for the signal | Configuration
Frequency | DInt | Frequency on PWM mode | Configuration
dutyCycle | Int | Duty cycle for the PWM 0-1000 | Application
name | String | Name for the signal | Info
description | String | Description text for the signal | Info
## Modes
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
## API
The methods of the different API are described here.
### C API Methods
* GPIOSet (int node, int GPIO)
* GPIOReset (int node, int GPIO)
* GPIOToggle (int node, int GPIO)
* GPIOWrite (int node, int GPIO, char value)
* char GPIORead (int node, int GPIO)
* GPIOSetPWMValue (int node, int GPIO, int dutyCycle)
#### GPIOSet
This function puts the GPIO pin to HIGH.
#### GPIOReset
This function puts the GPIO pin to LOW.
#### GPIOToggle
This function toggles the GPIO pin.
#### GPIOWrite
This function writes the value on the GPIO pin.
#### char GPIORead
This fucntion return a 1 if the pin was HIGH.
#### GPIOSetPWMValue
This function changes the duty cycle of the PWM signal on the pin.
# Driver code
This section describe the code of the driver program, the code is separated in multiple parts. One control the GPIO functions the rest control more advance options.
## GPIO
The GPIO code separates in two, one code is only executed at the start of the program or when the configuration changes. This code is under the function _void GPIOconfigurate(void)_. There is also an infinite loop repeated every sampling sequence, this loop is compose by two functions _void readInputs(void)_ y _void writeOutputs(void)_. In this function the software goes through a list of all the active inputs and outputs, and sets the necessary values according to the files on the state folder.

### Structures
#### Inputs
Variable | Type
-- | --
number | Character
raisingEdge | Character
fallingEdge | Character
prvValue | Character
nxt | pointer to inputs
prv | pointer to inputs
#### Outputs
Variables | Type
-- | --
number | Character
PWM | Character
PWMFrequency | Integer
nxt | pointer to outputs
prv | pointer to outputs
### GPIOConfigurate
This function will read the node 0 folder and create the neccesary structures. After doing this it will configure the hardware according to the needs on the file. It will be compose by various auxiliary smaller functions.
* readPin (char GPIO)
* createInput (char number, char rEdge, char fEdge)
* createOutput (char numver, char PWM, int PWMFreq)
#### readPin
* Get path to node folder
* Read value of mode, and store
* Mask mode and check if active
  * Return
* Check if output
  * Create output, setting flags according to mode
* If input
  * Create input, setting flags according to mode
#### createInput
#### createOutput

### readInputs
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
    
### writeOutputs
* if PWM
  * if pwm frquency in file and struct different
    * change frequency
  * write dutycycle from file into hardware
* else
  * if TRUE exists 
     * write a HIGH
  * else
     * write a LOW

