#pragma once
//
//    FILE: AD7367_SPI.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-02-10
// PURPOSE: Arduino library for the AD7367, 2 channel consecutive sampling 14 bit ADC.
//          Also AD7366 == 12 bits.
//     URL: https://github.com/RobTillaart/AD7367_SPI


#include "Arduino.h"
#include "SPI.h"

#define AD7367_SPI_LIB_VERSION        (F("0.1.1"))


#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif



class AD7367_SPI
{
public:
  //  CONSTRUCTOR
  //  pins to set.
  AD7367_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ * mySPI = &SPI);

  void     begin();
  uint8_t  getType();  //  returns 66 or 67
  int      getBits();  //  returns 12 or 14

  //  READ
  //  note the ADDR line below determines which pair is read (a1, b1) or (a2, b2)
  int      read();  //  reads ADC-A and ADC-B into an internal buffer.

  //  READ ASYNCHRONOUS
  void     triggerConversion();
  bool     conversionBusy();
  bool     conversionReady();
  int      readAsync();
  //  GET VALUES FROM ADC's
  int      getLastADCA();  //  returns last read value from ADC-A
  int      getLastADCB();  //  returns last read value from ADC-B

  //  FASTREAD
  //  read and return 2 measurements by reference. (arrays)
  //  a == ADC-A,  b == ADC-B
  int      fastRead(int &a, int &b);


  //  ADDR
  //  one could hard connect the ADDR pin,
  //  so these functions are not needed
  //  pin is set default LOW
  void     setADDRpin(uint8_t pin);
  //  LOW = (Va1, Vb1) or HIGH = (Va2, Vb2)
  inline void ADDRwrite(uint8_t mode) { digitalWrite(_addr, mode); };


  //  REFSEL
  //  one could hard connect the REFSEL pin,
  //  so these functions are not needed
  //  pin is set default HIGH = internal.
  void     setREFSELpin(uint8_t pin);
  //  LOW = external voltage or LOW = internal 2.5 Volt.
  inline void REFSELwrite(uint8_t mode) { digitalWrite(_refsel, mode); };


  //  RANGE
  void     setRangePin(uint8_t range0, uint8_t range1);
  //  page 16/17, table 8
  //  0 = ±10 V
  //  1 = ±5 V
  //  2 = 0 V to 10 V
  //  other values = fail
  //  returns 0 on success, -1 or -2 on failure.
  int      setRange(uint8_t range);
  uint8_t  getRange();  //  returns 0, 1, 2  (255 if pins are not set)


  //  SPI
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();


  //  OBSOLETE
  int      getValue(uint8_t channel); // 0 = ADC-A,  1 = ADC-B


protected:
  uint8_t  _type;
  uint8_t  _bits;
  uint8_t  _select;
  uint8_t  _convert;
  uint8_t  _busy;
  int16_t  _value[2] = {0, 0};

  uint8_t  _addr   = 255;
  uint8_t  _refsel = 255;
  uint8_t  _range0 = 255;
  uint8_t  _range1 = 255;


  //  SPI
  uint32_t _SPIspeed = 16000000;

  uint16_t readDevice();

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};



/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD7366
//
class AD7366_SPI : public AD7367_SPI
{
public:
  AD7366_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ * mySPI = &SPI);
};


//  -- END OF FILE --

