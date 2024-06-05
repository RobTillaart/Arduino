//
//    FILE: MCP_DAC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
//    DATE: 2021-02-03
// PURPOSE: Arduino library for MCP_DAC
//     URL: https://github.com/RobTillaart/MCP_DAC


#include "MCP_DAC.h"


//  HW SPI
MCP_DAC::MCP_DAC(__SPI_CLASS__ *inSPI)
{
  mySPI     = inSPI;
  _dataOut  = 255;
  _clock    = 255;
  _select   = 0;
  _hwSPI    = true;
  _channels = 1;
  _maxValue = 255;
  reset();
}


//  SW SPI
MCP_DAC::MCP_DAC(uint8_t dataOut,  uint8_t clock)
{
  mySPI     = NULL;
  _dataOut  = dataOut;
  _clock    = clock;
  _select   = 0;
  _hwSPI    = false;
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
    //  mySPI->end();
    //  mySPI->begin();
  }
  else  //  software SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
}


uint8_t MCP_DAC::channels()
{
  return _channels;
}


uint16_t MCP_DAC::maxValue()
{
  return _maxValue;
}


bool MCP_DAC::setGain(uint8_t gain)
{
  if ((0 == gain) || (gain > 2)) return false;
  _gain = gain;
  return true;
}


uint8_t MCP_DAC::getGain()
{
  return _gain;
}


bool MCP_DAC::write(uint16_t value, uint8_t channel)
{
  if (channel >= _channels) return false;

  //  CONSTRAIN VALUE
  uint16_t _val = value;
  if (_val > _maxValue) _val = _maxValue;
  _value[channel] = value;

  //  PREPARING THE DATA TRANSFER
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


uint16_t MCP_DAC::lastValue(uint8_t channel)
{
  return _value[channel];
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
  return write(_value[channel] + 1,  channel);
}


bool MCP_DAC::decrement(uint8_t channel)
{
  if (channel >= _channels) return false;
  if (_value[channel] == 0) return false;
  return write(_value[channel] - 1,  channel);
}


void MCP_DAC::setPercentage(float perc, uint8_t channel)
{
  if (perc < 0) perc = 0;
  if (perc > 100) perc = 100;
  write((0.01 * perc * _maxValue), channel);
}


float MCP_DAC::getPercentage(uint8_t channel)
{
  return (_value[channel] * 100.0) / _maxValue;
}


void MCP_DAC::setLatchPin(uint8_t latchPin)
{
  _latchPin = latchPin;
  pinMode(_latchPin, OUTPUT);
  digitalWrite(_latchPin, HIGH);
}


void MCP_DAC::triggerLatch()
{
  if (_latchPin != 255)
  {
    digitalWrite(_latchPin, LOW);
    //  delay needed == 100 ns - Page 7
    //  on "slow" devices the next delay can be commented
    delayMicroseconds(1);
    digitalWrite(_latchPin, HIGH);
  }
}


void MCP_DAC::shutDown()
{
  _active = false;
  transfer(0x0000);  //  a write will reset the values.
}


bool MCP_DAC::isActive()
{
  return _active;
}


void MCP_DAC::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


uint32_t MCP_DAC::getSPIspeed()
{
  return _SPIspeed;
}


void MCP_DAC::setBufferedMode(bool mode)
{
  _buffered = mode;
}


bool MCP_DAC::getBufferedMode()
{
  return _buffered;
}


bool MCP_DAC::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void MCP_DAC::transfer(uint16_t data)
{
  //  DATA TRANSFER
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer((uint8_t)(data >> 8));
    mySPI->transfer((uint8_t)(data & 0xFF));
    mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer((uint8_t)(data >> 8));
    swSPI_transfer((uint8_t)(data & 0xFF));
  }
  digitalWrite(_select, HIGH);
}


//  MSBFIRST
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
//  DERIVED CLASSES
//

/////////////////////////////////////////////////////////////////////////////
//
//  MCP4800 series
//

MCP4801::MCP4801(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 255;
};

MCP4801::MCP4801(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 255;
};

MCP4802::MCP4802(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 255;
};

MCP4802::MCP4802(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 255;
};

MCP4811::MCP4811(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 1023;
};

MCP4811::MCP4811(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 1023;
};

MCP4812::MCP4812(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 1023;
};

MCP4812::MCP4812(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
};

MCP4821::MCP4821(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 4095;
};

MCP4821::MCP4821(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 4095;
};

MCP4822::MCP4822(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 4095;
};

MCP4822::MCP4822(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
};


/////////////////////////////////////////////////////////////////////////////
//
//  MCP4900 series
//
MCP4901::MCP4901(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 255;
};

MCP4901::MCP4901(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 255;
};

MCP4902::MCP4902(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 255;
};

MCP4902::MCP4902(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 255;
};

MCP4911::MCP4911(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 1023;
};

MCP4911::MCP4911(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 1023;
};

MCP4912::MCP4912(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 1023;
};

MCP4912::MCP4912(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
};

MCP4921::MCP4921(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 1;
  _maxValue = 4095;
};

MCP4921::MCP4921(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 1;
  _maxValue = 4095;

};

MCP4922::MCP4922(__SPI_CLASS__ *inSPI) : MCP_DAC(inSPI)
{
  _channels = 2;
  _maxValue = 4095;
};

MCP4922::MCP4922(uint8_t dataOut, uint8_t clock) : MCP_DAC(dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
};


//  -- END OF FILE --

