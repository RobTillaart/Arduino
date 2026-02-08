//
//    FILE: DAC8562.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8562 SPI 16 bit dual channel DAC.
// VERSION: 0.1.0
//    DATE: 2025-01-29
//     URL: https://github.com/RobTillaart/DAC8562


#include "DAC8562.h"


//  select line == SYNC in datasheet.
DAC8562::DAC8562(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
{
  _select  = select;
  _dataOut = 255;
  _clock   = 255;
  _LDAC    = LDAC;
  _CLR     = CLR;
  _mySPI   = spi;
  _hwSPI   = true;
  _bits    = 16;
  _maxValue = 65535;
  _midPoint = false;
}


DAC8562::DAC8562(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
{
  _select  = select;
  _dataOut = spiData;
  _clock   = spiClock;
  _LDAC    = LDAC;
  _CLR     = CLR;
  _mySPI   = NULL;
  _hwSPI   = false;
  _bits    = 16;
  _maxValue = 65535;
  _midPoint = false;
}


//  initializes the SPI
//  and sets internal state of pins etc.
void DAC8562::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  if (255 != _LDAC)
  {
    pinMode(_LDAC, OUTPUT);
    digitalWrite(_LDAC, HIGH);
  }
  if (255 != _CLR)
  {
    pinMode(_CLR, OUTPUT);
    digitalWrite(_CLR, HIGH);
  }

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }

  _register = 0;
  //  power on value
  _value[0] = _midPoint ? 1L << (_bits - 1) : 0;
  _value[1] = _midPoint ? 1L << (_bits - 1) : 0;
}


/////////////////////////////////////////////////////////////////////
//
//  Datasheet page 36+37+38
//  The DAC756x, DAC816x, or DAC856x input shift register is 24 bits wide, consisting of
//  two don’t care bits (DB23 to DB22),
//  three command bits (DB21 to DB19),
//  three address bits (DB18 to DB16),
//  and 16 data bits (DB15 to DB0).

//  set both channels.
//  value = 0..maxValue
void DAC8562::setValue(uint16_t value)
{
  //  DATASHEET 8.5 page 36
  if (value > _maxValue) value = _maxValue;
  _value[0] = _value[1] = value;
  //  Table 12/13 page 37
  //  Write to input register and update DAC register
  uint32_t data = 0x03 << 3;
  data += 0x07;  //  DAC A + B
  data <<= 16;
  data += (value << (16 - _bits));
  updateDevice(data);
}

//  channel = 0, 1
//  value   = 0..maxValue
void DAC8562::setValue(uint8_t channel, uint16_t value)
{
  //  DATASHEET 8.5 page 37+38
  if (channel > 1) return;
  if (value > _maxValue) value = _maxValue;
  _value[channel] = value;
  //  Table 12/13 page 37+38
  //  0x03 = command Write to input register n and update DAC register
  uint32_t data = 0x03 << 3;
  data += channel;  //  Only one DAC
  data <<= 16;
  data += (value << (16 - _bits));
  updateDevice(data);
}

//  channel = 0, 1
//  returns 0..maxValue from cache!
uint16_t DAC8562::getValue(uint8_t channel)
{
  if (channel > 1) return 0;  //  workaround
  return _value[channel];
}

uint16_t DAC8562::getMaxValue()
{
  return _maxValue;
}


/////////////////////////////////////////////////////////////////////
//
//  Datasheet page 36+37+38
//
//  powerDownMode = 0..3
void DAC8562::setPowerDownMode(uint8_t powerDownMode)
{
  if (powerDownMode > 3) return;
  _register &= 0xFC;   //  clear 2 bits
  _register |= powerDownMode;
  //  0x04 = command update power mode
  uint32_t data = 0x04 << 3;
  data <<= 16;
  data |= ((powerDownMode << 4) | 0x03);  //  both DAC's in first release
  updateDevice(data);
}

uint8_t DAC8562::getPowerDownMode()
{
  return _register & 0x03;
}

