//
//    FILE: PCF8574.H
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.1.02
// PURPOSE: I2C PCF8574 library for Arduino
//     URL: 
//
// HISTORY:
// see PCF8574.cpp file
// 

#ifndef _PCF8574_H
#define _PCF8574_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PCF8574_LIB_VERSION "0.1.02"

class PCF8574
{
  public:
  PCF8574(int address); 
	 
  uint8_t read8(); 
  uint8_t read(uint8_t pin); 
  uint8_t value();  

  void write8(uint8_t value); 
  void write(uint8_t pin, uint8_t value); 

  void toggle(uint8_t pin);
  void shiftRight(uint8_t n=1);
  void shiftLeft(uint8_t n=1);
  
  int lastError();
  
  private:
  int _address;
  uint8_t _data;
  int _error;
};

#endif
//
// END OF FILE
//