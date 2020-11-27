//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.2.1
// PURPOSE: Arduino library for PCF8574 - I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8574
//          http://forum.arduino.cc/index.php?topic=184800
//
// HISTORY:
// 0.2.1  2020-06-19 fix library.json
// 0.2.0  2020-05-22 #pragma once; refactor;
//        removed pre 1.0 support
//        added begin(dsa, scl) for ESP32
//        added reverse()
//
// 0.1.9  2017-02-27 fix warning about return in readButton8()
// 0.1.08 2016-05-20 Merged work of Septillion 
//        Fix/refactor ButtonRead8() - see https://github.com/RobTillaart/Arduino/issues/38
//        missing begin() => mask parameter
// 0.1.07 2016-05-02 (manually merged) Septillion
//        added dataOut so a write() doesn't read first,
//        possibly corrupting a input pin;
//        fixed shift comment, should read 1..7;
//        added begin() to be sure it's in a known state,
//        states could be different if uC is reset and the PCF8574 isn't;
//        added buttonRead() and buttonRead8()
//        which only effect the output while reading
// 0.1.06 (intermediate) added defined errors + refactor rotate
// 0.1.05 2016-04-30 refactor, +toggleMask, +rotLeft, +rotRight
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


PCF8574::PCF8574(const uint8_t deviceAddress)
{
    _address = deviceAddress;
    _dataIn = 0;
    _dataOut = 0xFF;
    _buttonMask = 0xFF;
    _error = PCF8574_OK;
}

#if defined (ESP8266) || defined(ESP32)
void PCF8574::begin(uint8_t sda, uint8_t scl, uint8_t val)
{
  Wire.begin(sda, scl);
  PCF8574::write8(val);
}
#endif

void PCF8574::begin(uint8_t val)
{
  Wire.begin();
  PCF8574::write8(val);
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
        _error = PCF8574_I2C_ERROR;
        return _dataIn; // last value
    }
    _dataIn = Wire.read();
    return _dataIn;
}

void PCF8574::write8(const uint8_t value)
{
    _dataOut = value;
    Wire.beginTransmission(_address);
    Wire.write(_dataOut);
    _error = Wire.endTransmission();
}

uint8_t PCF8574::read(const uint8_t pin)
{
    if (pin > 7)
    {
        _error = PCF8574_PIN_ERROR;
        return 0;
    }
    PCF8574::read8();
    return (_dataIn & (1 << pin)) > 0;
}

void PCF8574::write(const uint8_t pin, const uint8_t value)
{
    if (pin > 7)
    {
        _error = PCF8574_PIN_ERROR;
        return;
    }
    if (value == LOW)
    {
        _dataOut &= ~(1 << pin);
    }
    else
    {
        _dataOut |= (1 << pin);
    }
    write8(_dataOut);
}

void PCF8574::toggle(const uint8_t pin)
{
    if (pin > 7)
    {
        _error = PCF8574_PIN_ERROR;
        return;
    }
    toggleMask(1 << pin);
}

void PCF8574::toggleMask(const uint8_t mask)
{
    _dataOut ^= mask;
    PCF8574::write8(_dataOut);
}

void PCF8574::shiftRight(const uint8_t n)
{
	if ((n == 0) || (_dataOut == 0)) return;
	if (n > 7)         _dataOut = 0;    // shift 8++ clears all, valid...
	if (_dataOut != 0) _dataOut >>= n;
    PCF8574::write8(_dataOut);
}

void PCF8574::shiftLeft(const uint8_t n)
{
	if ((n == 0) || (_dataOut == 0)) return;
	if (n > 7)         _dataOut = 0;    // shift 8++ clears all, valid...
	if (_dataOut != 0) _dataOut <<= n;  // only shift if there are bits set
    PCF8574::write8(_dataOut);
}

int PCF8574::lastError()
{
    int e = _error;
    _error = PCF8574_OK;
    return e;
}

void PCF8574::rotateRight(const uint8_t n)
{
	if ((n % 8) == 0) return;
    uint8_t r = n & 7;
    _dataOut = (_dataOut >> r) | (_dataOut << (8 - r));
    PCF8574::write8(_dataOut);
}

void PCF8574::rotateLeft(const uint8_t n)
{
    rotateRight(8- (n & 7));
}

void PCF8574::reverse() // quite fast: 14 shifts, 3 or, 3 assignment.
{
  uint8_t x = _dataOut;
  x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  PCF8574::write8(x);
}

//added 0.1.07/08 Septillion
uint8_t PCF8574::readButton8(const uint8_t mask)
{
    uint8_t temp = _dataOut;
    PCF8574::write8(mask | _dataOut); 
    PCF8574::read8();
    PCF8574::write8(temp);
    return _dataIn;
}

//added 0.1.07 Septillion
uint8_t PCF8574::readButton(const uint8_t pin)
{
    if (pin > 7)
    {
        _error = PCF8574_PIN_ERROR;
        return 0;
    }
    uint8_t temp = _dataOut;
    PCF8574::write(pin, HIGH);
    uint8_t rtn = PCF8574::read(pin);
    PCF8574::write8(temp);
    return rtn;
}

// -- END OF FILE --
