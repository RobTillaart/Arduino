//
//    FILE: PCA9685.H
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.1.00
// PURPOSE: I2C PCA9685 library for Arduino
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries
//
// HISTORY:
// see PCA9685.cpp file
//

#ifndef _PCA9685_H
#define _PCA9685_H

#include "Arduino.h"

#define PCA9685_LIB_VERSION "0.1.00 BETA"

// check datasheet for details
#define PCA9685_MODE1       0x00
#define PCA9685_MODE2       0x01
//
#define PCA9685_PWMALL      0xFA


// NOT IMPLEMENTED
#define PCA9685_SUBADR(x)   (0x01+(x))  // x = 1..3
// NOT IMPLEMENTED
#define PCA9685_ALLCALLADR  0x05
// NOT IMPLEMENTED
#define PCA9685_PRE_SCALE   0xFE
// NOT IMPLEMENTED
#define PCA9685_TESTMODE    0xFF

// ERROR CODES
#define PCA9685_OK          0x00
#define PCA9685_ERROR       0xFF
#define PCA9685_ERR_CHANNEL 0xFE
#define PCA9685_ERR_MODE    0xFD


class PCA9685
{
public:
    explicit PCA9685(const uint8_t deviceAddress);

    // reg = 1, 2  check datasheet for values
    void writeMode(uint8_t reg, uint8_t value);
    uint8_t readMode(uint8_t reg);

    // single PWM setting, 0..15, 0..4095, 0..4095
    // allows shifted PWM's
    void setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime);
    void getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime);

    // single PWM setting, 0..15, 0..4095
    // onTime == 0, sets the OFF time
    void setPWM(uint8_t channel, uint16_t val);

    void setON(uint8_t channel);
    void setOFF(uint8_t channel);

    int lastError();

private:
    // DIRECT CONTROL
    void writeReg(uint8_t reg, uint8_t value);
    void writeReg2(uint8_t reg, uint16_t a, uint16_t b);
    uint8_t readReg(uint8_t reg);

    uint8_t _address;
    int     _error;
};

#endif
//
// END OF FILE
//