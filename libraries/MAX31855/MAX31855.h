//
//    FILE: MAX31855.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.10
// PURPOSE: MAX31855 - Thermocouple
//    DATE: 2014-01-01
//     URL: http://forum.arduino.cc/index.php?topic=208061
//
// Released to the public domain
//
#ifndef MAX31855_H
#define MAX31855_H

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

#define MAX31855_VERSION "0.1.10"

#define STATUS_OK               0x00
#define STATUS_OPEN_CIRCUIT     0x01
#define STATUS_SHORT_TO_GND     0x02
#define STATUS_SHORT_TO_VCC     0x04
#define STATUS_ERROR            0x07
#define STATUS_NOREAD           0x80

//  Thermocouples working is based upon Seebeck effect.
//  Different TC have a different Seebeck Coefficient  (µV/°C)
//  From http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html
//
//  As the MAX31855 is designed for K type sensors, one can calculate
//  the factor needed to convert other sensors measurements.
//  note this is only a linear approximation.
//
//  E_TC = 61   =>    41/61 = 0.6721311475
//  J_TC = 52   =>    41/52 = 0.7884615385
//  K_TC = 41   =>    41/41 = 1
//  N_TC = 27   =>    41/27 = 1.5185185185
//  R_TC = 9    =>    41/9  = 4.5555555556
//  S_TC = 6    =>    41/6  = 6.8333333333
//  T_TC = 41   =>    41/41 = 1

//  0.1.07 updated with numbers from the MAX31855 datasheet
#define E_TC    (41.276/76.373)
#define J_TC    (41.276/57.953)
#define K_TC    (41.276/41.276)
#define N_TC    (41.276/36.256)
#define R_TC    (41.276/10.506)
#define S_TC    (41.276/9.587)
#define T_TC    (41.276/52.18)


class MAX31855
{
public:
    MAX31855(uint8_t SCLK, uint8_t CS, uint8_t MISO);
    void begin();

    uint8_t read();

    float   getInternal(void) const     { return _internal; }
    float   getTemperature(void) const  { return _temperature * _TCfactor; };

    uint8_t getStatus(void) const       { return _status; };
    // next 4 applies to last read
    inline  bool statusError() { return (_status & STATUS_ERROR) != 0; };
    inline  bool shortToGND()  { return (_status & STATUS_SHORT_TO_GND) != 0; };
    inline  bool shortToVCC()  { return (_status & STATUS_SHORT_TO_VCC) != 0; };
    inline  bool openCircuit() { return (_status & STATUS_OPEN_CIRCUIT) != 0; };

    void    setOffset(const float  t)   { _offset = t; };
    float   getOffset() const           { return _offset; };

    void    setTCfactor(const float  TCfactor) { _TCfactor = TCfactor; };
    float   getTCfactor() const         { return _TCfactor; };

private:
    uint32_t _read();
    float   _internal;
    float   _temperature;
    uint8_t _status;
    float   _offset;
    float   _TCfactor;

    uint8_t _sclk;
    uint8_t _miso;
    uint8_t _cs;
};

#endif

// END OF FILE
