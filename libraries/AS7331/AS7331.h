#pragma once
//
//    FILE: AS7331.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-08-28
// VERSION: 0.1.0
// PURPOSE: Arduino library for AS7331 UV sensor
//     URL: https://github.com/RobTillaart/AS7331
//          https://www.sparkfun.com/products/23517
//
//   SHEET: DS001047, v4.00, 2023-Mar-24
//

#include "Arduino.h"
#include "Wire.h"


#define AS7331_LIB_VERSION         (F("0.1.0"))

#ifndef AS7331_DEFAULT_ADDRESS
#define AS7331_DEFAULT_ADDRESS     0x2A
#endif

//  ERROR CODES
//  values <> 0 are errors.
#define AS7331_OK                  0x00
#define AS7331_CRC_ERROR           0x01
#define AS7331_NOT_READY           0x10
#define AS7331_REQUEST_ERROR       0x11


//  MODE OPERANDI
#define AS7331_MODE_CONTINUOUS     0x00  //  future
#define AS7331_MODE_MANUAL         0x01  //  (default) 0.1.0 version
#define AS7331_MODE_SYNS           0x02  //  future
#define AS7331_MODE_SYND           0x03  //  future


//  GAIN OPERANDI
#define AS7331_GAIN_1x             0x0B
#define AS7331_GAIN_2x             0x0A
#define AS7331_GAIN_4x             0x09
#define AS7331_GAIN_8x             0x08
#define AS7331_GAIN_16x            0x07
#define AS7331_GAIN_32x            0x06
#define AS7331_GAIN_64x            0x05
#define AS7331_GAIN_128x           0x04
#define AS7331_GAIN_256x           0x03
#define AS7331_GAIN_512x           0x02
#define AS7331_GAIN_1024x          0x01
#define AS7331_GAIN_2048x          0x00


//  CONVERSION TIME OPERANDI
//                 _millis
#define AS7331_CONV_001            0x00
#define AS7331_CONV_002            0x01
#define AS7331_CONV_004            0x02
#define AS7331_CONV_008            0x03
#define AS7331_CONV_016            0x04
#define AS7331_CONV_032            0x05
#define AS7331_CONV_064            0x06
#define AS7331_CONV_128            0x07
#define AS7331_CONV_256            0x08
#define AS7331_CONV_512            0x09
#define AS7331_CONV_1024           0x0A
#define AS7331_CONV_2048           0x0B
#define AS7331_CONV_4096           0x0C
#define AS7331_CONV_8192           0x0D
#define AS7331_CONV_16384          0x0E
#define AS7331_CONV_001xx          0x0F   //  TODO check datasheet


//  CLOCK FREQUENCY OPERANDI
//                  MHz
#define AS7331_CCLK_1024           0x00
#define AS7331_CCLK_2048           0x01
#define AS7331_CCLK_4096           0x02
#define AS7331_CCLK_8192           0x03


class AS7331
{
public:
  AS7331(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();  //  uint8_t RDY = 255, uint8_t SYN = 255); TODO
  bool     isConnected();
  uint8_t  getAddress();  //  debug purpose

  //
  //  CONFIGURATION STATE
  //
  //  MODE,  REGISTER 0x08 CREG3
  bool     setMode(uint8_t mode = AS7331_MODE_MANUAL);
  uint8_t  getMode();  //  from device.
  //  STANDBY
  void     setStandByOn();
  void     setStandByOff();


  //  GAIN & TIMING, REGISTER 0x06 CREG1
  //  gain = 0..11 (powers of 2)
  //         0  => 2048x
  //         11 => 1x
  bool     setGain(uint8_t gain);
  uint8_t  getGain();  //  from device.
  //  convTime = 0..15
  //       0  = 1 ms
  //       14 = 16384 ms
  //       15 = 1 ms
  bool     setConversionTime(uint8_t convTime);
  uint8_t  getConversionTime();  //  from device.


  //  DEVICE-ID, REGISTER 0x02 AGEN
  uint8_t  getDeviceID();  //  default = 0x21


  //  REGISTER 0x00 OSR
  //       control
  void     stopMeasurement();
  void     startMeasurement();
  void     powerDown();
  void     powerUp();
  void     softwareReset();
  void     setConfigurationMode();
  void     setMeasurementMode();
  //  TODO  uint8_t readBackOSR(); or separate functions?


  //  READY PIN, REGISTER 0x08 CREG3
  void     setRDYOpenDrain();
  void     setRDYPushPull();  //  default


  //  INTERNAL CLOCK, REGISTER 0x08 CREG3
  //  placeholder.
  bool     setClockFrequency(uint8_t CCLK);
  uint8_t  getClockFrequency();


  //
  //  MEASURMENT STATE
  //
  //  READ FUNCTION
  //
  //       STATUS
  uint8_t  readStatus();
  bool     conversionReady();
  //       READ
  //       returns in microWatts / cm2
  float    getUVA();
  float    getUVB();
  float    getUVC();
  float    getCelsius();


  //       DEBUG
  int      getLastError();


  ///////////////////////////////////////////////////
  //
  //  FUTURE TODO CONT, SYNS and SYND mode
  //
  //  REGISTER 0x07 CREG2
  //  for synS / synD control
  //  EN_TM (6), EN_DIV(3), DIV(2:0)

  //  BREAK time, REGISTER 0x09 BREAK
  //  for CONT, SYNS and SYND mode
  //  0..255  getter/setter

  //  EDGES time, REGISTER 0x09 EDGES
  //  for SYND mode
  //  1..255  getter/setter

  //  OPTIONS, REGISTER 0x0B OPTREG
  //  read datasheet, low level I2C - INITT_IDX in bit 0.

  //  bool conversionReady();  //  check status register (other?)


private:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  uint8_t  _mode;
  uint8_t  _gain;
  uint8_t  _convTime;
  uint8_t  _error;

  //  TODO adjust when gain or Tconv changes.
  void     _adjustGainTimeFactor();
  float    _GainTimeFactor =  1;

  int      _writeRegister8(uint8_t reg, uint8_t value);
  uint8_t  _readRegister8(uint8_t reg);
  uint16_t _readRegister16(uint8_t reg);
};


//  -- END OF FILE --

