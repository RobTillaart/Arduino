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

#define PCF8574_LIB_VERSION "0.1.01"

class PCF8574
{
  public:
  PCF8574(int address); 
	 
  int read8(); 
  int read(int pin); 
  int value();  

  void write8(int value); 
  void write(int pin, int value); 

  void toggle(int pin);
  void shiftRight();
  void shiftLeft();
  
  int getStatus();
  
  private:
  int _address;
  int _data;
  int _status;
};

#endif
	 
