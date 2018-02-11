# LedDisplay: Display driver for multi-digit 7-segment displays

## Installation

* LedDisplay: uses interrupts and has no dependencies, just download and enjoy!

Libraries are installed into the Arduino directory under libraries.

For example on windows it may be: `~/Documents/Arduino/libraries`

## Simple use case

Include the header and create a global display variable as below:

	#include <LedDisplay.h>

	LedDisplay display(startingPin, [true | false]);

In setup start the library (not needed for IoAbstraction version):

	void setup() {
		// your other stuff
		display.startInterrupt();
	}

Then you can draw onto the display, here's a few examples:

	// drawing letters
	display.setValueDec(20);
	display.setValueFloat(1.234, 3);
	display.setValueHex(254);

## More information

[TheCodersCorner library documenation](http://www.thecoderscorner.com/products/arduino-downloads/led-display/)
