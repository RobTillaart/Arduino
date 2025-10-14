#pragma once
//
//    FILE: AS7331.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-08-28
// VERSION: 0.3.0
// PURPOSE: Arduino library for AS7331 UV sensor
//     URL: https://github.com/RobTillaart/AS7331
//          https://www.sparkfun.com/products/23517
//
//   SHEET: DS001047, v4.00, 2023-Mar-24
//

#include "Arduino.h"
#include "Wire.h"


#define AS7331_LIB_VERSION          (F("0.3.0"))

#ifndef AS7331_DEFAULT_ADDRESS
#define AS7331_DEFAULT_ADDRESS      0x74
#endif

//  ERROR CODES
//  values <> 0 are errors.
#define AS7331_OK                   0x00
#define AS7331_CRC_ERROR            0x01
#define AS7331_NOT_READY            0x10
#define AS7331_REQUEST_ERROR        0x11


//  MODE OPERANDI
#define AS7331_MODE_CONTINUOUS      0x00
#define AS7331_MODE_MANUAL          0x01  //  default
#define AS7331_MODE_SYNS            0x02
#define AS7331_MODE_SYND            0x03  //  not supported yet


//  GAIN OPERANDI
#define AS7331_GAIN_1x              0x0B
#define AS7331_GAIN_2x              0x0A
#define AS7331_GAIN_4x              0x09
#define AS7331_GAIN_8x              0x08
#define AS7331_GAIN_16x             0x07
#define AS7331_GAIN_32x             0x06
#define AS7331_GAIN_64x             0x05
#define AS7331_GAIN_128x            0x04
#define AS7331_GAIN_256x            0x03
#define AS7331_GAIN_512x            0x02
#define AS7331_GAIN_1024x           0x01
#define AS7331_GAIN_2048x           0x00


//  CONVERSION TIME OPERANDI
//                 _millis
#define AS7331_CONV_001             0x00
#define AS7331_CONV_002             0x01
#define AS7331_CONV_004             0x02
#define AS7331_CONV_008             0x03
#define AS7331_CONV_016             0x04
#define AS7331_CONV_032             0x05
#define AS7331_CONV_064             0x06
#define AS7331_CONV_128             0x07
#define AS7331_CONV_256             0x08
#define AS7331_CONV_512             0x09
#define AS7331_CONV_1024            0x0A
#define AS7331_CONV_2048            0x0B
#define AS7331_CONV_4096            0x0C
#define AS7331_CONV_8192            0x0D
#define AS7331_CONV_16384           0x0E
#define AS7331_CONV_001xx           0x0F   //  check datasheet


//  CLOCK FREQUENCY OPERANDI
//                  MHz
#define AS7331_CCLK_1024            0x00
#define AS7331_CCLK_2048            0x01
#define AS7331_CCLK_4096            0x02
#define AS7331_CCLK_8192            0x03


//  STATUS BIT MASKS
//  to test against getStatus()
#define AS7331_STATUS_OUTCONVOF     0x8000
#define AS7331_STATUS_MRESOF        0x4000
#define AS7331_STATUS_ADCOF         0x2000
#define AS7331_STATUS_LDATA         0x1000
#define AS7331_STATUS_NDATA         0x0800
#define AS7331_STATUS_NOTREADY      0x0400
#define AS7331_STATUS_STANDBYSTATE  0x0200
#define AS7331_STATUS_POWERSTATE    0x0100


class AS7331
{
public:
  //
  //  CONSTRUCTOR
  //
  AS7331(uint8_t address, TwoWire *wire = &Wire);
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();  //  debug purpose
  void     softwareReset();

