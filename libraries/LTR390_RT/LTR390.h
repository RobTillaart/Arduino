#pragma once
//
//    FILE: LTR390.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-29
// VERSION: 0.1.1
// PURPOSE: Arduino library for the I2C LTR390 UV sensor.
//     URL: https://github.com/RobTillaart/LTR390_RT


#include "Arduino.h"
#include "Wire.h"


#define LTR390_LIB_VERSION         (F("0.1.1"))

//  LTR390 ERROR CODES
//  TODO


//  LTR390 REGISTERS (page 13 datasheet)
#define LTR390_MAIN_CTRL              0x00
#define LTR390_ALS_UVS_MEAS_RATE      0x04
#define LTR390_ALS_UVS_GAIN           0x05
#define LTR390_PART_ID                0x06
#define LTR390_MAIN_STATUS            0x07

#define LTR390_ALS_DATA_0             0x0D
#define LTR390_ALS_DATA_1             0x0E
#define LTR390_ALS_DATA_2             0x0F

#define LTR390_UVS_DATA_0             0x10
#define LTR390_UVS_DATA_1             0x11
#define LTR390_UVS_DATA_2             0x12

#define LTR390_INT_CFG                0x19
#define LTR390_INT_PST                0x1A

#define LTR390_ALS_UVS_THRES_UP_0     0x21
#define LTR390_ALS_UVS_THRES_UP_1     0x22
#define LTR390_ALS_UVS_THRES_UP_2     0x23
#define LTR390_ALS_UVS_THRES_LOW_0    0x24
#define LTR390_ALS_UVS_THRES_LOW_1    0x25
#define LTR390_ALS_UVS_THRES_LOW_2    0x26


class LTR390
{
public:
  LTR390(TwoWire *wire = &Wire)
  {
    _address = 0x53;  //  LTR390 device itself
    _wire = wire;
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
    writeRegister(LTR390_MAIN_CTRL, 0x02);
  }

  void setUVSMode()
  {
    writeRegister(LTR390_MAIN_CTRL, 0x0A);
  }

  uint8_t reset()
  {
    writeRegister(LTR390_MAIN_CTRL, 0x10);
    delay(100);
    return readRegister(LTR390_MAIN_CTRL);
  }

  void enable()
  {
    uint8_t reg = readRegister(LTR390_MAIN_CTRL);
    reg |= 0x02;
    writeRegister(LTR390_MAIN_CTRL, reg);
  }

  void disable()
  {
    uint8_t reg = readRegister(LTR390_MAIN_CTRL);
    reg &= ~0x02;
    writeRegister(LTR390_MAIN_CTRL, reg);
  }

  bool isEnabled()
  {
    uint8_t reg = readRegister(LTR390_MAIN_CTRL);
    return (reg & 0x02) > 0;
  }


  //////////////////////////////////////////////
  //
  //  MEASUREMENT CONFIGURATION
  //
  void setResolution(uint8_t resolution)  //  res = 0..5
  {
    if (resolution > 5) resolution = 5;
    uint8_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    reg &= 0x07;
    reg |= (resolution << 4);
    writeRegister(LTR390_ALS_UVS_MEAS_RATE, reg);
  }

  uint8_t getResolution()
  {
    uint8_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    return (reg >> 4) & 0x07;
  }


  void setRate(uint8_t rate)  //  rate = 0..7
  {
    uint8_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    reg &= 0xF8;
    reg |= rate;
    writeRegister(LTR390_ALS_UVS_MEAS_RATE, reg);
  }

  uint8_t getRate()
  {
    uint8_t reg = readRegister(LTR390_ALS_UVS_MEAS_RATE);
    return reg & 0x07;
  }


  void setGain(uint8_t gain)  //  gain = 0..4
  {
    if (gain > 4) gain = 4;
    uint8_t reg = readRegister(LTR390_ALS_UVS_GAIN);
    reg &= 0xF8;
    reg |= gain;
    writeRegister(LTR390_ALS_UVS_GAIN, reg);
  }