//
// Datasheet page 37+38, table 12 Enable/Disable Internal Reference
//
void DAC8562::enableInternalReference()
{
  //  0x07 = command Enable or disable the internal reference
  uint32_t data = 0x07 << 3;
  data <<= 16;
  data |= 0x01;  //  enable
  updateDevice(data);
}

void DAC8562::disableInternalReference()
{
  //  0x07 = command Enable or disable the internal reference
  uint32_t data = 0x07 << 3;
  data <<= 16;
  data |= 0x00;  //  disable
  updateDevice(data);
}


/////////////////////////////////////////////////////////////////////
//
//  SPI
//
void DAC8562::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

/*
The DAC756x, DAC816x, or DAC856x input shift register is 24 bits wide, consisting of two don’t care bits (DB23
to DB22), three command bits (DB21 to DB19), three address bits (DB18 to DB16), and 16 data bits (DB15 to
DB0). All 24 bits of data are loaded into the DAC under the control of the serial clock input, SCLK. DB23 (MSB)
is the first bit that is loaded into the DAC shift register. DB23 is followed by the rest of the 24-bit word pattern,
left-aligned. This configuration means that the first 24 bits of data are latched into the shift register, and any
further clocking of data is ignored.
*/

void DAC8562::updateDevice(uint32_t data, bool vref)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  MSB first
    _mySPI->transfer((data >> 16) & 0xFF);
    _mySPI->transfer((data >> 8) & 0xFF);
    _mySPI->transfer(data & 0xFF);
    //  datasheet 7.3.5 Enable/Disable Internal Reference, P21  TODO CHECK
    if (vref) _mySPI->transfer(0x00);  // force extra clock pulses
    _mySPI->endTransaction();
  }
  else //  Software SPI
  {
    //  MSB first
    swSPI_transfer((data >> 16) & 0xFF);
    swSPI_transfer((data >> 8) & 0xFF);
    swSPI_transfer(data & 0xFF);
    //  datasheet 7.3.5 Enable/Disable Internal Reference, P21  TODO CHECK
    if (vref) swSPI_transfer(0x00);  // force extra clock pulses
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void DAC8562::swSPI_transfer(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  DAC7562
//
DAC7562::DAC7562(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spi, LDAC, CLR)
{
  _bits = 12;
  _maxValue = 4095;
  _midPoint = false;
}

DAC7562::DAC7562(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spiData, spiClock, LDAC, CLR)
{
  _bits = 12;
  _maxValue = 4095;
  _midPoint = false;
}

//
//  DAC7563
//
DAC7563::DAC7563(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spi, LDAC, CLR)
{
  _bits = 12;
  _maxValue = 4095;
  _midPoint = true;
}

DAC7563::DAC7563(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spiData, spiClock, LDAC, CLR)
{
  _bits = 12;
  _maxValue = 4095;
  _midPoint = true;
}

//
//  DAC8162
//
DAC8162::DAC8162(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spi, LDAC, CLR)
{
  _bits = 14;
  _maxValue = 16383;
  _midPoint = false;
}

DAC8162::DAC8162(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spiData, spiClock, LDAC, CLR)
{
  _bits = 14;
  _maxValue = 16383;
  _midPoint = false;
}


//
//  DAC8163
//
DAC8163::DAC8163(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spi, LDAC, CLR)
{
  _bits = 14;
  _maxValue = 16383;
  _midPoint = true;
}

DAC8163::DAC8163(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spiData, spiClock, LDAC, CLR)
{
  _bits = 14;
  _maxValue = 16383;
  _midPoint = true;
}


//
//  DAC8563
//
DAC8563::DAC8563(uint8_t select, __SPI_CLASS__ * spi, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spi, LDAC, CLR)
{
  _bits = 16;
  _maxValue = 65535;
  _midPoint = true;
}

DAC8563::DAC8563(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC, uint8_t CLR)
        :DAC8562(select, spiData, spiClock, LDAC, CLR)
{
  _bits = 16;
  _maxValue = 65535;
  _midPoint = true;
}


//  -- END OF FILE --