  //
  //  CONFIGURATION STATE
  //
  //  MODE,  REGISTER 0x08 CREG3
  bool     setMode(uint8_t mode = AS7331_MODE_MANUAL);
  uint8_t  getMode();  //  from device.
  //  STANDBY  (e.g. page 20)
  //  0 == StandBy, 1 == Idle, Convert, ...
  void     setStandByOn();
  void     setStandByOff();
  uint8_t  getStandByMode();


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
  //  control, partially tested.
  void     stopMeasurement();
  void     startMeasurement();  //  sets Measurement mode too.
  void     powerDown();
  void     powerUp();
  void     setConfigurationMode();
  void     setMeasurementMode();


  //  READY PIN, REGISTER 0x08 CREG3
  //  not tested.
  void     setRDYOpenDrain();
  void     setRDYPushPull();  //  default


  //  INTERNAL CLOCK, REGISTER 0x08 CREG3
  //  not tested.
  bool     setClockFrequency(uint8_t CCLK);
  uint8_t  getClockFrequency();


  //
  //  MEASUREMENT STATUS
  //
  //       OSR in CONFIGURATION MODE
  uint8_t  readOSR();
  //       OSR + status in MEASUREMENT MODE (page 59)
  //       LOW byte  == OSR (page 59)
  //       HIGH byte == status
  uint16_t readStatus();
  //       To be used in POLLING mode
  bool     conversionReady();

  //       READ the measurements
  //       returns in microWatts / cm2
  float    getUVA_uW();
  float    getUVB_uW();
  float    getUVC_uW();
  float    getCelsius();  //  inner temperature.
  //  wrappers
  //       returns in milliWatts / cm2
  float    getUVA_mW() { return getUVA_uW() * 0.001; };
  float    getUVB_mW() { return getUVA_uW() * 0.001; };
  float    getUVC_mW() { return getUVA_uW() * 0.001; };
  //       returns in Watts / m2
  float    getUVA_Wm2() { return getUVA_uW() * 0.01; };
  float    getUVB_Wm2() { return getUVA_uW() * 0.01; };
  float    getUVC_Wm2() { return getUVA_uW() * 0.01; };


  //       BREAK-TIME, REGISTER 0x09 BREAK
  //       step size == 8 us, 0..255 ==> 0..2040 usec.
  //       to be used to set the time needed to fetch the data
  //       over I2C, so I2C does not disturb measurements.
  void     setBreakTime(uint8_t breakTime);
  uint8_t  getBreakTime();


  //       DEBUG
  int      getLastError();


  //  0.3.0 added
  ///////////////////////////////////////////////////
  //
  //       Configuration - REGISTER 0x07 CREG2
  //       for SYNS / SYND control
  //       CREG2.EN_TM(6) - SYND Only
  void     enableTemperature();
  void     disableTemperature();
  bool     isEnabledTemperature();

  //       CREG2.EN_DIV(3)
  void     enableDivider();
  void     disableDivider();
  bool     isEnabledDivider();

  //       CREG2.DIV(2:0)
  bool     setDivider(uint8_t div);
  uint8_t  getDivider();


  //       EDGES - REGISTER 0x0A EDGES
  //       used in SYND only
  //       1..255 edges (0 maps to 1)
  void     setEdges(uint8_t edges);
  uint8_t  getEdges();


  //       OPTIONS, REGISTER 0x0B OPTREG
  //       read datasheet, adjust low level I2C
  //       OPTREG.INITT_IDX(0)
  void     setInitIdx();
  void     clrInitIdx();

  //
  //  OUTCONV = timing ?
  uint32_t getOUTCONV();


  ///////////////////////////////////////////////////

private:
  int      _writeRegister8(uint8_t reg, uint8_t value);
  uint8_t  _readRegister8(uint8_t reg);
  uint16_t _readRegister16(uint8_t reg);

  uint8_t  _address;
  TwoWire* _wire;

  uint8_t  _mode;
  uint8_t  _gain;
  uint8_t  _convTime;
  uint8_t  _error;

  //  to adjust when gain or Tconv changes.
  void     _adjustGainTimeFactor();
  float    _GainTimeFactor = 1.0f;
};


//  -- END OF FILE --

