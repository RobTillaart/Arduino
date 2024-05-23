#pragma once
//
//    FILE: DAC8554.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8554 SPI Digital Analog Convertor
// VERSION: 0.4.1
//    DATE: 2017-12-19
//     URL: https://github.com/RobTillaart/DAC8554
//

#include "Arduino.h"
#include "SPI.h"

#define DAC8554_LIB_VERSION                       (F("0.4.1"))

#define DAC8554_POWERDOWN_NORMAL                  0x00
#define DAC8554_POWERDOWN_1K                      0x40
#define DAC8554_POWERDOWN_100K                    0x80
#define DAC8554_POWERDOWN_HIGH_IMP                0xC0


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


class DAC8554
{
public:
  //  hardware SPI constructor
  DAC8554(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t address = 0);
  //  software SPI constructor
  DAC8554(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t address = 0);

  void     begin();


  void     bufferValue(uint8_t channel, uint16_t value);
  void     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);
  //  writes the value to the channel but does not affect buffered ones
  void     setSingleValue(uint8_t channel, uint16_t value);


  void     bufferPowerDown(uint8_t channel, uint8_t powerDownMode);
  void     setPowerDown(uint8_t channel, uint8_t powerDownMode);
  uint8_t  getPowerDownMode(uint8_t channel);
  void     setSinglePowerDown(uint8_t channel, uint8_t powerDownMode);


  //  write all buffers to all(up to 4) 8554's channel's
  void     broadcastBuffer();
  //  write value to all(up to 4) 8554's channel's
  void     broadcastValue(uint16_t value);
  //  write powerDownMode to all 8554's channel's
  void     broadcastPowerDown(uint8_t powerDownMode);


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };
  bool     usesHWSPI() { return _hwSPI; };


protected:
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  bool     _hwSPI       = false;
  uint8_t  _address     = 0;

  uint16_t _value[4];     //  holds last written / buffered value per channel
  uint8_t  _register[4];  //  holds powerDownMode per channel

  uint32_t _SPIspeed    = 16000000;

  void     writeDevice(uint8_t configRegister, uint16_t value);
  void     swSPI_transfer(uint8_t value);


  __SPI_CLASS__ * _mySPI;
  SPISettings _spi_settings;
};


/////////////////////////////////////////////////////////
//
// DERIVED DAC8534
//

#define DAC8534_POWERDOWN_NORMAL       0
#define DAC8534_POWERDOWN_1K           1
#define DAC8534_POWERDOWN_100K         2
#define DAC8534_POWERDOWN_HIGH_IMP     3


class DAC8534 : public DAC8554
{
public:
  DAC8534(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t address = 0);
  DAC8534(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t address = 0);
};


//  -- END OF FILE --

