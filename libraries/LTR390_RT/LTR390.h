#pragma once
//
//    FILE: LTR390.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-29
// VERSION: 0.2.0
// PURPOSE: Arduino library for the I2C LTR390 UV sensor.
//     URL: https://github.com/RobTillaart/LTR390_RT

#include "Arduino.h"
#include "Wire.h"

#define LTR390_LIB_VERSION (F("0.2.0"))

//  LTR390 ERROR CODES
//  TODO

namespace LTR390RT
{
  //  LTR390 REGISTERS (page 13 datasheet)
  namespace REGISTER
  {
    constexpr uint8_t MAIN_CTRL          = 0x00;
    constexpr uint8_t ALS_UVS_MEAS_RATE  = 0x04;
    constexpr uint8_t ALS_UVS_GAIN       = 0x05;
    constexpr uint8_t PART_ID            = 0x06;
    constexpr uint8_t MAIN_STATUS        = 0x07;

    constexpr uint8_t ALS_DATA_0 = 0x0D;
    constexpr uint8_t ALS_DATA_1 = 0x0E;
    constexpr uint8_t ALS_DATA_2 = 0x0F;

    constexpr uint8_t UVS_DATA_0 = 0x10;
    constexpr uint8_t UVS_DATA_1 = 0x11;
    constexpr uint8_t UVS_DATA_2 = 0x12;

    constexpr uint8_t INT_CFG    = 0x19;
    constexpr uint8_t INT_PST    = 0x1A;

    constexpr uint8_t ALS_UVS_THRES_UP_0  = 0x21;
    constexpr uint8_t ALS_UVS_THRES_UP_1  = 0x22;
    constexpr uint8_t ALS_UVS_THRES_UP_2  = 0x23;

    constexpr uint8_t ALS_UVS_THRES_LOW_0 = 0x24;
    constexpr uint8_t ALS_UVS_THRES_LOW_1 = 0x25;
    constexpr uint8_t ALS_UVS_THRES_LOW_2 = 0x26;
  }

  namespace MAIN_CTRL
  {
    constexpr uint8_t ENABLE   = 0x02;  //  Bit 1: ALS/UVS Enable
    constexpr uint8_t UVS_MODE = 0x08;  //  Bit 3: 1 = UV, 0 = ALS
    constexpr uint8_t SW_RESET = 0x10;  //  Bit 4: Software reset

    constexpr uint8_t ALS_ACTIVE = ENABLE;             //  ALS mode (UVS_MODE = 0)
    constexpr uint8_t UVS_ACTIVE = ENABLE | UVS_MODE;  //  UV mode
  }

  namespace I2C
  {
    constexpr uint8_t ADDRESS = 0x53;
  }

  namespace MEAS_RATE
  {
    constexpr uint8_t RATE_MASK = 0x07; // bits 0-2
    constexpr uint8_t RES_MASK  = 0x70; // bits 4-6
    constexpr uint8_t RES_SHIFT = 4;
  }

  namespace STATUS
  {
    constexpr uint8_t POWER_ON  = 1 << 5; // 0x20
    constexpr uint8_t INTERRUPT_BIT = 1 << 4; // 0x10
    constexpr uint8_t DATA_RDY  = 1 << 3; // 0x08
    constexpr uint8_t MASK = POWER_ON | INTERRUPT_BIT | DATA_RDY;
  }

  namespace PART_ID
  {
    constexpr uint8_t MASK     = 0xF0; // bits 7:4
    constexpr uint8_t REV_MASK = 0x0F; // bits 3:0
    constexpr uint8_t SHIFT    = 4;
  }

  namespace DATA
  {
    constexpr uint8_t ADC_DATA_MASK = 0x0F; // bits 3:0 valid data
  }

  namespace THRESHOLD
  {
    constexpr uint8_t MSB_MASK  = 0x0F; // upper/lower threshold high byte
    constexpr uint8_t FULL_MASK = 0xFF; // full 8-bit mask
  }
}

class LTR390
{
public:
  explicit LTR390(TwoWire *wire = &Wire):
    _wire{wire},
    _address{LTR390RT::I2C::ADDRESS}
  {}

  bool begin()
  {
    return isConnected();
  }

  bool isConnected() const
  {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
  }

  uint8_t getAddress() const
  {
    return _address;
  }

