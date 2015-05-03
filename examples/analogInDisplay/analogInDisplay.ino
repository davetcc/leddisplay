#include <LEDDisplay.h>
/**
 * Analog in display is intended to be used along with the circuit diagram at the below website.
 * it reads the value on analog0 and renders it to the display as a decimal.
 * http://www.thecoderscorner.com/electronics/microcontrollers/driving-displays/47-arduino-7-segment-led-display-library
 */

// choose the pin where the connections start
int LED_PIN_START = 32;
void setup()
{
  // common must be HIGH to be on. 
  LEDDisplay* d = new LEDDisplay(LED_PIN_START, true);
  d->startInterrupt();  
}

void loop()
{
  float d = (float)analogRead(0) / (1024.0 / 5.0) ;
  LEDDisplay::instance()->setValueFloat(d, 3);
  delay(50);
}
