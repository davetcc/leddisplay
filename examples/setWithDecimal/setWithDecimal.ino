#include <LEDDisplay.h>

/**
 * This example shows setting a value on to the display (optionally as Hex)
 * http://www.thecoderscorner.com/electronics/microcontrollers/driving-displays/47-arduino-7-segment-led-display-library
 */

LEDDisplay *d;
int i=0;

// the pin where wiring starts 
int startPin = 32;

void setup()
{
  d = new LEDDisplay(startPin, true);
  d->setValueDec(0);
  d->startInterrupt();
}

void loop()
{
  int i = analogRead(0);
  d->setValueDec(i);
  // change the line below to render in hex instead of decimal
  //  d->setValueHex(i);
  delay(100);
}
