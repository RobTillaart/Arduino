//
//    FILE: DAC8552.cpp 
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor
// VERSION: 0.1.3
//     URL: https://github.com/RobTillaart/DAC8552
//
// HISTORY:
//   0.1.0: 2017-12-14 initial version
//   0.1.1: 2017-12-19 fix begin() bug
//   0.1.2  2020-04-06 minor refactor, readme.md
//   0.1.3  2020-06-07 fix library.json


#include <SPI.h>
#include <DAC8552.h>

#define MAXVOLTAGE  5.0
#define MAXVALUE    0xFFFF

DAC8552::DAC8552()
{
  _hwSPI = true;
}

DAC8552::DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI = false;
  _spiData = spiData;
  _spiClock = spiClock;
  _slaveSelect = slaveSelect;
}

// initializes the SPI
// and sets internal state
void DAC8552::begin()
{
  if(_hwSPI)
  {
    SPI.begin();
    delay(1);
  }
  else
  {
    pinMode(_spiData, OUTPUT);
    pinMode(_spiClock, OUTPUT);
    pinMode(_slaveSelect, OUTPUT);
    digitalWrite(_slaveSelect, HIGH);
    digitalWrite(_spiData, LOW);
    digitalWrite(_spiClock, LOW);
  }

  for (uint8_t i = 0; i < 2; i++)
  {
    _register[i] = 0;
    _value[i] = 0;
  }
}

// DAC = 0, 1, 2, 3 depending on type
// value = 0..65535
void DAC8552::bufferValue(uint8_t DAC, uint16_t value)
{
  _value[DAC] = value;
  updateDevice(DAC, false);
}

// DAC = 0, 1, 2, 3 depending on type
// value = 0..65535
void DAC8552::setValue(uint8_t DAC, uint16_t value)
{
  _value[DAC] = value;
  updateDevice(DAC, true);
}

// DAC = 0, 1, 2, 3 depending on type
// returns 0..65535
uint16_t DAC8552::getValue(uint8_t DAC)
{
  return _value[DAC];
}

void DAC8552::bufferPowerDown(uint8_t DAC, uint8_t powerDownMode)
{
  _register[DAC] &= 0xFC;
  _register[DAC] |= powerDownMode;
  updateDevice(DAC, false);
}

void DAC8552::setPowerDown(uint8_t DAC, uint8_t powerDownMode)
{
  _register[DAC] &= 0xFC;
  _register[DAC] |= powerDownMode;
  updateDevice(DAC, true);
}

uint8_t DAC8552::getPowerDownMode(uint8_t DAC)
{
  return _register[DAC] & 0x03;
}

// DAC = 0, 1, 2, 3 depending on type
// direct = true ==> write buffers to both DAC A and DAC B
// direct = false ==> buffer value
void DAC8552::updateDevice(uint8_t DAC, bool directWrite)
{
  uint8_t configRegister = _register[DAC];
  if (directWrite) configRegister |= 0x30;

  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_slaveSelect, LOW);
    SPI.transfer(configRegister);
    SPI.transfer(_value[DAC] >> 8);
    SPI.transfer(_value[DAC] & 0xFF);
    digitalWrite(_slaveSelect, HIGH);
    SPI.endTransaction();
  }
  else // Software SPI
  {
    digitalWrite(_slaveSelect, LOW);
    swSPI_transfer(configRegister);
    swSPI_transfer(_value[DAC] >> 8);
    swSPI_transfer(_value[DAC] & 0xFF);
    digitalWrite(_slaveSelect, HIGH);
  }
}

// simple one mode version
void DAC8552::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_spiData,(value & mask) != 0);
    digitalWrite(_spiClock, HIGH);
    digitalWrite(_spiClock, LOW);
  }
}

// -- END OF FILE --
