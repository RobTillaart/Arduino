#pragma once
//
//    FILE: LTR390_DFR.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2026-04-01
// PURPOSE: Arduino library for the I2C LTR390 UV sensor (DF Robotics edition).
//     URL: https://github.com/RobTillaart/LTR390_DFR


#include <Arduino.h>
#include <Wire.h>

#define LTR390_DFR_LIB_VERSION (F("0.2.0"))


//  LTR390 ERROR CODES
constexpr int LTR390_OK = 0;
constexpr int LTR390_I2C_REQUEST = -10;


//  DF_ROBOTICS LTR390 REGISTERS (16 bits)
namespace LTR390Reg
{
  constexpr uint8_t PID      = 0x00;
  constexpr uint8_t ADDRESS  = 0x02;
  constexpr uint8_t FIRMWARE = 0x05;
  constexpr uint8_t PART_ID  = 0x06;

  constexpr uint8_t ALS_DATA_0 = 0x07;
  constexpr uint8_t ALS_DATA_1 = 0x08;
  constexpr uint8_t UVS_DATA_0 = 0x09;
  constexpr uint8_t UVS_DATA_1 = 0x0A;

  constexpr uint8_t GAIN       = 0x0B;
  constexpr uint8_t INT_CONFIG = 0x0C;

  constexpr uint8_t ALS_UVS_THRES_UP_0   = 0x0D;
  constexpr uint8_t ALS_UVS_THRES_UP_1   = 0x0E;
  constexpr uint8_t ALS_UVS_THRES_LOW_0  = 0x0F;
  constexpr uint8_t ALS_UVS_THRES_LOW_1  = 0x10;
  constexpr uint8_t ALS_UVS_THRES_VAR_DATA = 0x11;

  constexpr uint8_t ALS_UVS_MEAS_RATE = 0x12;
  constexpr uint8_t MAIN_CTRL = 0x13;
}

class LTR390_DFR
{
public:
  explicit LTR390_DFR(TwoWire *wire = &Wire):
    _wire(wire),
    _address(0x1C),  //  0x1C == 28 ==> DF_ROBOTICS
    _gain(3.0f),     //  default
    _time(0.1f),     //  default 18 bit, 100 ms.
    _UVsensitivity(1.0f),
    _error(LTR390_OK) 
  {}

  [[nodiscard]] bool begin()
  {
    return isConnected();
  }

  [[nodiscard]] bool isConnected()
  {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
  }

  [[nodiscard]] uint8_t getAddress()
  {
    return _address;
  }

  //////////////////////////////////////////////
  //
  //  MAIN CONTROL
  //
  void setALSMode()
  {
    uint8_t raw = readRegister(LTR390Reg::MAIN_CTRL);
    raw &= ~0x08;
    (void)writeRegister(LTR390Reg::MAIN_CTRL, raw);
  }

  void setUVSMode()
  {
    uint8_t raw = readRegister(LTR390Reg::MAIN_CTRL);
    raw |= 0x08;
    (void)writeRegister(LTR390Reg::MAIN_CTRL, raw);
  }

  [[nodiscard]] uint8_t reset()
  {
    (void)writeRegister(LTR390Reg::MAIN_CTRL, 0x10);
    delay(100);
    return readRegister(LTR390Reg::MAIN_CTRL);
  }

  //////////////////////////////////////////////
  //
  //  PART_ID
  //
  [[nodiscard]] uint8_t getPartID()
  {
    uint8_t reg = readRegister(LTR390Reg::PART_ID);
    return reg >> 4;
  }

  [[nodiscard]] uint8_t getRevisionID()
  {
    uint8_t reg = readRegister(LTR390Reg::PART_ID);
    return reg & 0x0F;
  }

  //////////////////////////////////////////////
  //
  //  GET DATA
  //
  [[nodiscard]] uint32_t getALSData()
  {
    uint32_t raw = static_cast<uint32_t>(readRegister(LTR390Reg::ALS_DATA_1)) << 16;
    raw |= readRegister(LTR390Reg::ALS_DATA_0);
    return raw;
  }

  //  page 22 datasheet
  [[nodiscard]] float getLux(float wFactor = 1.0f)
  {
    float lux = 0.6f * getALSData() / (_gain * _time);
    if (wFactor > 1.0f)
      lux *= wFactor;
    return lux;
  }

  [[nodiscard]] uint32_t getUVSData()
  {
    uint32_t raw = readRegister(LTR390Reg::UVS_DATA_1) * 65536UL;
    raw += readRegister(LTR390Reg::UVS_DATA_0);
    return raw;
  }

  //  page 22 datasheet
  [[nodiscard]] float getUVI(float wfac = 1.0f)
  {
    float uvi = getUVSData() / _UVsensitivity;
    if (wfac > 1.0f)
      uvi *= wfac;
    return uvi;
  }

  //////////////////////////////////////////////
  //
  //  MEASUREMENT CONFIGURATION
  //
  [[nodiscard]] uint8_t setGain(uint8_t gain = 1)
  {
    constexpr uint8_t gainTable[] = {1, 3, 6, 9, 18};
    if (gain > 4)
      gain = 4;

    (void)writeRegister(LTR390Reg::GAIN, gain);
    _gain = gainTable[gain];
    return gain;
  }

  [[nodiscard]] uint8_t getGain()
  {
    uint16_t reg = readRegister(LTR390Reg::GAIN);
    return reg & 0x07;
  }

