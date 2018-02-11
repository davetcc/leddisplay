/*
Released under Apache V2 license by www.thecoderscorner.com (Dave Cherry).
This library will drive an LED 7 segment display by interrupt.
*/

#include "LEDDisplay.h"

LEDDisplay* LEDDisplay::theDisplay;

const unsigned char LEDDisplay::charMap[] PROGMEM = {
// bits       6543210
// digits     abcdefg
        0b1111110,//0 0x00
        0b0110000,//1 0x01
        0b1101101,//2 0x02
        0b1111001,//3 0x03
        0b0110011,//4 0x04
        0b1011011,//5 0x05
        0b1011111,//6 0x06
        0b1110000,//7 0x07
        0b1111111,//8 0x08
        0b1111011,//9 0x09
        0b1110111,//a 0x0A
        0b0011111,//b 0x0B
        0b1001110,//c 0x0C
        0b0111101,//d 0x0D
        0b1101111,//e 0x0E
        0b1000111,//f 0x0F
        0b1111011,//g 0x10
        0b0110111,//h 0x11
        0b0110000,//i 0x12
        0b0111000,//j 0x13
        0b0001110,//l 0x14
        0b0010101,//n 0x15
        0b0011101,//o 0x16
        0b1100111,//p 0x17
        0b0000101,//r 0x18
        0b1011011,//s 0x19
        0b0001111,//t 0x1A
        0b0011100,//u 0x1B
        0b0111011,//y 0x1C
        0b0000000 //  0x1D
};


LEDDisplay::LEDDisplay(char pinStart, boolean commonHigh, unsigned char brightness, int noOfDigits) {
    this->pinStart = pinStart;
    this->commonHigh = commonHigh;
	this->noOfDigits = noOfDigits;
	this->digits = new char[noOfDigits];

    for(int i=0;i<(LCD_BITS + noOfDigits);++i) {
        pinMode(pinStart + i, OUTPUT);
    }

    this->currentDigit = 0;

    this->brightness = brightness;
}

LEDDisplay::~LEDDisplay() {
	delete digits;
}

void LEDDisplay::startInterrupt() {
    this->theDisplay = this;

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 64000;   // preload timer
  TCCR1B |= _BV(CS11);    // 256 prescaler
  TIMSK1 |= _BV(TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

void LEDDisplay::setBrightness(unsigned char brightness) {
    if(brightness > MAX_BRIGHTNESS) brightness = MAX_BRIGHTNESS;
    this->brightness = brightness;
}

void LEDDisplay::setValueDec(unsigned int newValue, boolean zeroPad) {
    setNumeric(newValue, 10, 0, 3, zeroPad);
}

void LEDDisplay::setValueHex(unsigned int newValue) {
    setNumeric(newValue, 16, 0, 3, true);
}

void LEDDisplay::setValueFloat(float newValue, unsigned int decimalPlaces, boolean zeroPad) {
    int whole = (int) newValue;
    int frac = (int) ((newValue - (float)whole) * pow(10, decimalPlaces + 1) + 0.5);
    int wholeDp = noOfDigits - decimalPlaces;
    setNumeric(frac, 10, wholeDp, decimalPlaces, true);
    setNumeric(whole, 10, 0, wholeDp-1, zeroPad);
    if(commonHigh) {
        digits[wholeDp-1] &= 0x7f;
    }
    else {
        digits[wholeDp-1] |= 0x80;
    }
}

void LEDDisplay::setNumeric(unsigned int value, unsigned int base, char start, char places, boolean zeroPad) {
    for(int i =places+start;i>=start;--i) {
        int digit = value % base;
        value = value / base;
        if(digit == 0 && value == 0 && !zeroPad) {
            digit=0x1d;
        }
        setValueRaw(i, digit);
    }
}


void LEDDisplay::setValueRaw(char position, char newValue, boolean dpOn) {
    if(position < noOfDigits) {
        digits[position] = pgm_read_byte_near(charMap + newValue);

        if(dpOn) {
            digits[position] |= 0x80;
        }

        if(commonHigh) {
            digits[position] = ~digits[position];
        }
    }
}


void LEDDisplay::isr_display() {

    if(currentDigit >= noOfDigits) {
        digitalWrite(pinStart + LCD_BITS + noOfDigits -1, 0);
        currentDigit = 0;
        ++pwm;
    }
    else {
        digitalWrite(pinStart + LCD_BITS + currentDigit -1, 0);
    }

    for(int i=0;i<7;i++) {
        digitalWrite(pinStart + i, digits[currentDigit] & (1<<6-i));
    }

    digitalWrite(pinStart + (LCD_BITS -1 ), digits[currentDigit] & 0x80);

    if(brightness == MAX_BRIGHTNESS) {
        digitalWrite(pinStart + LCD_BITS + currentDigit, commonHigh);
    }
    else {
        digitalWrite(pinStart + LCD_BITS + currentDigit, brightness > (pwm & 3));
    }

    ++currentDigit;
}

ISR(TIMER1_OVF_vect) {
    TCNT1 = 64000;
    LEDDisplay::instance()->isr_display();
}

