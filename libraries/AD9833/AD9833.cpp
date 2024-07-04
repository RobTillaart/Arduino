//
//    FILE: AD9833.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AD9833 function generator
//    DATE: 2023-08-25
// VERSION: 0.4.2
//     URL: https://github.com/RobTillaart/AD9833


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

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
    uint8_t _port    = digitalPinToPort(_dataPin);
    _dataOutRegister = portOutputRegister(_port);
    _dataOutBit      = digitalPinToBitMask(_dataPin);
    _port            = digitalPinToPort(_clockPin);
    _clockRegister   = portOutputRegister(_port);
    _clockBit        = digitalPinToBitMask(_clockPin);
#endif
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
  //  clear previous power bits
  _control &= ~(AD9833_SLEEP1 | AD9833_SLEEP12);
  _control |= (mode << 6);  //  set the new power bits
  writeControlRegister(_control);
  return true;
}


uint8_t AD9833::getPowerMode()
{
  return (_control & (AD9833_SLEEP1 | AD9833_SLEEP12)) >> 6;
}


void AD9833::setWave(uint8_t waveform)
{
  if (waveform > AD9833_TRIANGLE) return;

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
  //  if (_freq[channel] == frequency) return frequency;
  //  local variable is faster.
  float newFrequency = frequency;
  if (newFrequency < 0) newFrequency = 0;
  else if (newFrequency > AD9833_MAX_FREQ) newFrequency = AD9833_MAX_FREQ;

  //  convert to bit pattern
  //  fr = round(frequency * pow(2, 28) / 25 MHz));  //  25 MHz == crystal frequency.
  //  _crystalFreqFactor == (pow(2, 28) / crystal frequency);
  //  round() to minimize error / use the whole range
  uint32_t freq = round(newFrequency * _crystalFreqFactor);

  writeFrequencyRegister(channel, freq);

  //  cache the newFrequency;
  _freq[channel] = newFrequency;
  return newFrequency;
}


float AD9833::getFrequency(uint8_t channel)
{
  //  return round(_freq[channel] * _crystalFreqFactor) / _crystalFreqFactor;
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
  //  local variable is faster.
  float newPhase = phase;
  while (newPhase >= AD9833_MAX_PHASE) newPhase -= AD9833_MAX_PHASE;
  while (newPhase <  0) newPhase += AD9833_MAX_PHASE;

  //  round() to minimize error / use the whole range 0..4095
  uint16_t ph = round(newPhase * (4095.0 / 360.0));
  writePhaseRegister(channel, ph);

  //  cache the newPhase
  _phase[channel] = newPhase;
  return newPhase;
}


float AD9833::getPhase(uint8_t channel)
{
  //  more precise => more math;
  //  return round(_phase[channel] * (4095.0 / 360.0)) / (4095.0 / 360.0);
  return _phase[channel];
}


//  returns phase set (radians) - not optimized.
//  [0 .. 2 PI>
float AD9833::setPhaseRadians(float phase, uint8_t channel)
{
  return setPhase(phase * RAD_TO_DEG, channel) * DEG_TO_RAD;
}


float AD9833::getPhaseRadians(uint8_t channel)
{
  return getPhase(channel) * DEG_TO_RAD;
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
  //  268435456.0 == POW2TO28
  _crystalFreqFactor = 268435456.0 / crystalFrequency;
}


float AD9833::getCrystalFrequency()
{
  //  268435456.0 == POW2TO28
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

  //  send the most significant 14 bits
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
    //  SPI MODE2
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

    uint8_t cbmask1  = _clockBit;
    uint8_t cbmask2  = ~_clockBit;
    uint8_t outmask1 = _dataOutBit;
    uint8_t outmask2 = ~_dataOutBit;

    //  MSBFIRST
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      uint8_t oldSREG = SREG;
      noInterrupts();
      if (data & mask) *_dataOutRegister |= outmask1;
      else             *_dataOutRegister &= outmask2;
      *_clockRegister &= cbmask2;
      *_clockRegister |= cbmask1;
      SREG = oldSREG;
    }

#else  //  REFERENCE IMPLEMENTATION

    //  local variables is fast.
    uint8_t clk = _clockPin;
    uint8_t dao = _dataPin;
    //  MSBFIRST
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (data & mask) != 0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }

#endif
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
    //  SPI MODE2
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

    uint8_t cbmask1  = _clockBit;
    uint8_t cbmask2  = ~_clockBit;
    uint8_t outmask1 = _dataOutBit;
    uint8_t outmask2 = ~_dataOutBit;

    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      uint8_t oldSREG = SREG;
      noInterrupts();
      if (LSB & mask) *_dataOutRegister |= outmask1;
      else            *_dataOutRegister &= outmask2;
      *_clockRegister &= cbmask2;
      *_clockRegister |= cbmask1;
      SREG = oldSREG;
    }

    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      uint8_t oldSREG = SREG;
      noInterrupts();
      if (MSB & mask) *_dataOutRegister |= outmask1;
      else            *_dataOutRegister &= outmask2;
      *_clockRegister &= cbmask2;
      *_clockRegister |= cbmask1;
      SREG = oldSREG;
    }

#else  //  REFERENCE IMPLEMENTATION

    //  local variables is fast.
    uint8_t clk = _clockPin;
    uint8_t dao = _dataPin;

    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (LSB & mask) != 0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }

    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(dao, (MSB & mask) != 0 ? HIGH : LOW);
      digitalWrite(clk, LOW);
      digitalWrite(clk, HIGH);
    }

#endif
  }
  if (_useSelect) digitalWrite(_selectPin, HIGH);
}



//  -- END OF FILE --
