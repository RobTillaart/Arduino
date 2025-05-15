#pragma once
//
//    FILE: AD5593R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-30
// PURPOSE: Arduino library for AD5593R, I2C, 8 channel ADC / DAC / GPIO device.
//     URL: https://github.com/RobTillaart/AD5593R
//
//  read datasheet for details.


#include "Arduino.h"
#include "Wire.h"


#define AD5593R_LIB_VERSION        (F("0.1.1"))


//  ERROR CODES
#define AD5593R_OK                  0x0000
#define AD5593R_PIN_ERROR           0xFF81
#define AD5593R_I2C_ERROR           0xFF82
#define AD5593R_LDAC_ERROR          0xFF83


//  LDAC MODI
const uint8_t AD5593R_LDAC_DIRECT  = 0;
const uint8_t AD5593R_LDAC_HOLD    = 1;
const uint8_t AD5593R_LDAC_RELEASE = 2;


class AD5593R
{
public:
  AD5593R(const uint8_t deviceAddress, TwoWire * wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  MODE
  //  A=ADC, D=DAC, I=INPUT, O=OUTPUT, T=THREESTATE e.g. "AADDIIOT"
  //  (datasheet) last set mode bit counts.
  int      setMode(const char config[9]);
  int      setADCmode(uint8_t bitMask);
  int      setDACmode(uint8_t bitMask);
  int      setINPUTmode(uint8_t bitMask);
  int      setOUTPUTmode(uint8_t bitMask);
  int      setTHREESTATEmode(uint8_t bitMask);


  // PULL DOWN IO - 85 KOhm
  int      setPULLDOWNmode(uint8_t bitMask);

  //  LATCH (dac)
  //  mode                    meaning
  //  AD5593R_LDAC_DIRECT  => COPY input register direct to DAC. (default)
  //  AD5593R_LDAC_HOLD    => HOLD in input registers.
  //  AD5593R_LDAC_RELEASE => RELEASE all input registers to DAC simultaneously.
  //  must be set AFTER setExternalReference
  int      setLDACmode(uint8_t mode);

  //  OPENDRAIN
  //  page 26 - output mode - pull up resistor needed.
  //  bitMask should match output pins.
  int     setOpenDrainMode(uint8_t bitMask);


  //  DIGITAL IO
  //  pin = 0..7, value = LOW or HIGH
  uint16_t write1(uint8_t pin, uint8_t value);
  uint16_t read1(uint8_t pin);
  uint16_t write8(uint8_t bitMask);
  uint16_t read8();


  //  REFERENCE VOLTAGE VREF
  //  power on = internal reference 2.5V
  //  true = external reference, false = internal reference.
  int      setExternalReference(bool flag, float Vref);
  float    getVref();
  //  configure ADC / DAC range
  //  false == 1x Vref or true == 2x Vref.
  int      setADCRange2x(bool flag);
  int      setDACRange2x(bool flag);

  //  GENERAL CONTROL
  //  page 33
  int      enableADCBufferPreCharge(bool flag);
  int      enableADCBuffer(bool flag);
  int      enableIOLock(bool flag);
  //  page 34
  int      writeAllDacs(bool flag);


  //  ANALOG IO
  uint16_t writeDAC(uint8_t pin, uint16_t value);
  //  reads back last written value
  uint16_t readDAC(uint8_t pin);
  uint16_t readADC(uint8_t pin);
  //  temperature page 19.  indicative, accuracy 3C over 5 samples averaged.
  float readTemperature();


  //  POWER
  //  power on => internal reference 2.5V
  int      powerDown();
  int      wakeUp();
  //  DACs can be separately disabled.
  int      powerDownDac(uint8_t pin);
  int      wakeUpDac(uint8_t pin);


  //  RESET
  int      reset();


  //  LOW LEVEL access for full control
  int      writeRegister(uint8_t reg, uint16_t data);
  uint16_t readIORegister(uint8_t reg);
  uint16_t readConfigRegister(uint8_t reg);

protected:
  uint8_t _address;
  int     _error;
  float   _Vref;
  int     _gain;

  TwoWire*  _wire;
};



//  -- END OF FILE --

