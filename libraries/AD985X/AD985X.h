#pragma once
//
//    FILE: AD985X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2019-02-08
// PURPOSE: Class for AD9850 and AD9851 function generator
//
//     URL: https://github.com/RobTillaart/AD985X
//


#include "Arduino.h"
#include "SPI.h"


#define AD985X_LIB_VERSION    (F("0.3.1"))


#define AD9850_MAX_FREQ       (40UL * 1000UL * 1000UL)
#define AD9851_MAX_FREQ       (70UL * 1000UL * 1000UL)


class AD9850
{
public:
  AD9850();

  // for HW SPI only use lower 3 parameters.
  void     begin(uint8_t select, uint8_t resetPin, uint8_t FQUDPin, uint8_t dataOut = 0, uint8_t clock = 0);
  void     reset();
  void     powerDown();
  void     powerUp();

  void     setFrequency(uint32_t freq);         // 0..AD9850_MAX_FREQ
  void     setFrequencyF(float freq);           // works best for lower frequencies.
  float    getFrequency()    { return _freq; };
  uint32_t getMaxFrequency() { return AD9850_MAX_FREQ; };

  // 0 .. 31  steps of 11.25 degrees
  void     setPhase(uint8_t phase = 0);
  uint8_t  getPhase()        { return (_config >> 3); };

  // offset to calibrate the frequency (internal counter)
  // offset must be stored by the user.
  void     setCalibration(int32_t offset = 0) { _offset = offset; };
  int32_t  getCalibration()  { return _offset; };
  // internal chip factor used for frequency. (debugging only)
  uint32_t getFactor()       { return _factor; };

  // autoUpdate is default true;
  void     setAutoUpdate(bool update) { _autoUpdate = update; };  
  bool     getAutoUpdate()   { return _autoUpdate; };
  void     update();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  // debugging
  bool     usesHWSPI() { return _hwSPI; };
  
  // ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  // to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


protected:
  void     pulsePin(uint8_t pin);
  void     writeData();
  void     swSPI_transfer(uint8_t val);

  bool     _hwSPI    = true;
  uint32_t _SPIspeed = 2000000;

  SPIClass    * mySPI;
  SPISettings _spi_settings;

#if defined(ESP32)
  bool        _useHSPI = true;
#endif

  // PINS
  uint8_t  _dataOut = 0;
  uint8_t  _clock   = 0;
  uint8_t  _select  = 0;
  uint8_t  _reset   = 0;
  uint8_t  _fqud    = 0;  // frequency update

  // SIGNAL
  float    _freq    = 1;
  uint32_t _factor  = 0;
  uint8_t  _config  = 0;
  int32_t  _offset  = 0;
  bool     _autoUpdate = true;
};


class AD9851 : public AD9850
{
public:
  void     setFrequency(uint32_t freq);    // 0..AD9851_MAX_FREQ
  void     setFrequencyF(float freq);
  uint32_t getMaxFrequency()  { return AD9851_MAX_FREQ; };

  void     setRefClockHigh();   // 180 MHz
  void     setRefClockLow();    //  30 MHz
  uint8_t  getRefClock();

  void     setAutoRefClock(bool arc);
  bool     getAutoRefClock()  { return _autoRefClock; };

  // 10 MHz is default, set in Hz.
  // will be kept <= 30 MHz as that is the freq of LOW mode.
  void     setARCCutOffFreq(uint32_t Hz = 10000000UL );
  uint32_t getARCCutOffFreq() { return _ARCCutOffFreq; };

protected:
  bool     _autoRefClock = false;
  uint32_t _ARCCutOffFreq = 10000000UL;

};

// -- END OF FILE --
