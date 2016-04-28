//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.1.04
// PURPOSE: I2C PCF8574 library for Arduino
//     URL:
//
// HISTORY:
// 0.1.07 2016-04-28 Septillion
//        added dataOut so a write() doesn't read first, 
//        possibly corrupting a input pin;
//        fixed shift comment, should read 1..7;
//        added begin() to be sure it's in a known state,
//        states could be different if uC is reset and the PCF8574 isn't;
//        added buttonRead() and buttonRead8() 
//        which only effect the ouput while reading
// 0.1.04 2015-05-09 removed ambiguity in read8()
// 0.1.03 2015-03-02 address int -> uint8_t
// 0.1.02 replaced ints with uint8_t to reduce footprint;
//        added default value for shiftLeft() and shiftRight()
//        renamed status() to lastError();
// 0.1.01 added value(); returns last read 8 bit value (cached);
//        value() does not always reflect the latest state of the pins!
// 0.1.00 initial version
//

#include "PCF8574.h"

#include <Wire.h>

PCF8574::PCF8574(uint8_t deviceAddress)
{
    _address = deviceAddress;
    Wire.begin();
    // TWBR = 12; // 400KHz
}

//added 0.1.07
void PCF8574::begin()
{
  PCF8574::write8(0xFF);
}

// removed Wire.beginTransmission(addr);
// with  @100KHz -> 265 micros()
// without @100KHz -> 132 micros()
// without @400KHz -> 52 micros()
// TODO @800KHz -> ??
uint8_t PCF8574::read8()
{
    if (Wire.requestFrom(_address, (uint8_t)1) != 1)
    {
        _error = 10;
        return _data; // last value
    }
#if (ARDUINO <  100)
    _data = Wire.receive();
#else
    _data = Wire.read();
#endif
    return _data;
}

uint8_t PCF8574::value()
{
    return _data;
}

//added 0.1.07
uint8_t PCF8574::valueOut ()
{
    return _dataOut;
}

void PCF8574::write8(uint8_t value)
{
    _dataOut = value;
    Wire.beginTransmission(_address);
    Wire.write(_dataOut);
    _error = Wire.endTransmission();
}

// pin should be 0..7
uint8_t PCF8574::read(uint8_t pin)
{
    PCF8574::read8();
    return (_data & (1<<pin)) > 0;
}

// pin should be 0..7
void PCF8574::write(uint8_t pin, uint8_t value)
{
    //Don't read because we could bring pulled low inputs into output state
    //PCF8574::read8();
    if (value == LOW)
    {
        _dataOut &= ~(1<<pin);
    }
    else
    {
        _dataOut |= (1<<pin);
    }
    PCF8574::write8(_dataOut);
}

//added 0.1.07
uint8_t PCF8574::readButton8()
{
  uint8_t temp = _dataOut;
  PCF8574::begin();
  uint8_t rtn = PCF8574::read8();
  PCF8574::write8(temp);
  
  return rtn;
}

//added 0.1.07
uint8_t PCF8574::readButton(uint8_t pin)
{
  uint8_t temp = _dataOut;
  PCF8574::write(pin, HIGH);
  uint8_t rtn = PCF8574::read(pin);
  PCF8574::write8(temp);
  
  return rtn;
}

// pin should be 0..7
void PCF8574::toggle(uint8_t pin)
{   
    //Same as write
    //Don't read because that may upset pulled low inputs
    //PCF8574::read8();
    _dataOut ^=  (1 << pin);
    PCF8574::write8(_dataOut);
}

// n should be 1..7
void PCF8574::shiftRight(uint8_t n)
{
    if (n == 0 || n > 7 ) return;
    //PCF8574::read8();
    _dataOut >>= n;
    PCF8574::write8(_dataOut);
}

// n should be 1..7
void PCF8574::shiftLeft(uint8_t n)
{
    if (n == 0 || n > 7) return;
    //PCF8574::read8();
    _dataOut <<= n;
    PCF8574::write8(_dataOut);
}

int PCF8574::lastError()
{
    int e = _error;
    _error = 0;
    return e;
}
//
// END OF FILE
//