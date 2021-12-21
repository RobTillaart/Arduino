//
//    FILE: MCP_DAC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2021-02-03
// PURPOSE: Arduino library for MCP_DAC
//     URL: https://github.com/RobTillaart/MCP_DAC
//
//  HISTORY
//  0.1.0   2021-02-03  initial version
//  0.1.1   2021-05-26  moved SPI.begin() from constructor to begin()
//  0.1.2   2021-07-29  VSPI / HSPI support for ESP32 (default pins only
//                      faster software SPI
//                      minor optimizations / refactor
//  0.1.3   2021-07-31  add increment() and decrement()
//  0.1.4   2021-08-01  fix setGPIOpins() - needs more testing.
//  0.1.5   2021-11-08  update build-CI, badges,
//                      default parameter 1 for setGain()
//                      default parameter false for setBufferedMode()
//                      default parameter 0 for getPercentage()
//                      extended unit tests
//  0.1.6   2021-12-21  update library.json, license, minor edits


#include "MCP_DAC.h"


MCP_DAC::MCP_DAC(uint8_t dataOut,  uint8_t clock)
{
  _dataOut  = dataOut;
  _clock    = clock;
  _select   = 0;
  _hwSPI    = (dataOut == 255) || (clock == 255);
  _channels = 1;
  _maxValue = 255;
  reset();
}


void MCP_DAC::reset()
{
  _gain     = 1;
  _value[0] = 0;
  _value[1] = 0;
  _buffered = false;
  _active   = true;
}


void MCP_DAC::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      // HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, select);   // CLK=14 MISO=12 MOSI=13
    }
    else               // VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, select);   // CLK=18 MISO=19 MOSI=23
    }
    #else              // generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
  }
  else                 // software SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
}


#if defined(ESP32)
void MCP_DAC::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clk;
  _dataOut = mosi;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();  // disable SPI
  mySPI->begin(clk, miso, mosi, select);
}
#endif


bool MCP_DAC::setGain(uint8_t gain)
{
  if ((0 == gain) || (gain > 2)) return false;
  _gain = gain;
  return true;
}


bool MCP_DAC::analogWrite(uint16_t value, uint8_t channel)
{
  if (channel >= _channels) return false;

  // CONSTRAIN VALUE
  uint16_t _val = value;
  if (_val > _maxValue) _val = _maxValue;
  _value[channel] = value;

  // PREPARING THE DATA TRANSFER
  uint16_t data = 0x1000;
  if (channel == 1) data |= 0x8000;
  if (_buffered)    data |= 0x4000;
  if (_gain == 1)   data |= 0x2000;

  if (_maxValue == 4095)      data |= _val;
  else if (_maxValue == 1023) data |= (_val << 2);
  else                        data |= (_val << 4);
  transfer(data);
  return true;
}


void MCP_DAC::fastWriteA(uint16_t value)
{
  transfer(0x3000 | value);
}


void MCP_DAC::fastWriteB(uint16_t value)
{
  transfer(0xB000 | value);
}


bool MCP_DAC::increment(uint8_t channel)
{
  if (channel >= _channels) return false;
  if (_value[channel] == _maxValue) return false;
  return analogWrite(_value[channel] + 1,  channel);
}


bool MCP_DAC::decrement(uint8_t channel)
{
  if (channel >= _channels) return false;
  if (_value[channel] == 0) return false;
  return analogWrite(_value[channel] - 1,  channel);
}


void MCP_DAC::setPercentage(float perc, uint8_t channel)
{
  if (perc < 0) perc = 0;
  if (perc > 100) perc = 100;
  analogWrite(perc * _maxValue, channel);
}


float MCP_DAC::getPercentage(uint8_t channel)
{
  return (_value[channel] * 100.0) / _maxValue;
}


void MCP_DAC::setLatchPin(uint8_t latchPin)
{
  _latchPin = latchPin;
  pinMode(_latchPin, OUTPUT);
  digitalWrite(_latchPin, LOW);
}


void MCP_DAC::triggerLatch()
{
  if (_latchPin != 255)
  {
    digitalWrite(_latchPin, HIGH);
    delayMicroseconds(1);     // 100 ns - Page 7
    digitalWrite(_latchPin, LOW);
  }
}


void MCP_DAC::shutDown()
{
  _active = false;
  transfer(0x0000);  // a write will reset the values..
}


void MCP_DAC::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


//////////////////////////////////////////////////////////////////
//
// PROTECTED
//
void MCP_DAC::transfer(uint16_t data)
{
  // DATA TRANSFER
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    // mySPI->beginTransaction(SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0));
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer((uint8_t)(data >> 8));
    mySPI->transfer((uint8_t)(data & 0xFF));
    mySPI->endTransaction();
  }
  else // Software SPI
  {
    swSPI_transfer((uint8_t)(data >> 8));
    swSPI_transfer((uint8_t)(data & 0xFF));
  }
  digitalWrite(_select, HIGH);
}


// MSBFIRST
uint8_t MCP_DAC::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao, (val & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
  return 0;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP4800 series
//
MCP4801::MCP4801(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 255;
};


MCP4802::MCP4802(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 255;
};


MCP4811::MCP4811(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 1023;
};


MCP4812::MCP4812(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
};


MCP4821::MCP4821(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 4095;
};


MCP4822::MCP4822(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
};


/////////////////////////////////////////////////////////////////////////////
//
// MCP4900 series
//
MCP4901::MCP4901(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 255;
};


MCP4902::MCP4902(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 255;
};


MCP4911::MCP4911(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 1023;
};


MCP4912::MCP4912(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
};


MCP4921::MCP4921(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 4095;

};


MCP4922::MCP4922(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
};


// -- END OF FILE --

