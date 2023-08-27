//
//    FILE: AD9833.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AD9833 function generator
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/AD9833
//

#include "AD9833.h"

//  CONTROL REGISTER BITS
#define AD9833_B28      (1 << 13)
#define AD9833_HLB      (1 << 12)
#define AD9833_FSELECT  (1 << 11)
#define AD9833_PSELECT  (1 << 10)
#define AD9833_RESET    (1 << 8)
#define AD9833_SLEEP1   (1 << 7)
#define AD9833_SLEEP12  (1 << 6)
#define AD9833_OPBITEN  (1 << 5)
#define AD9833_DIV2     (1 << 3)
#define AD9833_MODE     (1 << 1)


AD9833::AD9833()
{
}


void AD9833::begin(uint8_t selectPin, uint8_t dataPin, uint8_t clockPin)
{
  _selectPin = selectPin;
  _dataPin   = dataPin;
  _clockPin  = clockPin;

  pinMode(_selectPin, OUTPUT);
  digitalWrite(_selectPin, HIGH);

  _hwSPI = ((dataPin == 0) || (clockPin == 0));

  _spi_settings = SPISettings(8000000, MSBFIRST, SPI_MODE2);

  if (_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      //  HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, selectPin);   //  CLK = 14  MISO = 12  MOSI = 13
    }
    else               //  VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, selectPin);   //  CLK = 18  MISO = 19  MOSI = 23
    }
    #else              //  generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
  }
  else                 //  software SPI
  {
    pinMode(_dataPin,  OUTPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_dataPin,  LOW);
    digitalWrite(_clockPin, LOW);
  }
  reset();
}


void AD9833::begin(uint8_t selectPin, SPIClass * spi)
{
  _selectPin = selectPin;
  pinMode(_selectPin, OUTPUT);
  digitalWrite(_selectPin, HIGH);

  _hwSPI = true;
  _spi_settings = SPISettings(8000000, MSBFIRST, SPI_MODE2);

  mySPI = spi;
  mySPI->end();
  mySPI->begin();

  reset();
}


void AD9833::reset()
{
  setWave(AD9833_OFF);
  setFrequency(1000, 0);
  setFrequency(1000, 1);
  setPhase(0, 0);
  setPhase(0, 1);
}


void AD9833::setWave(uint8_t waveType)
{
  if (waveType > 4) return;

  //  store wave type
  _waveType = waveType;

  //  clear bits in control register
  _control &= ~(AD9833_SLEEP1 | AD9833_SLEEP12 | AD9833_OPBITEN | AD9833_MODE);

  //  set bits in control register
  switch(_waveType)
  {
    case AD9833_OFF:
      _control |= (AD9833_SLEEP1 | AD9833_SLEEP12);
    break;
    case AD9833_SINE:
      //  no bits need to set
    break;
    case AD9833_SQUARE1:
      _control |= (AD9833_DIV2 | AD9833_OPBITEN);
    break;
    case AD9833_SQUARE2:
      _control |= (AD9833_OPBITEN);
    break;
    case AD9833_TRIANGLE:
      _control |= (AD9833_MODE);
    break;
  }
  writeControlRegister(_control);
}


uint8_t AD9833::getWave()
{
  return _waveType;
}


float AD9833::setFrequency(float freq, uint8_t channel)
{
  if (channel > 1) return -1;
  _freq[channel] = freq;
  if (_freq[channel] > AD9833_MAX_FREQ) _freq[channel] = AD9833_MAX_FREQ;
  if (_freq[channel] < 0) _freq[channel] = 0;

  //  convert to bit pattern
  //  fr = round(freq * pow(2, 28) / 25 MHz));
  //  rounding
  uint32_t fr = (_freq[channel] * (268435456.0 / 25000000.0) + 0.5);

  _control |= AD9833_B28;
  writeControlRegister(_control);
  writeFreqRegister(channel, fr);

  return _freq[channel];
}


float AD9833::getFrequency(uint8_t channel)
{
  return _freq[channel];
}


float AD9833::getMaxFrequency()
{
  return AD9833_MAX_FREQ;
}


void  AD9833::setFrequencyChannel(uint8_t channel)
{
  if (channel > 1) return;

  if (channel == 0) _control &= ~AD9833_FSELECT;
  if (channel == 1) _control |= AD9833_FSELECT;
  writeControlRegister(_control);
}


float AD9833::setPhase(float phase, uint8_t channel)
{
  if (channel > 1) return -1;
  _phase[channel] = phase;
  while (_phase[channel] >= AD9833_MAX_PHASE) _phase[channel] -= AD9833_MAX_PHASE;
  while (_phase[channel] <  0) _phase[channel] += AD9833_MAX_PHASE;

  uint16_t ph = _phase[channel] * (4095.0 / 360.0);
  writePhaseRegister(channel, ph);

  return _phase[channel];
}


float AD9833::getPhase(uint8_t channel)
{
  return _phase[channel];
}


float AD9833::getMaxPhase()
{
  return AD9833_MAX_PHASE;
}


void  AD9833::setPhaseChannel(uint8_t channel)
{
  if (channel > 1) return;

  if (channel == 0) _control &= ~AD9833_PSELECT;
  if (channel == 1) _control |= AD9833_PSELECT;
  writeControlRegister(_control);
}


void AD9833::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE2);
}


uint32_t AD9833::getSPIspeed()
{
  return _SPIspeed;
}


bool AD9833::usesHWSPI()
{
  return _hwSPI;
}


////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
void AD9833::writeControlRegister(uint16_t value)
{
  uint16_t data = value & 0x3FFF;  //  bit 15 and 14 == 00
  writeData(data);
}


void AD9833::writeFreqRegister(uint8_t reg, uint32_t freq)
{
  uint16_t data = 0;
  if (reg > 1) return;
  if (reg == 0) data = 0x4000;  //  bit 15 and 14    01
  if (reg == 1) data = 0x8000;  //  bit 15 and 14    10

  //  28 bits in two sets of 14
  data |= (freq & 0x3FFF);
  writeData(data);
  data &= 0xC000;
  data |= (freq >> 14);
  writeData(data);
}


void AD9833::writePhaseRegister(uint8_t reg, uint16_t value)
{
  uint16_t data = 0;
  if (reg > 1) return;
  if (reg == 0) data = 0xC000;  //  bit 15 and 14 and 13   110
  if (reg == 1) data = 0xE000;  //  bit 15 and 14 and 13   111

  data |= (value & 0x0FFF);
  writeData(data);
}


void AD9833::writeData(uint16_t data)
{
  digitalWrite(_selectPin, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer16(data);
    mySPI->endTransaction();
  }
  else
  {
    //  local variables is fast.
    uint8_t clk = _clockPin;
    uint8_t dao = _dataPin;
    //  MSBFIRST
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (data & mask));
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }
    digitalWrite(dao, LOW);
  }
  digitalWrite(_selectPin, HIGH);
}


//  -- END OF FILE --
