//
//    FILE: PCF8574.H
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
//
// PUPROSE:
//

#ifndef _PCF8574_H
#define _PCF8574_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PCF8574_LIB_VERSION "0.1.00"

class PCF8574
{
  public:
  PCF8574(uint8_t address); 
	 
  uint8_t read8(); 
  uint8_t read(uint8_t pin);  

  void write8(uint8_t value); 
  void write(uint8_t pin, uint8_t value); 

  void PCF8574::toggle(uint8_t pin);
  void PCF8574::shiftRight();
  void PCF8574::shiftLeft();
  
  private:
  uint8_t _address;
  uint8_t _data;
  int _status;
};

#endif
	 
