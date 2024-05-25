//
//    FILE: AD985X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.7.1
//    DATE: 2019-02-08
// PURPOSE: Class for AD9850 and AD9851 function generator
//     URL: https://github.com/RobTillaart/AD985X


#include "AD985X.h"


//  UNO HARDWARE SPI         PINS
//  #define SPI_CLOCK             13          //  not portable.
//  #define SPI_MISO              12
//  #define SPI_MOSI              11


#define AD985X_POWERDOWN      0x04


////////////////////////////////////////////////////////
//
//  AD9850
//

//  HARDWARE SPI
//  spiClock needed for RESET(). TODO: nicer solution?
AD9850::AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, __SPI_CLASS__ * mySPI, uint8_t spiClock)
{
  _select  = slaveSelect;
  _reset   = resetPin;
  _fqud    = FQUDPin;
  _hwSPI   = true;
  _mySPI   = mySPI;
  _dataOut = 0;
  _clock   = spiClock;
  _factoryMask = 0xFC;
}

//  SOFTWARE SPI
AD9850::AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, uint8_t spiData, uint8_t spiClock)
{
  _select  = slaveSelect;
  _reset   = resetPin;
  _fqud    = FQUDPin;
  _hwSPI   = false;
  _mySPI   = NULL;
  _dataOut = spiData;
  _clock   = spiClock;
  _factoryMask = 0xFC;
}


void AD9850::begin()
{

  //  following 3 are always set.
  pinMode(_select, OUTPUT);
  pinMode(_reset,  OUTPUT);
  pinMode(_fqud,   OUTPUT);
  pinMode(_clock,   OUTPUT);

  //  device select = HIGH  See - https://github.com/RobTillaart/AD985X/issues/13
  digitalWrite(_select, LOW);
  digitalWrite(_reset,  LOW);
  digitalWrite(_fqud,   LOW);
  digitalWrite(_clock,   LOW);

  _spi_settings = SPISettings(2000000, LSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataOut, OUTPUT);
    digitalWrite(_dataOut, LOW);
  }

  reset();
}


void AD9850::reset()
{
  //  be sure to select the correct device
  digitalWrite(_select, HIGH);
  pulsePin(_reset);
  pulsePin(_clock);
  digitalWrite(_select, LOW);

  _config = 0;    //  0 phase   no power down
  _freq   = 0;
  _factor = 0;
  _offset = 0;
  _autoUpdate = true;
  writeData();
}


void AD9850::powerDown()
{
  _config |= AD985X_POWERDOWN;      //  keep phase and REFCLK as is.
  writeData();
}


void AD9850::powerUp()
{
  _config &= ~AD985X_POWERDOWN;
  writeData();
}


bool AD9850::setPhase(uint8_t phase)
{
  if (phase > 31) return false;
  _config &= 0x07;          //  keep last three bits
  _config |= (phase << 3);  //  set new phase
  writeData();
  return true;
}


uint8_t AD9850::getPhase()
{
  return (_config >> 3);
}


void AD9850::pulsePin(uint8_t pin)
{
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}


void AD9850::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, LSBFIRST, SPI_MODE0);
};


void AD9850::writeData()
{
  //  Serial.println(_factor, HEX);
  //  Serial.println(_config, HEX);
  uint32_t data = _factor;

  //  used for multi device configuration only
  //  see https://github.com/RobTillaart/AD985X/issues/13
  digitalWrite(_select, HIGH);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(data & 0xFF);
    data >>= 8;
    _mySPI->transfer(data & 0xFF);
    data >>= 8;
    _mySPI->transfer(data & 0xFF);
    _mySPI->transfer(data >> 8);
    _mySPI->transfer(_config & _factoryMask);  //  mask factory test bits
    _mySPI->endTransaction();
  }
  else
  {
    swSPI_transfer(data & 0xFF);
    data >>= 8;
    swSPI_transfer(data & 0xFF);
    data >>= 8;
    swSPI_transfer(data & 0xFF);
    swSPI_transfer(data >> 8);
    swSPI_transfer(_config & _factoryMask);  //  mask factory test bits
  }
  digitalWrite(_select, LOW);

  //  update frequency + phase + control bits.
  //  should at least be 4 ns delay - P14 datasheet
  if (_autoUpdate) update();
}


