/**
 * This is a series of unit tests that run though most of the functions
 * of the LEDDisplay library. After building the project you can test
 * with this example to ensure it is working correctly.
 * see http://www.thecoderscorner.com/electronics/microcontrollers/driving-displays/47-arduino-7-segment-led-display-library
 */
#include <LEDDisplay.h>

// set the pin at which you started wiring below
int ledPinStart = 32;

void setup()
{
  LEDDisplay* d = new LEDDisplay(ledPinStart, true);
  d->startInterrupt();
}

void loop()
{
  for(int i=0;i<100;++i) {
    LEDDisplay::instance()->setValueDec(i);
    ++i;
    delay(250);
  }
  LEDDisplay::instance()->setBrightness(3);

  for(unsigned int i=50000;i<53000;i+=100) {
    LEDDisplay::instance()->setValueDec(i);
    ++i;
    delay(250);
  }

  LEDDisplay::instance()->setBrightness(2);

  for(unsigned int i=50000;i<53000;i+=123) {
    LEDDisplay::instance()->setValueHex(i);
    ++i;
    delay(250);
  }

  LEDDisplay::instance()->setBrightness(1);

  float d = 1.234;  
  while(d<9.9) {
    LEDDisplay::instance()->setValueFloat(d, 2);
    d += 0.543;
    delay(250);
  }
}
