#pragma once
//
//    FILE: DAC8551.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8551 SPI Digital Analog Convertor
//          could work with DAC8550, not tested
// VERSION: 0.2.7
// HISTORY: See DAC8551.cpp
//     URL: https://github.com/RobTillaart/DAC8551
//


#include "Arduino.h"
#include "SPI.h"


#define DAC8551_LIB_VERSION            (F("0.2.7"))


#define DAC8551_POWERDOWN_NORMAL       0
#define DAC8551_POWERDOWN_1K           1
#define DAC8551_POWERDOWN_100K         2
#define DAC8551_POWERDOWN_HIGH_IMP     3


class DAC8551
{
public:
  DAC8551(uint8_t slaveSelect);
  DAC8551(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void     begin();

  void     setValue(uint16_t value);
  uint16_t getValue();

  void     setPowerDown(uint8_t powerDownMode);
  uint8_t  getPowerDownMode();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  bool     usesHWSPI() { return _hwSPI; };

  // ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  // to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif

protected:
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select = 255;

  bool     _hwSPI       = false;
  uint16_t _value       = 0;
  uint8_t  _register    = 0;

  uint32_t _SPIspeed    = 16000000;

  void     updateDevice();
  void     swSPI_transfer(uint8_t value);


  SPIClass    * mySPI;
  SPISettings _spi_settings;

  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif
};


/////////////////////////////////////////////////////////
//
// derive 8501, 8531 and 8550 from 8551
//

#define DAC8501_POWERDOWN_NORMAL       0
#define DAC8501_POWERDOWN_1K           1
#define DAC8501_POWERDOWN_100K         2
#define DAC8501_POWERDOWN_HIGH_IMP     3


class DAC8501 : public DAC8551
{
public:
  DAC8501(uint8_t slaveSelect);
  DAC8501(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

};


#define DAC8531_POWERDOWN_NORMAL       0
#define DAC8531_POWERDOWN_1K           1
#define DAC8531_POWERDOWN_100K         2
#define DAC8531_POWERDOWN_HIGH_IMP     3


class DAC8531 : public DAC8551
{
public:
  DAC8531(uint8_t slaveSelect);
  DAC8531(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

};


#define DAC8550_POWERDOWN_NORMAL       0
#define DAC8550_POWERDOWN_1K           1
#define DAC8550_POWERDOWN_100K         2
#define DAC8550_POWERDOWN_HIGH_IMP     3


class DAC8550 : public DAC8551
{
public:
  DAC8550(uint8_t slaveSelect);
  DAC8550(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

};


// -- END OF FILE --

