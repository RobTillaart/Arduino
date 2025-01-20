#pragma once
//
//    FILE: AD5593R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-01-30
// PURPOSE: Arduino library for AD5593R, I2C, 8 channel ADC / DAC / GPIO device.
//     URL: https://github.com/RobTillaart/AD5593R


#include "Arduino.h"
#include "Wire.h"


#define AD5593R_LIB_VERSION        (F("0.1.0"))


//  ERROR CODES
#define AD5593R_OK                  0x0000
#define AD5593R_PIN_ERROR           0xFF81
#define AD5593R_I2C_ERROR           0xFF82


class AD5593R
{
public:
  AD5593R(const uint8_t deviceAddress, TwoWire * wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  mode
  int      setADCmode(uint8_t bitMask);
  int      setDACmode(uint8_t bitMask);
  int      setINPUTmode(uint8_t bitMask);
  int      setOUTPUTmode(uint8_t bitMask);
  int      setPULLDOWNmode(uint8_t bitMask);

  //  digital
  uint16_t write1(uint8_t pin, uint8_t value);
  uint16_t read1(uint8_t pin);
  uint16_t write8(uint8_t bitMask);
  uint16_t read8();

  //  analog
  uint16_t writeDAC(uint8_t pin, uint16_t value);
  uint16_t readDAC(uint8_t pin);
  uint16_t readADC(uint8_t pin);

  //  External reference and power
  //  power on = internal reference 2.5V
  int      setExternalReference(bool flag);
  int      powerDown();
  int      wakeUp();
  
  //  OTHER
  //  reset
  int     reset();
  //  temperature
  int      getTemperature();  //  Page 19.  accuracy 3C over 5 samples averaged.

  //  LOW LEVEL access for full control
  int      writeRegister(uint8_t reg, uint16_t data);
  uint16_t readRegister(uint8_t reg);

protected:
  uint8_t _address;
  int     _error;

  TwoWire*  _wire;
};



//  -- END OF FILE --

