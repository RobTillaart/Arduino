//
//    FILE: PCF8574.H
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.1.08
// PURPOSE: I2C PCF8574 library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=184800
//
// HISTORY:
// see PCF8574.cpp file
//

#ifndef _PCF8574_H
#define _PCF8574_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PCF8574_LIB_VERSION "0.1.08"

#define PCF8574_OK          0x00
#define PCF8574_PIN_ERROR   0x81
#define PCF8574_I2C_ERROR   0x82


class PCF8574
{
public:
    explicit PCF8574(const uint8_t deviceAddress);

    void begin(uint8_t val=0xFF);

    uint8_t read8();
    uint8_t read(uint8_t pin);
    uint8_t value() const { return _dataIn; };

    void write8(const uint8_t value);
    void write(const uint8_t pin, const uint8_t value);
    uint8_t valueOut() const { return _dataOut; }

    //added 0.1.07/08 Septillion
    inline uint8_t readButton8(){ PCF8574::readButton8(_buttonMask);}
    uint8_t readButton8(const uint8_t mask=0xFF);
    uint8_t readButton(const uint8_t pin);
    void setButtonMask(uint8_t mask);

    // rotate, shift, toggle expect all lines are output
    void toggle(const uint8_t pin);
    void toggleMask(const uint8_t mask);    // invertAll() = toggleMask(0xFF)
    void shiftRight(const uint8_t n=1);
    void shiftLeft(const uint8_t n=1);
    void rotateRight(const uint8_t n=1);
    void rotateLeft(const uint8_t n=1);

    int lastError();

private:
    uint8_t _address;
    uint8_t _dataIn;
    uint8_t _dataOut;
    uint8_t _buttonMask;
    int _error;
};

#endif
//
// END OF FILE
//