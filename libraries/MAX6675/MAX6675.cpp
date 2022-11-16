//
//    FILE: MAX6675.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for MAX6675 chip for K type thermocouple
//    DATE: 2022-01-11
//     URL: https://github.com/RobTillaart/MAX6675
//
// HISTORY: see changelog.md


#include "MAX6675.h"


MAX6675::MAX6675()
{
}


void MAX6675::begin(const uint8_t select)
{
  begin(255, select, 255);
}


void MAX6675::begin(const uint8_t clock, const uint8_t select, const uint8_t miso)
{
  _clock        = clock;
  _miso         = miso;
  _select       = select;
  _hwSPI        = (_clock == 255);

  _lastTimeRead = 0;
  _offset       = 0;
  _status       = STATUS_NOREAD;
  _temperature  = MAX6675_NO_TEMPERATURE;
  _rawData      = 0;
  setSPIspeed(1000000);

  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  if (_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      //  HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, _select);   //  CLK=14  MISO=12  MOSI=13
    }
    else               //  VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, _select);   //  CLK=18  MISO=19  MOSI=23
    }
    #else              //  generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
    delay(1);
  }
  else
  {
    pinMode(_clock, OUTPUT);
    digitalWrite(_clock, LOW);
    pinMode(_miso, INPUT);
  }
}


void MAX6675::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


#if defined(ESP32)
void MAX6675::setGPIOpins(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clock;
  _miso    = miso;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  //  disable SPI and enable again
  mySPI->end();
  mySPI->begin(clock, miso, mosi, select);
}
#endif


uint8_t MAX6675::read()
{
  //  return value of _read()  page 5 datasheet
  //  BITS       DESCRIPTION
  //  ------------------------------
  //       00    three state ?
  //       01    device ID ?
  //       02    INPUT OPEN
  //  03 - 14    TEMPERATURE (RAW)
  //       15    SIGN
  uint16_t value = _read();

  // needs a pull up on MISO pin to work properly!
  if (value == 0xFFFF)
  {
    _status = STATUS_NO_COMMUNICATION;
    return _status;
  }

  _lastTimeRead = millis();

  //  process status bit 2
  _status = value & 0x04;

   value >>= 3;

  //  process temperature bits
  _temperature = (value & 0x1FFF) * 0.25;
  //  dummy negative flag set ?
  //  if (value & 0x2000)
  return _status;
}


uint32_t MAX6675::_read(void)
{
  _rawData = 0;
  //  DATA TRANSFER
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    digitalWrite(_select, LOW);
    _rawData = mySPI->transfer(0);
    _rawData <<= 8;
    _rawData += mySPI->transfer(0);
    digitalWrite(_select, HIGH);
    mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    //  split _swSPIdelay in equal dLow and dHigh
    //  dLow should be longer one when _swSPIdelay = odd.
    uint16_t dHigh = _swSPIdelay/2;
    uint16_t dLow = _swSPIdelay - dHigh;
    digitalWrite(_select, LOW);
    for (int8_t i = 15; i >= 0; i--)
    {
      _rawData <<= 1;
      digitalWrite(_clock, LOW);
      if (dLow > 0) delayMicroseconds(dLow);    //  DUE might need 1 us
      if ( digitalRead(_miso) ) _rawData++;
      digitalWrite(_clock, HIGH);
      if (dHigh > 0) delayMicroseconds(dHigh);  //  DUE
    }
    digitalWrite(_select, HIGH);
  }

  return _rawData;
}


// -- END OF FILE --

