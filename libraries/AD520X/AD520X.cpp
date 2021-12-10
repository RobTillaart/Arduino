//
//    FILE: AD520X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.2.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers (+ older AD8400, AD8402, AD8403)
//     URL: https://github.com/RobTillaart/AD520X
//
// HISTORY:
//  0.0.1   2020-07-24  initial version
//  0.0.2   2020-07-25  support for AD8400 series in documentation.
//  0.1.0   2020-07-26  refactor, fix #2 select pin for HW SPI; add shutdown.
//  0.1.1   2020-12-08  Arduino-CI + unit test + isPowerOn()
//  0.1.2   2021-08-19  VSPI / HSPI support for ESP32 only
//                      add setGPIOpins for ESP32 only
//                      add SetSPIspeed (generic)
//  0.2.0   2021-10-16  update build-CI
//                      add get- and setPercentage()
//  0.2.1   2021-12-10  update library.json, licence
//                      default value for setAll()


#include "AD520X.h"


AD520X::AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
{
  _pmCount  = 6;
  _select   = select;
  _dataOut  = dataOut;
  _clock    = clock;
  _reset    = reset;
  _shutdown = shutdown;
  _hwSPI    = (dataOut == 255) && (clock == 255);
}


//  initializes the pins and starts SPI in case of hardware SPI
void AD520X::begin(uint8_t value)
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, LOW);
  pinMode(_shutdown, OUTPUT);
  digitalWrite(_shutdown, LOW);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      //  HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, _select);   //  CLK=14 MISO=12 MOSI=13
    }
    else               //  VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, _select);   //  CLK=18 MISO=19 MOSI=23
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
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  setAll(value);
}


#if defined(ESP32)
void AD520X::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clk;
  _dataOut = mosi;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();                 //  disable SPI and restart
  mySPI->begin(clk, miso, mosi, select);
}
#endif


bool AD520X::setValue(uint8_t pm, uint8_t value)
{
  if (pm >= _pmCount) return false;
  _value[pm] = value;
  updateDevice(pm);
  return true;
}


void  AD520X::setAll(uint8_t value)
{
  for (uint8_t pm = 0; pm < _pmCount; pm++)
  {
    setValue(pm, value);
  }
}


uint8_t AD520X::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
}


bool AD520X::setPercentage(uint8_t pm, float percentage)
{
  if ((percentage < 0) || (percentage > 100.0)) return false;
  return setValue(pm, round(percentage * (255.0 / 100.0)));
}


float AD520X::getPercentage(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  uint8_t v = _value[pm];
  if (v == 0) return 0.0;
  return (100.0 / 255.0) * v;
}


void AD520X::reset(uint8_t value)
{
  digitalWrite(_reset, HIGH);
  digitalWrite(_reset, LOW);
  setAll(value);
}


void AD520X::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


/////////////////////////////////////////////////////////////////////////////
//
// PROTECTED
//
void AD520X::updateDevice(uint8_t pm)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(pm);
    mySPI->transfer(_value[pm]);
    mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer(pm);
    swSPI_transfer(_value[pm]);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD520X::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(val & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AD5206::AD5206(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 6;
}


AD5204::AD5204(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 4;
}


AD8403::AD8403(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 4;
}


AD8402::AD8402(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 2;
}


AD8400::AD8400(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 1;
}

// -- END OF FILE --
