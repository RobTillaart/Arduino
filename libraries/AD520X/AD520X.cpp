//
//    FILE: AD520X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.3.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers
//          (+ AD8400, AD8402, AD8403)
//     URL: https://github.com/RobTillaart/AD520X


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
  digitalWrite(_reset, HIGH);
  pinMode(_shutdown, OUTPUT);
  digitalWrite(_shutdown, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

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


/////////////////////////////////////////////////////////////////////////////
//
//  SET VALUE
//
bool AD520X::setValue(uint8_t pm, uint8_t value)
{
  if (pm >= _pmCount) return false;
  _value[pm] = value;
  updateDevice(pm, value);
  return true;
}


uint8_t AD520X::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
}


//  STEREO same value
bool AD520X::setValue(uint8_t pmA, uint8_t pmB, uint8_t value)
{
  if ((pmA >= _pmCount) || (pmB >= _pmCount)) return false;
  _value[pmA] = value;
  updateDevice(pmA, value);
  _value[pmB] = value;
  updateDevice(pmB, value);
  return true;
}


void  AD520X::setAll(uint8_t value)
{
  for (uint8_t pm = 0; pm < _pmCount; pm++ )
  {
    _value[pm] = value;
    updateDevice(pm, value);
  }
}


void  AD520X::setGroupValue(uint8_t mask, uint8_t value)
{
  uint8_t m = 0x01;
  for (uint8_t pm = 0; pm < _pmCount; pm++ )
  {
    if (mask & m)
    {
      _value[pm] = value;
      updateDevice(pm, value);
    }
    m <<= 1;
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  SET PERCENTAGE
//
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


//  STEREO same percentage
bool AD520X::setPercentage(uint8_t pmA, uint8_t pmB, float percentage)
{
  if ((percentage < 0) || (percentage > 100.0)) return false;
  return setValue(pmA, pmB, round(percentage * (255.0 / 100.0)));
}


void AD520X::setGroupPercentage(uint8_t mask, float percentage)
{
  uint8_t m = 0x01;
  for (uint8_t pm = 0; pm < _pmCount; pm++ )
  {
    if (mask & m)
    {
      setValue(pm, round(percentage * (255.0 / 100.0)));
    }
    m <<= 1;
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  OTHER
//
void AD520X::reset(uint8_t value)
{
  digitalWrite(_reset, LOW);
  digitalWrite(_reset, HIGH);
  setAll(value);
}


uint8_t AD520X::pmCount()
{
  return _pmCount;
}


void AD520X::powerOn()
{
  digitalWrite(_shutdown, HIGH);
}


void AD520X::powerOff()
{
  digitalWrite(_shutdown, LOW);
}


bool AD520X::isPowerOn()
{
  return digitalRead(_shutdown) == HIGH;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void AD520X::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


uint32_t AD520X::getSPIspeed()
{
  return _SPIspeed;
}


bool AD520X::usesHWSPI()
{
  return _hwSPI;
};


#if defined(ESP32)

void AD520X::selectHSPI()
{
  _useHSPI = true;
}


void AD520X::selectVSPI()
{
  _useHSPI = false;
}


bool AD520X::usesHSPI()
{
  return _useHSPI;
}


bool AD520X::usesVSPI()
{
  return !_useHSPI;
}


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


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void AD520X::updateDevice(uint8_t pm, uint8_t value)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(pm);
    mySPI->transfer(value);
    mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer(pm);
    swSPI_transfer(value);
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
