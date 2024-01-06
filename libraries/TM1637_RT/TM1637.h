#pragma once
//
//    FILE: TM1637.h
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-28
// VERSION: 0.4.0
// PURPOSE: TM1637 library for Arduino
//     URL: https://github.com/RobTillaart/TM1637_RT

//  NOTE:
//  on the inexpensive TM1637 boards @wfdudley has used, keyScan
//  works if you add a 1000 ohm pull-up resistor from DIO to 3.3v
//  This reduces the rise time of the DIO signal when reading the key info.
//  If one only uses the pull-up inside the microcontroller,
//  the rise time is too long for the data to be read reliably.

//  tested on 6 digit display
//  tested on 4 digit (clock) display esp. displayTime()


#include "Arduino.h"

#define TM1637_LIB_VERSION      (F("0.4.0"))


class TM1637
{
public:
  TM1637();

  //  begin replaces init()
  void begin(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6);


  //  DISPLAY FUNCTIONS
  void displayPChar( char * buff );
  void displayRaw(uint8_t * data, uint8_t pointPos);
  void displayInt(long value);
  void displayFloat(float value);
  void displayFloat(float value, uint8_t fixedPoint);
  void displayHex(uint32_t value);


  //  next 3 only tested on 4 digit display with colon
  void displayTime(uint8_t hh, uint8_t mm, bool colon);
  void displayTwoInt(int ll, int rr, bool colon = true);
  //  Celsius  -9..99°C
  void displayCelsius(int temp, bool colon = false);
  //  Fahrenheit -9..99°F
  void displayFahrenheit(int temp, bool colon = false);


  // DISPLAY FUNCTIONS META
  void displayClear();
  void displayRefresh();
  //  EXPERIMENTAL 0.3.8
  void hideSegment(uint8_t idx);
  void hideMultiSegment(uint8_t mask);  //  0 bit = show  1 bit = hide


  //  BRIGHTNESS
  //  brightness = 0..7
  void    setBrightness(uint8_t brightness = 3);  //  default 3
  uint8_t getBrightness();


  //  BIT DELAY
  //  tune the timing of writing bytes.
  void    setBitDelay(uint8_t bitDelay = 10);
  uint8_t getBitDelay();


  //  KEY SCAN
  uint8_t keyScan(void);


  //  CONFIGURATION
  //  the order the individual digits must be sent to the display.
  //  optionally to be called after begin()
  void    setDigitOrder(uint8_t a = 0, uint8_t b = 1,
                        uint8_t c = 2, uint8_t d = 3,
                        uint8_t e = 4, uint8_t f = 5,
                        uint8_t g = 6, uint8_t h = 7);


  //  DEBUG only
  void dumpCache();


protected:
  uint8_t _clockPin   = -1;
  uint8_t _dataPin    = -1;
  uint8_t _digits     = 6;
  uint8_t _brightness = 3;
  uint8_t _bitDelay   = 10;

  uint8_t _digitOrder[8];

  uint8_t _data[8];
  uint8_t _lastPointPos;

  uint8_t writeByte(uint8_t data);
  void    start();
  void    stop();

  void    writeSync(uint8_t pin, uint8_t val);
  void    nanoDelay(uint16_t n);

  //  Override in your own derived class for custom character translation
  virtual uint8_t asciiTo7Segment ( char c ) ;
};


//  -- END OF FILE --