  uint8_t getGain()
  {
    uint8_t reg = readRegister(LTR390_ALS_UVS_GAIN);
    return reg & 0x07;
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
  //  MAIN STATUS
  //  TODO elaborate - need split? or masks?
  //
  uint8_t getStatus()
  {
    uint8_t reg = readRegister(LTR390_MAIN_STATUS);
    return reg & 0x38;
  }


  //////////////////////////////////////////////
  //
  //  GET DATA
  //
  uint32_t getALSData()
  {
    uint32_t value = readRegister(LTR390_ALS_DATA_2) & 0x0F;
    value <<= 8;
    value += readRegister(LTR390_ALS_DATA_1);
    value <<= 8;
    value += readRegister(LTR390_ALS_DATA_0);
    return value;
  }

  uint32_t getUVSData()
  {
    uint32_t value = readRegister(LTR390_UVS_DATA_2) & 0x0F;
    value <<= 8;
    value += readRegister(LTR390_UVS_DATA_1);
    value <<= 8;
    value += readRegister(LTR390_UVS_DATA_0);
    return value;
  }


  //////////////////////////////////////////////
  //
  //  INTERRUPT
  //  TODO elaborate
  //
  int setInterruptConfig(uint8_t value)
  {
    return writeRegister(LTR390_INT_CFG, value);
  }

  uint8_t getInterruptConfig()
  {
    return readRegister(LTR390_INT_CFG);
  }

  int setInterruptPersist(uint8_t value)
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
  //  TODO elaborate
  //
  void setHighThreshold(uint32_t value)
  {
    writeRegister(LTR390_ALS_UVS_THRES_UP_0, value & 0xFF);
    value >>= 8;
    writeRegister(LTR390_ALS_UVS_THRES_UP_1, value & 0xFF);
    value >>= 8;
    writeRegister(LTR390_ALS_UVS_THRES_UP_2, value & 0x0F);
  }


  uint32_t getHighThreshold()
  {
    uint32_t value = readRegister(LTR390_ALS_UVS_THRES_UP_2) & 0x0F;
    value <<= 8;
    value += readRegister(LTR390_ALS_UVS_THRES_UP_1);
    value <<= 8;
    value += readRegister(LTR390_ALS_UVS_THRES_UP_0);
    return value;
  }


  void setLowThreshold(uint32_t value)
  {
    writeRegister(LTR390_ALS_UVS_THRES_LOW_0, value & 0xFF);
    value >>= 8;
    writeRegister(LTR390_ALS_UVS_THRES_LOW_1, value & 0xFF);
    value >>= 8;
    writeRegister(LTR390_ALS_UVS_THRES_LOW_2, value & 0x0F);
  }


  uint32_t getLowThreshold()
  {
    uint32_t value = readRegister(LTR390_ALS_UVS_THRES_LOW_2) & 0x0F;
    value <<= 8;
    value += readRegister(LTR390_ALS_UVS_THRES_LOW_1);
    value <<= 8;
    value += readRegister(LTR390_ALS_UVS_THRES_LOW_0);
    return value;
  }


//////////////////////////////////////////////
//
//  PRIVATE
//
  int writeRegister(uint8_t reg, uint8_t value)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(value);
    int n = _wire->endTransmission();
    //if (n != 0)
    //{
    //  Serial.print("write:\t");
    //  Serial.println(n);
    //}
    return n;
  }


  uint8_t readRegister(uint8_t reg)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    int n = _wire->endTransmission();
    //if (n != 0)
    //{
    //  Serial.print("read:\t");
    //  Serial.println(n);
    //  return n;
    //}

    n = _wire->requestFrom(_address, (uint8_t)1);
    if (n != 1)
    {
    //  Serial.print("requestFrom: \t");
    //  Serial.print(n);
    //  return n;
    }
    return _wire->read();
  }


private:
  TwoWire * _wire;
  uint8_t _address;

};


//  -- END OF FILE --

