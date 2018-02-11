/*
Released under Apache V2 license by www.thecoderscorner.com (Dave Cherry).
This library will drive an LED 7 segment display by interrupt.
*/

/**
This library can control an LCD display with a variable number of segments
It drives the display by timer interrupt, so the loop() is kept clean.
Future expansion may provide for a shift register implementation for devices
with smaller pinouts. It defaults to 4 digits, for more or less digits define
LED_NUM_DIGITS differently. Simple examples in the libraries example folder.
*/

#ifndef TCC_LED_DISPLAY_H
#define TCC_LED_DISPLAY_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#define LCD_BITS 8

#define MAX_BRIGHTNESS 4

/** utility method for doing power of 10 on integers */
unsigned int fastPow10(unsigned int dp);

class LEDDisplay {
public:
	/** Create an LCD Display instance to control a connected display */
	LEDDisplay(char pinStart, boolean commonHigh, unsigned char brightness = MAX_BRIGHTNESS, int numDigits = 4);
	~LEDDisplay();

	static LEDDisplay* instance() {return theDisplay;}

	/** Starts a timer interrupt that will keep the display updated */
	void startInterrupt();

	/** Sets the brightness of the display, min 0, max 3 */
	void setBrightness(unsigned char brightness);

	/** Set the display to a decimal value */
	void setValueDec(unsigned int newValue, boolean zeroPad=true);

	/** Set the display to hex value */
	void setValueHex(unsigned int newValue);

	/** Set the display to a floating point value using the specified
        decimalPlaces */
	void setValueFloat(float newValue, unsigned int decimalPlaces, boolean zeroPad=false);

	/** Set digit at position to newValue */
	void setValueRaw(char position, char newValue, boolean dpOn = false);

	/** Advanced numeric digit facility, writes a number in a given base on the
	    display between segments start and end. */
    void setNumeric(unsigned int value, unsigned int base, char start, char places, boolean zeroPad);

    void isr_display();
private:
    /** The instance variable as created for the ISR */
    static LEDDisplay* theDisplay;

    /** The start of the pinouts for the display */
    unsigned char pinStart;

    /** Sets if the display needs common high or low */
    boolean commonHigh;

	/** memory representation of each item for display */
	int noOfDigits;
	volatile unsigned char *digits;

	/** the current digit being rendered */
	volatile unsigned char currentDigit;

	/** the brightness level if selected */
	volatile unsigned char brightness;

	/** we simulate PWM in the switching of the LED display */
	volatile unsigned char pwm;

	/** The actual character bit patterns for display */
	const static unsigned char charMap[] PROGMEM;
};

#endif

