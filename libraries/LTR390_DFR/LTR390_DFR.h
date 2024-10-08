#pragma once
//
//    FILE: LTR390_DFR.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-29
// VERSION: 0.1.1
// PURPOSE: Arduino library for the I2C LTR390 UV sensor (DF Robotics edition).
//     URL: https://github.com/RobTillaart/LTR390_DFR


#include "Arduino.h"
#include "Wire.h"


#define LTR390_DFR_LIB_VERSION         (F("0.1.1"))

//  LTR390 ERROR CODES
#define LTR390_OK                       0x00


//  DF_ROBOTICS LTR390 REGISTERS (16 bits)
#define LTR390_PID                      0x00
#define LTR390_ADDRESS                  0x02
#define LTR390_FIRMWARE                 0x05
#define LTR390_PART_ID                  0x06

#define LTR390_ALS_DATA_0               0x07
#define LTR390_ALS_DATA_1               0x08
#define LTR390_UVS_DATA_0               0x09
#define LTR390_UVS_DATA_1               0x0A

#define LTR390_GAIN                     0x0B
#define LTR390_INT_CONFIG               0x0C

#define LTR390_ALS_UVS_THRES_UP_0       0x0D
#define LTR390_ALS_UVS_THRES_UP_1       0x0E
#define LTR390_ALS_UVS_THRES_LOW_0      0x0F
#define LTR390_ALS_UVS_THRES_LOW_1      0x10
#define LTR390_ALS_UVS_THRES_VAR_DATA   0x11

#define LTR390_ALS_UVS_MEAS_RATE        0x12
#define LTR390_MAIN_CTRL                0x13


class LTR390_DFR
{
public:
  LTR390_DFR(TwoWire *wire = &Wire)
  {
    _address = 0x1C;  //  Fixed 0x1C = 28 = DF_ROBOTICS
    _wire = wire;
    _gain = 3.0;  //  default
    _time = 0.1;  //  default 18 bit, 100 ms.
    _UVsensitivity = 1.0;
  }

  bool begin()
  {
    return isConnected();
  }

  bool isConnected()
  {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
  }

  uint8_t getAddress()
  {
    return _address;
  }


  //////////////////////////////////////////////
  //
  //  MAIN CONTROL
  //
  void setALSMode()
  {
    uint8_t raw = readRegister(LTR390_MAIN_CTRL);
    raw &= ~0x08;
    writeRegister(LTR390_MAIN_CTRL, raw);
  }

  void setUVSMode()
  {
    uint8_t raw = readRegister(LTR390_MAIN_CTRL);
    raw |= 0x08;
    writeRegister(LTR390_MAIN_CTRL, raw);
  }

  uint8_t reset()
  {
    writeRegister(LTR390_MAIN_CTRL, 0x10);
    delay(100);
    return readRegister(LTR390_MAIN_CTRL);
  }


  //////////////////////////////////////////////
  //
  //  PART_ID
  //
  uint8_t getPartID()
  {
    uint8_t reg = readRegister(LTR390_PART_ID);
    return reg >> 4;
  }

  uint8_t getRevisionID()
  {
    uint8_t reg = readRegister(LTR390_PART_ID);
    return reg & 0x0F;
  }


  //////////////////////////////////////////////
  //
  //  GET DATA
  //
  uint32_t getALSData()
  {
    uint32_t raw = readRegister(LTR390_ALS_DATA_1) * 65536UL;
    raw += readRegister(LTR390_ALS_DATA_0);
    return raw;
  }

  //  page 22 datasheet
  float getLux(float wfac = 1)
  {
    float lux = 0.6 * getALSData() /( _gain * _time);
    if (wfac > 1) lux *= wfac;
    return lux;
  }

  uint32_t getUVSData()
  {
    uint32_t raw = readRegister(LTR390_UVS_DATA_1) * 65536UL;
    raw += readRegister(LTR390_UVS_DATA_0);
    return raw;
  }

  //  page 22 datasheet
  float getUVI(float wfac = 1)
  {
    float uvi = getUVSData() / _UVsensitivity;
    if (wfac > 1) uvi *= wfac;
    return uvi;
  }


  //////////////////////////////////////////////
  //
  //  MEASUREMENT CONFIGURATION
  //
  uint8_t setGain(uint8_t gain = 1)  //  0..4
  {
    uint16_t value = gain;
    if (value > 4) value = 4;
    writeRegister(LTR390_GAIN, value);
    _gain = 1;
    if      (value == 1) _gain = 3;
    else if (value == 2) _gain = 6;
    else if (value == 3) _gain = 9;
    else if (value == 4) _gain = 18;
    return value;
  }

  uint8_t getGain()
  {
    uint16_t reg = readRegister(LTR390_GAIN);
    return reg & 0x07;
  }

