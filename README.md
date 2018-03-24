# LedDisplay: Display driver for multi-digit 7-segment displays

LEDDisplay is a library that renders information onto multi-digit 7-segment displays. This library requires no additional hardware and uses mutliplex method to refresh each digit. Further, the standalone version can use interrupts to multiplex the digits of the display,  meaning that you don't have to constantly call an "update" method to do the multiplexing.

## Installation

Take a zip download (clone or download button) from here and install it into your Arduino libraries directory.

Libraries are usually installed into the Arduino directory under libraries. For example on windows it may be: `~/Documents/Arduino/libraries`

When you unzip into the libraries directory, enusre the directory is called leddisplay (you'll probably need to remove master from the end).

## Simple use case

Include the header and create a global display variable as below:

	#include <LedDisplay.h>

	// startingPin where the A-G and DP are wired - must be sequential pins.
	// commonIsHigh set to true if your common pin is at 5V when on, otherwise false.
	// optional noOfDigits sets the number of digits for your display (default 4)

	LedDisplay display(startingPin, commonIsHigh, optional noOfDigits );

In setup start the library:

	void setup() {
		// This line starts the muliplexing of the digits on an interrupt
		// if you prefer you can update the display manually too (see docs).
		display.startInterrupt();
	}

Then you can draw onto the display, here's a few examples:

	display.setValueDec(20); // display 20 onto the display
	display.setValueFloat(1.234, 3); // display float with 3dp eg (1.234)
	display.setValueHex(254); // display the value as Hexadecimal.
	display.setValueRaw(1,1); // draw character 1 at position 1.

## More information

[TheCodersCorner library documenation](http://www.thecoderscorner.com/products/arduino-libraries/led-display/68-arduino-7-segment-leddisplay-library-download/)
