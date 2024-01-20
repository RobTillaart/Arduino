//
//    FILE: AD9833.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AD9833 function generator
// VERSION: 0.4.0
//     URL: https://github.com/RobTillaart/AD9833
//

#include "AD9833.h"

//  FREQUENCY REGISTER BITS
#define AD9833_FREG1        0x8000
#define AD9833_FREG0        0x4000

//  CONTROL REGISTER BITS
#define AD9833_B28          (1 << 13)
#define AD9833_HLB          (1 << 12)
#define AD9833_FSELECT      (1 << 11)
#define AD9833_PSELECT      (1 << 10)
#define AD9833_RESET        (1 << 8)
#define AD9833_SLEEP1       (1 << 7)
#define AD9833_SLEEP12      (1 << 6)
#define AD9833_OPBITEN      (1 << 5)
#define AD9833_DIV2         (1 << 3)
#define AD9833_MODE         (1 << 1)



//  HARDWARE SPI
AD9833::AD9833(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _selectPin = slaveSelect;
  _hwSPI     = true;
  _mySPI     = mySPI;
}

//  SOFTWARE SPI
AD9833::AD9833(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _selectPin = slaveSelect;
  _dataPin   = spiData;
  _clockPin  = spiClock;
  _hwSPI     = false;
  _mySPI     = NULL;
}


void AD9833::begin()
{
  _useSelect = (_selectPin != 255);
  if (_useSelect)
  {
    pinMode(_selectPin, OUTPUT);
    digitalWrite(_selectPin, HIGH);
  }

  _spi_settings = SPISettings(8000000, MSBFIRST, SPI_MODE2);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataPin,  OUTPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_dataPin,  LOW);
    digitalWrite(_clockPin, HIGH);
  }
  reset();
}


void AD9833::reset()
{
  hardwareReset();
  _control = AD9833_B28;  //  implicit select sine wave.
  writeControlRegister(_control);
}


void AD9833::hardwareReset()
{
  writeControlRegister(_control | AD9833_RESET);
  //  reset all library variables to be in "sync" with hardware.
  _control  = 0;
  _waveform = AD9833_OFF;
  _freq[0]  = _freq[1]  = 0;
  _phase[0] = _phase[1] = 0;
}


bool AD9833::setPowerMode(uint8_t mode)
{
  if (mode > 3) return false;
  _control &= 0xFF3F;       //  clear previous power flags
  _control |= (mode << 6);  //  set the new power flags
  writeControlRegister(_control);
  return true;
}


void AD9833::setWave(uint8_t waveform)
{
  if (waveform > 4) return;

  //  store waveform
  _waveform = waveform;

  //  clear bits in control register
  _control &= ~(AD9833_SLEEP1 | AD9833_SLEEP12 | AD9833_OPBITEN | AD9833_MODE | AD9833_DIV2);

  //  set bits in control register
  switch(_waveform)
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
  return _waveform;
}