  //  resolution = 0..5  See datasheet P14.
  //        time = 0..7  See datasheet P14.
  bool setMeasurement(uint8_t resolution, uint8_t time)
  {
    if (resolution > 5) return false;
    if (time > 7 ) return false;

    uint16_t value = (resolution << 4) | time;
    writeRegister(LTR390_ALS_UVS_MEAS_RATE, value);

    _time = 2.000;  // time = 6 0r 7
    if (time == 0) _time = 0.025;
    if (time == 1) _time = 0.050;
    if (time == 2) _time = 0.100;
    if (time == 3) _time = 0.200;
    if (time == 4) _time = 0.500;
    if (time == 5) _time = 1.000;
    return true;
  }

  uint8_t getResolution()
  {
    uint16_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    return (reg >> 4) & 0x07;
  }

  uint8_t getTime()
  {
    uint16_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    return reg & 0x07;
  }

  bool setUVsensitivity(float s)
  {
    if ((s <= 0.0) || (s > 1.0))return false;
    _UVsensitivity = s;
    return true;
  }

  float getUVsensitivity()
  {
    return _UVsensitivity;
  }


//
//  Code below this line is not tested yet.
//  Use carefully, feel free to experiment.
//  Please let me know if it works or not.
//

/*
  void enable()
  {
    uint8_t raw = readRegister(LTR390_MAIN_CTRL);
    raw != 0x02;
    writeRegister(LTR390_MAIN_CTRL, raw);
  }

  void disable()
  {
    uint8_t raw = readRegister(LTR390_MAIN_CTRL);
    raw &= ~0x02;
    writeRegister(LTR390_MAIN_CTRL, raw);
  }
*/


/*
  //////////////////////////////////////////////
  //
  //  MAIN STATUS
  //
  uint8_t getStatus()
  {
    uint8_t reg = readRegister(LTR390_MAIN_STATUS);  ? no such register.
    return reg & 0x38;
  }


  //////////////////////////////////////////////
  //
  //  INTERRUPT
  //
  int setInterruptConfig(uint8_t value = 0x10)
  {
    return writeRegister(LTR390_INT_CFG, value);
  }

  uint8_t getInterruptConfig()
  {
    return readRegister(LTR390_INT_CFG);
  }

  int setInterruptPersist(uint8_t value = 0x00)
  {
    return writeRegister(LTR390_INT_PST, value);
  }

  uint8_t getInterruptPersist()
  {
    return readRegister(LTR390_INT_PST);
  }


  //////////////////////////////////////////////
  //
  //  THRESHOLD
  //
  //  note registers are 16 bit.
  //
  void setHighThreshold(uint32_t value = 0x000FFFFF)
  {
    writeRegister(LTR390_ALS_UVS_THRES_UP_0, value & 0xFFFF);
    writeRegister(LTR390_ALS_UVS_THRES_UP_1, value >> 16);
  }

  uint32_t getHighThreshold()
  {
    uint32_t value = readRegister(LTR390_ALS_UVS_THRES_UP_1) << 16;
    value += readRegister(LTR390_ALS_UVS_THRES_UP_0);
    return value;
  }

  void setLowThreshold(uint32_t value = 0)
  {
    writeRegister(LTR390_ALS_UVS_THRES_LOW_0, value & 0xFFFF);
    writeRegister(LTR390_ALS_UVS_THRES_LOW_1, value >> 16);
  }

  uint32_t getLowThreshold()
  {
    uint32_t value = readRegister(LTR390_ALS_UVS_THRES_LOW_1) << 16;
    value += readRegister(LTR390_ALS_UVS_THRES_LOW_0);
    return value;
  }
*/

//  END OF PUBLIC PART


  //////////////////////////////////////////////
  //
  //  PRIVATE
  //
  int writeRegister(uint8_t reg, uint16_t value)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(value & 0xFF);
    _wire->write(value >> 8);
    int n = _wire->endTransmission();
    if (n != 0)
    {
      //  _error = LTR390_I2C_ERROR;
      //  Serial.print("write:\t");
      //  Serial.println(n);
    }
    return n;
  }


  uint16_t readRegister(uint8_t reg)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    int n = _wire->endTransmission();
    if (n != 0)
    {
      //  _error = LTR390_I2C_ERROR;
      //  Serial.print("read:\t");
      //  Serial.println(n);
      return n;
    }

    n = _wire->requestFrom(_address, (uint8_t)2);
    if (n != 2)
    {
      //  Serial.print("requestFrom: \t");
      //  Serial.print(n);
      return n;
    }
    uint16_t data = _wire->read();
    return data + _wire->read() * 256;
  }


private:
  TwoWire * _wire;
  uint8_t _address;

  //  for LUX math
  float   _gain;
  float   _time;
  float   _UVsensitivity;
};


//  -- END OF FILE --

