//
//    FILE: DAC8554.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: DAC8554 library for Arduino
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8554
// HISTORY:
//   0.1.0: 2017-12-19 initial version
//
// Released to the public domain
//

#include <SPI.h>
#include <DAC8554.h>

#define DAC8554_BUFFER_WRITE  0x00
#define DAC8554_SINGLE_WRITE  0x10
#define DAC8554_ALL_WRITE     0x20
#define DAC8554_BROADCAST     0x30

DAC8554::DAC8554(uint8_t address)
{
  _hwSPI = true;
  _address = (address & 0x03) << 6;
}

// 0,1,2,4 resp 8550 8551 8552 8554
DAC8554::DAC8554(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect, uint8_t address)
{
  _hwSPI = false;
  _spiData = spiData;
  _spiClock = spiClock;
  _slaveSelect = slaveSelect;
  _address = (address & 0x03) << 6;
}

// initializes the SPI
// and sets internal state
void DAC8554::begin()
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
}

//////////////////////////////////////////////////////////////////////
//
// SETVALUE
//
// DAC = 0,1,2,3
// value = 0..65535
void DAC8554::bufferValue(uint8_t DAC, uint16_t value)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_BUFFER_WRITE;
  configRegister |= (DAC << 1);
  writeDevice(configRegister, value);
}

void DAC8554::setValue(uint8_t DAC, uint16_t value)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_ALL_WRITE;
  configRegister |= (DAC << 1);
  writeDevice(configRegister, value);
}

void DAC8554::setSingleValue(uint8_t DAC, uint16_t value)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_SINGLE_WRITE;
  configRegister |= (DAC << 1);
  writeDevice(configRegister, value);
}

//////////////////////////////////////////////////////////////////////
//
// POWERDOWN
//
// DAC = 0,1,2,3
// powerDownMode =
// DAC8554_POWERDOWN_NORMAL   0x00
// DAC8554_POWERDOWN_1K       0x40
// DAC8554_POWERDOWN_100K     0x80
// DAC8554_POWERDOWN_HIGH_IMP 0xC0
void DAC8554::bufferPowerDown(uint8_t DAC, uint8_t powerDownMode)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_BUFFER_WRITE;
  configRegister |= (DAC << 1);
  uint16_t value = (powerDownMode & 0xC0) << 8;
  writeDevice(configRegister, value);
}

void DAC8554::setPowerDown(uint8_t DAC, uint8_t powerDownMode)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_ALL_WRITE;
  configRegister |= (DAC << 1);
  uint16_t value = (powerDownMode & 0xC0) << 8;
  writeDevice(configRegister, value);
}

void DAC8554::setSinglePowerDown(uint8_t DAC, uint8_t powerDownMode)
{
  uint8_t configRegister = _address;
  configRegister |= DAC8554_SINGLE_WRITE;
  configRegister |= (DAC << 1);
  uint16_t value = (powerDownMode & 0xC0) << 8;
  writeDevice(configRegister, value);
}

//////////////////////////////////////////////////////////////////////
//
// BROADCAST (addresses all 8554 on "SPI-bus")
//
void DAC8554::broadcastBuffer()
{
  uint8_t configRegister = DAC8554_BROADCAST;
  uint16_t value = 0;
  writeDevice(configRegister, value);
}

void DAC8554::broadcastValue(uint16_t value)
{
  uint8_t configRegister = DAC8554_BROADCAST;
  configRegister |= 0x04;  // TODO magic number
  writeDevice(configRegister, value);
}

void DAC8554::broadcastPowerDown(uint8_t powerDownMode)
{
  uint8_t configRegister = DAC8554_BROADCAST;
  configRegister |= 0x05;  // TODO magic number
  uint16_t value = (powerDownMode & 0xC0) << 8;
  writeDevice(configRegister, value);
}


void DAC8554::writeDevice(uint8_t configRegister, uint16_t value)
{
  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_slaveSelect, LOW);
    SPI.transfer(configRegister);
    SPI.transfer(value >> 8);
    SPI.transfer(value & 0xFF);
    digitalWrite(_slaveSelect, LOW);
    SPI.endTransaction();
  }
  else // Software SPI
  {
    digitalWrite(_slaveSelect, LOW);
    swSPI_transfer(configRegister);
    swSPI_transfer(value >> 8);
    swSPI_transfer(value & 0xFF);
    digitalWrite(_slaveSelect, LOW);
  }
}

// simple one mode version
void DAC8554::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_spiData,(value & mask) != 0);
    digitalWrite(_spiClock, HIGH);
    digitalWrite(_spiClock, LOW);
  }
}

// END OF FILE