float AD9833::setFrequency(float frequency, uint8_t channel)
{
  if (channel > 1) return -1;
  _freq[channel] = frequency;
  if (_freq[channel] > AD9833_MAX_FREQ) _freq[channel] = AD9833_MAX_FREQ;
  if (_freq[channel] < 0) _freq[channel] = 0;

  //  convert to bit pattern
  //  fr = round(frequency * pow(2, 28) / 25 MHz));  //  25 MHz == crystal frequency.
  //  _crystalFreqFactor == (pow(2, 28) / crystal frequency);
  //  rounding
  uint32_t freq = round(_freq[channel] * _crystalFreqFactor);

  writeFrequencyRegister(channel, freq);

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
//  LOW LEVEL API - Expert users only
//
void AD9833::writeControlRegister(uint16_t value)
{
  uint16_t data = value & 0x3FFF;  //  bit 15 and 14 == 00
  writeData(data);
}


void AD9833:: writeFrequencyRegister(uint8_t channel, uint32_t freq)
{
  uint16_t LSB = 0;
  uint16_t MSB = 0;
  if (channel > 1) return;
  if (channel == 0) LSB = AD9833_FREG0;  //  bit 15 and 14    01
  if (channel == 1) LSB = AD9833_FREG1;  //  bit 15 and 14    10
  //  copy channel mask.
  MSB = LSB;

  //  be sure B28 bit is set.
  _control |= AD9833_B28;
  writeControlRegister(_control);

  //  28 bits in two sets of 14
  LSB |= (freq & 0x3FFF);
  MSB |= ((freq >> 14) & 0x3FFF);

  //  faster to write them in one SPI transaction
  writeData28(LSB, MSB);
  //  first send the least significant 14 bits
  //  writeData(LSB);
  //  then send the most significant 14 bits
  //  writeData(MSB);
}


void AD9833::writePhaseRegister(uint8_t channel, uint16_t value)
{
  uint16_t data = 0;
  if (channel > 1) return;
  if (channel == 0) data = 0xC000;  //  bit 15 and 14 and 13   110
  if (channel == 1) data = 0xE000;  //  bit 15 and 14 and 13   111

  data |= (value & 0x0FFF);
  writeData(data);
}


void AD9833::setCrystalFrequency(float crystalFrequency)
{
  //  calculate the often used factor
  _crystalFreqFactor = 268435456.0 / crystalFrequency;
}


float AD9833::getCrystalFrequency()
{
  return 268435456.0 / _crystalFreqFactor;
}



///////////////////////////////////////////////////////////////////
//
//  EXPERIMENTAL
//
void AD9833::writeFrequencyRegisterLSB(uint8_t channel, uint16_t LSB)
{
  if (channel > 1) return;
  //  force 14 bit
  LSB &= 0x3FFF;
  if (channel == 0) LSB |= AD9833_FREG0;  //  bit 15 and 14    01
  if (channel == 1) LSB |= AD9833_FREG1;  //  bit 15 and 14    10

  //  be sure B28 and HLB bit is cleared.
  _control &= ~AD9833_B28;
  _control &= ~AD9833_HLB;
  writeControlRegister(_control);

  //  send the least significant 14 bits
  writeData(LSB);
}


void AD9833::writeFrequencyRegisterMSB(uint8_t channel, uint16_t MSB)
{
  if (channel > 1) return;
  //  force 14 bit
  MSB &= 0x3FFF;
  if (channel == 0) MSB |= AD9833_FREG0;  //  bit 15 and 14    01
  if (channel == 1) MSB |= AD9833_FREG1;  //  bit 15 and 14    10

  //  be sure B28 is cleared and HLB bit is set.
  _control &= ~AD9833_B28;
  _control |= AD9833_HLB;
  writeControlRegister(_control);

  //  send the least significant 14 bits
  writeData(MSB);
}



///////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
void AD9833::writeData(uint16_t data)
{
  if (_useSelect) digitalWrite(_selectPin, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer16(data);
    _mySPI->endTransaction();
  }
  else
  {
    //  local variables is fast.
    uint8_t clk = _clockPin;
    uint8_t dao = _dataPin;
    //  MSBFIRST
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (data & mask) !=0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }
    digitalWrite(dao, LOW);
  }
  if (_useSelect) digitalWrite(_selectPin, HIGH);
}


void AD9833::writeData28(uint16_t LSB, uint16_t MSB)
{
  if (_useSelect) digitalWrite(_selectPin, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer16(LSB);
    _mySPI->transfer16(MSB);
    _mySPI->endTransaction();
  }
  else
  {
    //  local variables is fast.
    uint8_t clk = _clockPin;
    uint8_t dao = _dataPin;
    //  MSBFIRST
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (LSB & mask) !=0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }

    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (MSB & mask) !=0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }

    digitalWrite(dao, LOW);
  }
  if (_useSelect) digitalWrite(_selectPin, HIGH);
}



//  -- END OF FILE --
