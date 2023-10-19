#pragma once
//
//    FILE: DAC8552.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor  
// VERSION: 0.2.5
//    DATE: 2017-12-14
//     URL: https://github.com/RobTillaart/DAC8552


#include "Arduino.h"
#include "SPI.h"


#define DAC8552_LIB_VERSION           (F("0.2.5"))


#define DAC8552_POWERDOWN_NORMAL      0
#define DAC8552_POWERDOWN_1K          1
#define DAC8552_POWERDOWN_100K        2
#define DAC8552_POWERDOWN_HIGH_IMP    3


class DAC8552
{
public:
  DAC8552(uint8_t slaveSelect);
  DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void     begin();

  void     bufferValue(uint8_t channel, uint16_t value);
  void     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);

  void     bufferPowerDown(uint8_t channel, uint8_t powerDownMode);
  void     setPowerDown(uint8_t channel, uint8_t powerDownMode);
  uint8_t  getPowerDownMode(uint8_t channel);

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  bool     usesHWSPI() { return _hwSPI; };

  //  ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  //  to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


private:
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;
  
  bool     _hwSPI       = false;
  uint16_t _value[2];
  uint8_t  _register[2];

  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint8_t channel, bool directWrite);
  void     swSPI_transfer(uint8_t value);

  SPIClass    * mySPI;
  SPISettings _spi_settings;

  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif
};


//  -- END OF FILE --

