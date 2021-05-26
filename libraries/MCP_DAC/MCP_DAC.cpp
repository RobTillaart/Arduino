//
//    FILE: MCP_DAC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2021-02-03
// PURPOSE: Arduino library for MCP_DAC
//     URL: https://github.com/RobTillaart/MCP_DAC
//
//  HISTORY
//  0.1.0   2021-02-03  initial version
//  0.1.1   2021-05-26  moved SPI.begin() from constructor to begin()

#include "MCP_DAC.h"


MCP_DAC::MCP_DAC(uint8_t dataOut,  uint8_t clock)
{
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = (dataOut == 255) || (clock == 255);
  if (_hwSPI == false)
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
  _channels = 1;
  _maxValue = 255;
  _select   = 0;
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
  if (_hwSPI)
  {
    SPI.begin();
  }
}


bool MCP_DAC::setGain(uint8_t gain)
{
  if ((0 < gain) && (gain < 2)) return false;
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
  digitalWrite(_latchPin, HIGH);
  delayMicroseconds(1);     // 100 ns - Page 7
  digitalWrite(_latchPin, LOW);
}


void MCP_DAC::shutDown()
{
  _active = false;
  transfer(0x0000);  // a write will reset the values..
}


void MCP_DAC::transfer(uint16_t data)
{
  // DATA TRANSFER 
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0));
    SPI.transfer((uint8_t)(data >> 8));
    SPI.transfer((uint8_t)(data & 0xFF));
    SPI.endTransaction();
  }
  else // Software SPI
  {
    swSPI_transfer((uint8_t)(data >> 8));
    swSPI_transfer((uint8_t)(data & 0xFF));
  }
  digitalWrite(_select, HIGH);
}


// MSBFIRST
uint8_t  MCP_DAC::swSPI_transfer(uint8_t val)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_dataOut,(val & mask) != 0);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
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

