//
//    FILE: DAC8551.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: DAC8550 DAC8551 library for Arduino
// VERSION: 0.1.1
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8551
// HISTORY:
//   0.1.0: 2017-12-18 initial version
//   0.1.1: 2017-12-19 fix begin() bug
//
// Released to the public domain
//

#include <SPI.h>
#include <DAC8551.h>

#define MAXVALUE    0xFFFF

DAC8551::DAC8551()
{
  _hwSPI = true;
}

DAC8551::DAC8551(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI = false;      
  _spiData = spiData;
  _spiClock = spiClock;
  _slaveSelect = slaveSelect;
}

// initializes the SPI
// and sets internal state
void DAC8551::begin()
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
  }

  _register = 0;
  _value = 0;
}

// value = 0..65535
void DAC8551::setValue(uint16_t value)
{
  _value = value;
  updateDevice();
}

// returns 0..65535
uint16_t DAC8551::getValue()
{
  return _value;
}

void DAC8551::setPowerDown(uint8_t powerDownMode)
{
  _register = powerDownMode;
  updateDevice();
}

uint8_t DAC8551::getPowerDownMode()
{
  return _register & 0x03;
}

void DAC8551::updateDevice()
{
  uint8_t configRegister = _register;

  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_slaveSelect, LOW);
    SPI.transfer(configRegister);
    SPI.transfer(_value >> 8);
    SPI.transfer(_value & 0xFF);
    digitalWrite(_slaveSelect, LOW);
    SPI.endTransaction();
  }
  else // Software SPI 
  {
    digitalWrite(_slaveSelect, LOW);
    swSPI_transfer(configRegister);
    swSPI_transfer(_value >> 8);
    swSPI_transfer(_value & 0xFF);
    digitalWrite(_slaveSelect, LOW);
  }
}

// simple one mode version
void DAC8551::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_spiData,(value & mask) != 0);
    digitalWrite(_spiClock, HIGH);
    digitalWrite(_spiClock, LOW);
  }
}

// END OF FILE