  //  resolution = 0..5  See datasheet P14.
  //        time = 0..7  See datasheet P14.
  [[nodiscard]] bool setMeasurement(uint8_t resolution, uint8_t time)
  {
    if (resolution > 5)
      return false;
    if (time > 7)
      return false;

    uint16_t value = (resolution << 4) | time;
    (void)writeRegister(LTR390Reg::ALS_UVS_MEAS_RATE, value);

    constexpr float timeTable[] = {
      0.025f, 0.05f, 0.1f, 0.2f, 0.5f, 1.0f, 2.0f, 2.0f
      };
    _time = timeTable[time];
    return true;
  }

  [[nodiscard]] uint8_t getResolution()
  {
    uint16_t reg = readRegister(LTR390Reg::ALS_UVS_MEAS_RATE);
    return (reg >> 4) & 0x07;
  }

  [[nodiscard]] uint8_t getTime()
  {
    uint16_t reg = readRegister(LTR390Reg::ALS_UVS_MEAS_RATE);
    return reg & 0x07;
  }

  [[nodiscard]] bool setUVsensitivity(float sensitivity = 1.0f)
  {
    if ((sensitivity <= 0.0f) || (sensitivity > 1.0f))
      return false;
    _UVsensitivity = sensitivity;
    return true;
  }

  [[nodiscard]] float getUVsensitivity()
  {
    return _UVsensitivity;
  }


  //////////////////////////////////////////////
  //
  //  WARNING: VERY EXPERIMENTAL
  //
  //  Code below this line is not tested yet.
  //  Use carefully, feel free to experiment.
  //  Please let me know if it works or not.
  //
  //////////////////////////////////////////////
  //
  //  ENABLE
  //
  void enable()
  {
    uint8_t raw = readRegister(LTR390Reg::MAIN_CTRL);
    raw |=0x02;
    (void) writeRegister(LTR390Reg::MAIN_CTRL, raw);
  }

  void disable()
  {
    uint8_t raw = readRegister(LTR390Reg::MAIN_CTRL);
    raw &= ~0x02;
    (void) writeRegister(LTR390Reg::MAIN_CTRL, raw);
  }

  [[nodiscard]] bool isEnabled()
  {
    uint8_t raw = readRegister(LTR390Reg::MAIN_CTRL);
    return (raw & 0x02) == 0x02;
  }

  //////////////////////////////////////////////
  //
  //  INTERRUPT
  //
  [[nodiscard]] int setInterruptConfig(uint8_t value = 0x10)
  {
    return writeRegister(LTR390Reg::INT_CONFIG, value);
  }

  [[nodiscard]] uint8_t getInterruptConfig()
  {
    return readRegister(LTR390Reg::INT_CONFIG);
  }


  //////////////////////////////////////////////
  //
  //  THRESHOLD
  //
  void setHighThreshold(uint32_t value = 0x000FFFFF)
  {
    (void) writeRegister(LTR390Reg::ALS_UVS_THRES_UP_0, value & 0xFFFF);
    (void) writeRegister(LTR390Reg::ALS_UVS_THRES_UP_1, value >> 16);
  }

  [[nodiscard]] uint32_t getHighThreshold()
  {
    uint32_t value = readRegister(LTR390Reg::ALS_UVS_THRES_UP_1);
    value <<= 16;
    value |= readRegister(LTR390Reg::ALS_UVS_THRES_UP_0);
    return value;
  }

  void setLowThreshold(uint32_t value = 0)
  {
    (void) writeRegister(LTR390Reg::ALS_UVS_THRES_LOW_0, value & 0xFFFF);
    (void) writeRegister(LTR390Reg::ALS_UVS_THRES_LOW_1, value >> 16);
  }

  [[nodiscard]] uint32_t getLowThreshold()
  {
    uint32_t value = readRegister(LTR390Reg::ALS_UVS_THRES_LOW_1);
    value <<= 16;
    value |= readRegister(LTR390Reg::ALS_UVS_THRES_LOW_0);
    return value;
  }


  //////////////////////////////////////////////
  //
  //  THRESHOLD
  //
  [[nodiscard]] int lastError()
  {
    int e = _error;
    _error = LTR390_OK;
    return e;
  }


  //  END OF PUBLIC PART


  //////////////////////////////////////////////
  //
  //  PRIVATE
  //
  [[nodiscard]] int writeRegister(uint8_t reg, uint16_t value)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(value & 0xFF);
    _wire->write(value >> 8);
    _error = _wire->endTransmission();
    if (_error != 0)
    {
      //  Serial.print("writeRegister:\t");
      //  Serial.println(_error);
    }
    return _error;
  }

  [[nodiscard]] uint16_t readRegister(uint8_t reg)
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _error = _wire->endTransmission();
    if (_error != 0)
    {
      //  Serial.print("readRegister:\t");
      //  Serial.println(_error);
      return _error;
    }

    int n = _wire->requestFrom(_address, (uint8_t)2);
    if (n != 2)
    {
      //  Serial.print("requestFrom: \t");
      //  Serial.print(n);
      _error = LTR390_I2C_REQUEST;
      return n;
    }
    uint16_t data = _wire->read();
    return data + _wire->read() * 256;
  }

private:
  TwoWire *_wire;
  uint8_t _address;

  //  for LUX math
  float _gain;
  float _time;
  float _UVsensitivity;
  int   _error;
};

//  -- END OF FILE --
