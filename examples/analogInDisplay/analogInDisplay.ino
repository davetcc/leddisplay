#include <LEDDisplay.h>
/**
 * Analog in display is intended to be used along with the circuit diagram at the below website.
 * it reads the value on analog0 and renders it to the display as a decimal.
 * http://www.thecoderscorner.com/electronics/microcontrollers/driving-displays/47-arduino-7-segment-led-display-library
 */

// choose the pin where the connections start
int LED_PIN_START = 42;

LEDDisplay display(LED_PIN_START, true);

void setup()
{
  // common must be HIGH to be on. 
  display.startInterrupt();  
}

void loop()
{
  float value = (float)analogRead(0) / (1024.0 / 5.0) ;
  display.setValueFloat(value, 3);
  delay(50);
}
