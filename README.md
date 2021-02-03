# RPI_Driver
Small program to drive, special hardware form Raspberry Pi. It allows for any other program to just have to modify a few files to drive all the function of GPIO. Initially there is an API avaible on C.
# GPIO
This part of the program uses the basic funtions of the GPIOs, other parts will use the comuniction buses and other special functions.
## File Structure
Filename | SignalType | Description | User
---- | - | -| -
true // false | Boolean | Value of the pin, two files true//false | Application
edgeRead | Boolean | File used in edge mode to control the reading of the edge of a signal | Application
mode | Character | An 8 bit number that sets the mode of the pin (see below) | Configuration
Ton | Int | In tenths of second on delay for the signal | Configuration
Toff | Int | In tenths of second off delay for the signal | Configuration
Frequency | DInt | Frequency on PWM mode | Configuration
dutyCycle | Int | Duty cycle for the PWM 0-1000 | Application
EDGE | Boolean | File for the driver, edge mode active| Driver
PWM | Boolean | File for the driver, edge mode active| Driver
## Modes
The mode is determined by a set of 8 bit, every bit activates a different functionality. Some functionalitys are not compatible with each other. This is the format of the bits X1234567:
1. This bit determine if the pin is active or not
2. This bit determine if the pin is in output or input mode
3. This bit activates the PWM mode when working as an output.
4. This bit activates frequency samplig mode.
5. This bit determines if the input is in edge mode. In edge mode the input will only read as one in either the falling or raising edge.
6. This bit determines the edge mode. Raising = 1 and falling = 0.
7. This bit determines the resistor mode if using it as an input. The resistor will be on pull up mode if the bit is 1. In pull down if 0.
## API
The methods of the different API are described here.
### C API Methods
* GPIOSet (int GPIO)
* GPIOReset (int GPIO)
* GPIOToggle (int GPIO)
* GPIOWrite (int GPIO, char value)
* char GPIORead (int GPIO)
* int GPIOReadFreq (int GPIO)
* GPIOSetPWMValue (int GPIO, int dutyCycle)
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
#### int GPIOReadFreq
This function returns the frequency of the signal in the input if the pin is in sampling mode.
#### GPIOSetPWMValue
This function changes the duty cycle of the PWM signal on the pin.
