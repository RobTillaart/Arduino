#pragma once
//
//    FILE: AD5680.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-09-19
// PURPOSE: Arduino library for AD5680 Digital Analog Convertor (18 bit).


#include "Arduino.h"
#include "SPI.h"

#define AD5680_LIB_VERSION        (F("0.1.0"))

class AD5680
{
public:
  AD5680(uint8_t slaveSelect);
  AD5680(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void     begin();
  uint8_t  getType();


  //  SET DAC
  //  sets output immediately = prepare + update.
  bool     setValue(uint32_t value);
  uint32_t getValue();
  bool     setPercentage(float percentage);
  float    getPercentage();

  //  SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();

  //  ESP32 specific
  #if defined(ESP32)
  void     selectHSPI();
  void     selectVSPI();
  bool     usesHSPI();
  bool     usesVSPI();

  //  to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


protected:
  uint8_t  _type        = 18;      //  # bits
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  uint32_t _value       = 0;

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint32_t value);
  void     swSPI_transfer(uint8_t value);

  SPIClass    * mySPI;
  SPISettings _spi_settings;

  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif
};


// -- END OF FILE --
