//
//    FILE: PCA9635.H
//  AUTHOR: Rob Tillaart
//    DATE: 23-apr-2016
// VERSION: 0.1.2
// PURPOSE: I2C PCA9635 library for Arduino
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries
//
// HISTORY:
// see PCA9635.cpp file
//

#ifndef _PCA9635_H
#define _PCA9635_H

#include "Arduino.h"

#define PCA9635_LIB_VERSION "0.1.00 BETA"

#define PCA9635_MODE1       0x00
#define PCA9635_MODE2       0x01
#define PCA9635_PWM(x)      (0x02+(x))

#define PCA9635_GRPPWM      0x12
#define PCA9635_GRPFREQ     0x13

// check datasheet for details
#define PCA9635_LEDOUT_BASE 0x14    // 0x14..0x17
#define PCA9635_LEDOFF      0x00    // default @ startup
#define PCA9635_LEDON       0x01
#define PCA9635_LEDPWM      0x02
#define PCA9635_LEDGRPPWM   0x03

#define PCA9635_OK          0x00
#define PCA9635_ERROR       0xFF

// NOT IMPLEMENTED YET
#define PCA9635_SUBADR(x)   (0x17+(x))  // x = 1..3
#define PCA9635_ALLCALLADR  0x1B

class PCA9635
{
public:
    explicit PCA9635(const uint8_t deviceAddress);

    void setLedDriverMode(uint8_t channel, uint8_t mode);
    uint8_t getLedDriverMode(uint8_t channel);

    // single PWM setting
    void write1(uint8_t channel, uint8_t value);
    // RGB setting
    void write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B);
    // generic workhorse
    void writeN(uint8_t channel, uint8_t* arr, uint8_t count);

    // reg = 1, 2  check datasheet for values
    void writeMode(uint8_t reg, uint8_t value);
    uint8_t readMode(uint8_t reg);

    // TODO PWM also in %% ?
    void setGroupPWM(uint8_t value) { writeReg(PCA9635_GRPPWM, value); }
    uint8_t getGroupPWM() { return readReg(PCA9635_GRPPWM); }

    // TODO set time in millisec and round to nearest value?
    void setGroupFREQ(uint8_t value) { writeReg(PCA9635_GRPFREQ, value); }
    uint8_t getGroupFREQ() { return readReg(PCA9635_GRPFREQ); }

    int lastError();

private:
    // DIRECT CONTROL
    void writeReg(uint8_t reg, uint8_t value);
    uint8_t readReg(uint8_t reg);

    uint8_t _address;
    uint8_t _register;
    uint8_t _data;
    int     _error;
};

#endif
//
// END OF FILE
//