//  simple one mode version
void AD9850::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  //  for (uint8_t mask = 0x80; mask; mask >>= 1)   //  MSBFIRST
  for (uint8_t mask = 0x01; mask; mask <<= 1)   //  LSBFIRST
  {
    digitalWrite(dao, (val & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


bool AD9850::setFrequency(uint32_t freq)
{
  bool rv = true;
  //  freq OUT = (Δ Phase × CLKIN)/2^32
  //  64 bit math to keep precision to the max
  if (freq > AD9850_MAX_FREQ)
  {
    rv = false;
    freq = AD9850_MAX_FREQ;
  }
  //  _factor = round(freq * 34.359738368);             //  4294967296 / 125000000
  _factor = (147573952589ULL * freq) >> 32;
  _freq = freq;
  _factor += _offset;
  writeData();
  return rv;
}


//  especially for lower frequencies (with decimals)
bool AD9850::setFrequencyF(float freq)
{
  bool rv = true;
  //  freq OUT = (Δ Phase × CLKIN)/2^32
  //  64 bit math to keep precision to the max
  if (freq > AD9850_MAX_FREQ)
  {
    rv = false;
    freq = AD9850_MAX_FREQ;
  }
  _factor = round(freq * 34.359738368);                //  4294967296 / 125000000
  _freq = freq;
  _factor += _offset;
  writeData();
  return rv;
}


float AD9850::getFrequency()
{
  return _freq;
}


uint32_t AD9850::getMaxFrequency()
{
  return AD9850_MAX_FREQ;
}


void AD9850::update()
{
  digitalWrite(_select, HIGH);
  pulsePin(_fqud);
  digitalWrite(_select, LOW);
}


////////////////////////////////////////////////////////
//
//  AD9851
//

//  bit is a 6x multiplier bit P.14 datasheet
#define AD9851_REFCLK        0x01

AD9851::AD9851(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, __SPI_CLASS__ * mySPI, uint8_t spiClock) : AD9850(slaveSelect, resetPin, FQUDPin, mySPI, spiClock)
{
  _factoryMask = 0xFD;
}


AD9851::AD9851(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, uint8_t spiData, uint8_t spiClock) : AD9850(slaveSelect, resetPin, FQUDPin, spiData, spiClock)
{
  _factoryMask = 0xFD;
}


bool AD9851::setFrequency(uint32_t freq)
{
  bool rv = true;
  //  PREVENT OVERFLOW
  if (freq > AD9851_MAX_FREQ)
  {
    rv = false;
    freq = AD9851_MAX_FREQ;
  }
  //  AUTO SWITCH REFERENCE FREQUENCY
  if (_autoRefClock)
  {
    if (freq > _ARCCutOffFreq)
    {
      _config |= AD9851_REFCLK;
    }
    else
    {
      _config &= ~AD9851_REFCLK;
    }
  }

  if (_config & AD9851_REFCLK)  //  6x 30 = 180 MHz
  {
    _factor = (102481911520ULL * freq) >> 32;  //  (1 << 64) / 180000000
  }
  else                          //  1x 30 = 30 MHz
  {
    _factor = (614891469123ULL * freq) >> 32;  //  (1 << 64) / 30000000
  }
  _freq = freq;
  _factor += _offset;
  writeData();
  return rv;
}


//  especially for lower frequencies (with decimals)
bool AD9851::setFrequencyF(float freq)
{
  bool rv = true;
  //  PREVENT OVERFLOW
  if (freq > AD9851_MAX_FREQ)
  {
    rv = false;
    freq = AD9851_MAX_FREQ;
  }

  //  AUTO SWITCH REFERENCE FREQUENCY
  if (_autoRefClock)
  {
    if (freq > _ARCCutOffFreq)
    {
      _config |= AD9851_REFCLK;
    }
    else
    {
      _config &= ~AD9851_REFCLK;
    }
  }

  if (_config & AD9851_REFCLK)  //  6x 30 = 180 MHz
  {
    _factor = uint64_t(102481911520ULL * freq) >> 32;  //  (1 << 64) / 180000000
  }
  else                          //  1x 30 = 30 MHz
  {
    _factor = (6148914691ULL * uint64_t (100 * freq)) >> 32;
  }

  _freq = freq;
  _factor += _offset;
  writeData();
  return rv;
}


uint32_t AD9851::getMaxFrequency()
{
  return AD9851_MAX_FREQ;
};


////////////////////////////////////////////////////////
//
//  AD9851 - AUTO REFERENCE CLOCK
//
void AD9851::setAutoRefClock(bool arc)
{
  _autoRefClock = arc;
  setFrequency(_freq);
};


bool AD9851::getAutoRefClock()
{
  return _autoRefClock;
};


void AD9851::setRefClockHigh()
{
  _config |= AD9851_REFCLK;
  setFrequency(_freq);
}


void AD9851::setRefClockLow()
{
  _config &= ~AD9851_REFCLK;
  setFrequency(_freq);
}


uint8_t AD9851::getRefClock()
{
  return (_config & AD9851_REFCLK) ? 180 : 30;
}


void AD9851::setARCCutOffFreq(uint32_t Hz)
{
  if (Hz > 30000000UL) Hz = 30000000;
  _ARCCutOffFreq = Hz;
};


uint32_t AD9851::getARCCutOffFreq()
{
  return _ARCCutOffFreq;
};


//  -- END OF FILE --

