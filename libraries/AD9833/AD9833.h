#pragma once
//
//    FILE: AD9833.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AD9833 function generator.
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/AD9833


#include "Arduino.h"
#include "SPI.h"


#define AD9833_LIB_VERSION     (F("0.1.0"))


#define AD9833_MAX_FREQ       (12500000UL)  //  12.5 MHz.
#define AD9833_MAX_PHASE      (360.0)


//  MODE OPERANDI
#define AD9833_OFF            0
#define AD9833_SINE           1
#define AD9833_SQUARE1        2
#define AD9833_SQUARE2        3
#define AD9833_TRIANGLE       4


class AD9833
{
public:
  AD9833();

  //  selectPin == fsyncPin
  void     begin(uint8_t selectPin, uint8_t dataPin = 0, uint8_t clockPin = 0);
  void     begin(uint8_t selectPin, SPIClass * spi);

  void     reset();

  void     setWave(uint8_t wave = AD9833_OFF);
  uint8_t  getWave();


  //       returns frequency set
  //       0 .. 12.5 MHz == AD9833_MAX_FREQ
  float    setFrequency(float freq, uint8_t channel = 0);
  float    getFrequency(uint8_t channel = 0);
  float    getMaxFrequency();
  void     setFrequencyChannel(uint8_t channel);

  //       returns phase set
  //       [0 .. 360>
  float    setPhase(float phase, uint8_t channel = 0);
  float    getPhase(uint8_t channel = 0);
  float    getMaxPhase();
  void     setPhaseChannel(uint8_t channel);


  //       Hardware SPI settings
  void     setSPIspeed(uint32_t speed);  //  speed in Hz
  uint32_t getSPIspeed();
  bool     usesHWSPI();


  //  ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  //  to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif

private:

  void     writeControlRegister(uint16_t value);
  void     writeFreqRegister(uint8_t reg, uint32_t freq);
  void     writePhaseRegister(uint8_t reg, uint16_t value);
  void     writeData(uint16_t data);

  bool     _hwSPI    = true;
  uint32_t _SPIspeed = 8000000;

  SPIClass    * mySPI;
  SPISettings _spi_settings;

#if defined(ESP32)
  bool        _useHSPI = true;
#endif

  //  PINS
  uint8_t  _dataPin   = 0;
  uint8_t  _clockPin  = 0;
  uint8_t  _selectPin = 0;


  //  SIGNAL
  uint16_t _control   = 0;
  uint8_t  _waveType  = AD9833_OFF;


  float    _freq[2]   = { 1000, 1000 };  //  Hz
  float    _phase[2]  = { 0, 0 };        //  angle
};



//  --  END OF FILE --