  //////////////////////////////////////////////
  //
  //  MAIN CONTROL
  //
  void setALSMode()
  {
    writeRegister(LTR390RT::REGISTER::MAIN_CTRL, LTR390RT::MAIN_CTRL::ALS_ACTIVE);
  }

  void setUVSMode()
  {
    writeRegister(LTR390RT::REGISTER::MAIN_CTRL, LTR390RT::MAIN_CTRL::UVS_ACTIVE);
  }

  uint8_t reset()
  {
    writeRegister(LTR390RT::REGISTER::MAIN_CTRL, LTR390RT::MAIN_CTRL::SW_RESET);
    delay(100);
    return readRegister(LTR390RT::REGISTER::MAIN_CTRL);
  }

  void enable()
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_CTRL);
    reg |= LTR390RT::MAIN_CTRL::ENABLE;
    writeRegister(LTR390RT::REGISTER::MAIN_CTRL, reg);
  }

  void disable()
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_CTRL);
    reg &= ~LTR390RT::MAIN_CTRL::ENABLE;
    writeRegister(LTR390RT::REGISTER::MAIN_CTRL, reg);
  }

  [[nodiscard]] bool isEnabled() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_CTRL);
    return (reg & LTR390RT::MAIN_CTRL::ENABLE) > 0;
  }

  //////////////////////////////////////////////
  //
  //  MEASUREMENT CONFIGURATION
  //
  void setResolution(uint8_t resolution) //  resolution = 0..5 (2 default)
  {
    if (resolution > 5)
      resolution = 5;

    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE);
    reg &= LTR390RT::MEAS_RATE::RATE_MASK;
    reg |= (resolution << LTR390RT::MEAS_RATE::RES_SHIFT);
    writeRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE, reg);
  }

  [[nodiscard]] uint8_t getResolution() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE);
    return (reg >> LTR390RT::MEAS_RATE::RES_SHIFT) & LTR390RT::MEAS_RATE::RATE_MASK;
  }

  [[nodiscard]] float getIntegrationTime() const
  {
    static const uint16_t intTime[6] = {800, 400, 200, 100, 50, 25};
    return intTime[getResolution()] * 0.5f;
  }

  //////////////////////////////////////////////

  void setRate(uint8_t rate) //  rate = 0..7 (2 default)
  {
    if (rate > 7)
      rate = 7;
    
    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE);
    reg &= ~LTR390RT::MEAS_RATE::RES_MASK;
    reg |= rate;
    writeRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE, reg);
  }

  [[nodiscard]] uint8_t getRate() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_MEAS_RATE);
    return reg & LTR390RT::MEAS_RATE::RATE_MASK;
  }

  [[nodiscard]] float getMeasurementTime() const
  {
    static const uint16_t measTime[8] = {25, 50, 100, 200, 500, 1000, 2000, 2000};
    return measTime[getRate()];
  }

  //////////////////////////////////////////////

  void setGain(uint8_t gain) //  gain = 0..4
  {
    if (gain > 4)
      gain = 4;
    
    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_GAIN);
    reg &= ~LTR390RT::MEAS_RATE::RATE_MASK;
    reg |= gain;
    writeRegister(LTR390RT::REGISTER::ALS_UVS_GAIN, reg);
  }

  [[nodiscard]] uint8_t getGain() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::ALS_UVS_GAIN);
    return reg & LTR390RT::MEAS_RATE::RATE_MASK;
  }

  [[nodiscard]] uint8_t getGainFactor() const
  {
    static const uint8_t gainFactor[5] = {1, 3, 6, 9, 18};
    return gainFactor[getGain()];
  }

  //////////////////////////////////////////////
  //
  //  PART_ID
  //
  [[nodiscard]] uint8_t getPartID() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::PART_ID);
    return (reg & LTR390RT::PART_ID::MASK) >> LTR390RT::PART_ID::SHIFT;
  }

  [[nodiscard]] uint8_t getRevisionID() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::PART_ID);
    return reg & LTR390RT::PART_ID::REV_MASK;
  }

  //////////////////////////////////////////////
  //
  //  MAIN STATUS
  //
  [[nodiscard]] uint8_t getStatus() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_STATUS);
    return reg & LTR390RT::STATUS::MASK;
  }

  [[nodiscard]] bool getPowerOnStatus() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_STATUS);
    return (reg & LTR390RT::STATUS::POWER_ON) > 0;
  }

  [[nodiscard]] bool getInterruptStatus() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_STATUS);
    return (reg & LTR390RT::STATUS::INTERRUPT_BIT) > 0;
  }

  [[nodiscard]] bool getDataStatus() const
  {
    uint8_t reg = readRegister(LTR390RT::REGISTER::MAIN_STATUS);
    return (reg & LTR390RT::STATUS::DATA_RDY) > 0;
  }

  //////////////////////////////////////////////
  //
  //  GET DATA
  //
  [[nodiscard]] uint32_t getALSData() const
  {
    uint32_t value = readRegister(LTR390RT::REGISTER::ALS_DATA_2) & LTR390RT::DATA::ADC_DATA_MASK;

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_DATA_1);

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_DATA_0);

    return value;
  }

  [[nodiscard]] uint32_t getUVSData() const
  {
    uint32_t value = readRegister(LTR390RT::REGISTER::UVS_DATA_2) & LTR390RT::DATA::ADC_DATA_MASK;

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::UVS_DATA_1);

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::UVS_DATA_0);

    return value;
  }

  [[nodiscard]] float getLUX(float windowsFactor = 1.0f) const
  {
    float lux = (100.0f * 0.6f) * getALSData();
    lux /= (getGainFactor() * getIntegrationTime());

    if (windowsFactor > 1.0f)
      lux *= windowsFactor;

    return lux;
  }

  [[nodiscard]] float getUVIndex(float windowsFactor = 1.0f) const
  {
    float reciprokeSensitivity = (18.0f * 400.0f) / 2300.0f;
    reciprokeSensitivity /= (getGainFactor() * getIntegrationTime());
    
    float uvi = getUVSData() * reciprokeSensitivity;

    if (windowsFactor > 1.0f)
      uvi *= windowsFactor;

    return uvi;
  }

  //////////////////////////////////////////////
  //
  //  INTERRUPT
  //  TODO elaborate
  //
  [[nodiscard]] int setInterruptConfig(uint8_t value)
  {
    return writeRegister(LTR390RT::REGISTER::INT_CFG, value);
  }

  [[nodiscard]] uint8_t getInterruptConfig() const
  {
    return readRegister(LTR390RT::REGISTER::INT_CFG);
  }

  int setInterruptPersist(uint8_t value)
  {
    return writeRegister(LTR390RT::REGISTER::INT_PST, value);
  }

  [[nodiscard]] uint8_t getInterruptPersist() const
  {
    return readRegister(LTR390RT::REGISTER::INT_PST);
  }

  //////////////////////////////////////////////
  //
  //  THRESHOLD
  //  TODO elaborate
  //
  void setHighThreshold(uint32_t value)
  {
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_0, value & LTR390RT::THRESHOLD::FULL_MASK);
    value >>= 8;    
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_1, value & LTR390RT::THRESHOLD::FULL_MASK);
    value >>= 8;
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_2, value & LTR390RT::THRESHOLD::MSB_MASK);
  }

  [[nodiscard]] uint32_t getHighThreshold() const
  {
    uint32_t value = readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_2) & LTR390RT::THRESHOLD::MSB_MASK;

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_1);
    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_UP_0);

    return value;
  }

  void setLowThreshold(uint32_t value)
  {
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_0, value & LTR390RT::THRESHOLD::FULL_MASK);
    value >>= 8;
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_1, value & LTR390RT::THRESHOLD::FULL_MASK);
    value >>= 8;
    writeRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_2, value & LTR390RT::THRESHOLD::MSB_MASK);
  }

  [[nodiscard]] uint32_t getLowThreshold() const
  {
    uint32_t value = readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_2) & LTR390RT::THRESHOLD::MSB_MASK;

    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_1);
    value <<= 8;
    value += readRegister(LTR390RT::REGISTER::ALS_UVS_THRES_LOW_0);

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
    // if (n != 0)
    //{
    //   Serial.print("write:\t");
    //   Serial.println(n);
    // }
    return n;
  }

  uint8_t readRegister(uint8_t reg) const
  {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    int n = _wire->endTransmission();
    // if (n != 0)
    //{
    //   Serial.print("read:\t");
    //   Serial.println(n);
    //   return n;
    // }

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
  TwoWire *_wire;
  uint8_t _address;
};

//  -- END OF FILE --
