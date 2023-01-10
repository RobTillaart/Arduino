#pragma once
//
//    FILE: AD56X8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2022-07-28
// PURPOSE: Arduino library for AD56X8, SPI 8 channel Digital Analog Convertor.


#include "Arduino.h"
#include "SPI.h"

#define AD56X8_LIB_VERSION        (F("0.1.2"))


#define AD56X8_PWR_NORMAL         0x00
#define AD56X8_PWR_1K             0x01
#define AD56X8_PWR_100K           0x02
#define AD56X8_PWR_TRI_STATE      0x03

//  ZERO, HALF, FULL ?
#define AD56X8_CC_0000            0x00
#define AD56X8_CC_8000            0x01
#define AD56X8_CC_FFFF            0x02
#define AD56X8_CC_NOP             0x03    //  do not use (read datasheet)



class AD56X8
{
public:
  AD56X8(uint8_t slaveSelect);
  AD56X8(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void     begin();
  uint8_t  getType();


  //  SET DAC
  //  returns false if channel out of range
  //  sets output immediately = prepare + update.
  bool     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);
  bool     setPercentage(uint8_t channel, float percentage);
  float    getPercentage(uint8_t channel);

  //  prep & update separately
  bool     prepareChannel(uint8_t channel, uint16_t value);
  bool     updateChannel(uint8_t channel);
  void     updateAllChannels();


  //  LDAC
  void     setLDACmask(uint8_t mask = 0x00);
  uint8_t  getLDACmask();
  bool     inLDACmask(uint8_t channel);


  //  POWER
  //  mode = 0..3
  //  returns false if mode out of range
  bool     setPowerMode(uint8_t powerDownMode, uint8_t mask = 0x00);


  //  MISC
  //  software reset
  void     reset();
  //  returns false if mode out of range
  //  CCmode = 0..2
  bool     setClearCode(uint8_t CCmode);  //  check datasheet.


  //  SPI
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
  uint8_t  _type        = 0;      //  # bits
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  uint16_t _value[8];
  uint8_t  _ldacMask    = 0;

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint8_t cmd, uint8_t channel, uint16_t value);
  void     updateDevice(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
  void     swSPI_transfer(uint8_t value);

  SPIClass    * mySPI;
  SPISettings _spi_settings;

  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED
//
class AD5668_3 : public AD56X8
{
public:
  AD5668_3(uint8_t slaveSelect);
  AD5668_3(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void     reset();
};


class AD5668 : public AD56X8
{
public:
  AD5668(uint8_t slaveSelect);
  AD5668(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);
};


class AD5648 : public AD56X8
{
public:
  AD5648(uint8_t slaveSelect);
  AD5648(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);
};


class AD5628 : public AD56X8
{
public:
  AD5628(uint8_t slaveSelect);
  AD5628(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);
};



// -- END OF FILE --
