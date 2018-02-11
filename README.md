# LedDisplay: Display driver for multi-digit 7-segment displays

LEDDisplay is a library that renders information onto multi-digit 7-segment displays. It does so using
interrupts meaning that you don't have to constantly call an "update" method.

## Installation

Take a zip download (clone or download button) from here and install it into your Arduino libraries directory.

Libraries are usually installed into the Arduino directory under libraries. For example on windows it may be: `~/Documents/Arduino/libraries`

## Simple use case

Include the header and create a global display variable as below:

	#include <LedDisplay.h>

	// startingPin where the A-G and DP are wired - must be sequential pins.
	// commonIsHigh set to true if your common pin is at 5V when on, otherwise false.
	// optional noOfDigits sets the number of digits for your display (default 4)

	LedDisplay display(startingPin, commonIsHigh, optional noOfDigits );

In setup start the library:

	void setup() {
		// your other stuff
		display.startInterrupt();
	}

Then you can draw onto the display, here's a few examples:

	display.setValueDec(20); // display 20 onto the display
	display.setValueFloat(1.234, 3); // display float with 3dp eg (1.234)
	display.setValueHex(254); // display the value as Hexadecimal.
	display.setValueRaw(1,1); // draw character 1 at position 1.

## More information

[TheCodersCorner library documenation](http://www.thecoderscorner.com/products/arduino-downloads/led-display/)
