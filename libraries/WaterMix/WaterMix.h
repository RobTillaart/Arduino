#pragma once
//
//    FILE: WaterMix.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for mixing water with different temperatures.
// VERSION: 0.1.3
//     URL: https://github.com/RobTillaart/WaterMix


#include "Arduino.h"


#define WATERMIX_LIB_VERSION     (F("0.1.3"))


////////////////////////////////////////////
//
//  LIQUIDMIX
//
class LiquidMix
{
public:
  LiquidMix()
  {
    _volume = 0;
    _temperature = 0;
  }

  void begin(float volume = 0, float temperature = 0)
  {
    _volume = volume;
    _temperature = temperature;
  }

  void add(float volume, float temperature)
  {
    if (volume <= 0) return;  //  false ?
    float vol = _volume + volume;
    _temperature = (_volume * _temperature + volume * temperature) / vol;
    _volume = vol;
  }

  void add(LiquidMix &lm)
  {
    add(lm.volume(), lm.temperature());
  }

  void sub(float volume)
  {
    _volume -= volume;
    if (_volume <= 0) _volume = 0;
    //  temperature does not change.
  }

  void div(float nr)
  {
    _volume /= nr;
    //  temperature does not change.
  }

  void mul(float nr)
  {
    _volume *= nr;
    //  temperature does not change.
  }

  float volume()
  {
    return _volume;
  }

  float temperature()
  {
    return _temperature;
  }


protected:
  float   _volume;
  float   _temperature;
};


////////////////////////////////////////////
//
//  WATERMIX
//
class WaterMix : public LiquidMix
{
public:
  WaterMix() : LiquidMix()
  {
  }

  void add(float volume, float temperature)
  {
    LiquidMix::add(volume, temperature);
  }

  void addExact(float volume, float temperature)
  {
    if (volume <= 0) return;  //  false
    float mass0     = _volume * density(_temperature);
    float mass1     =  volume * density(temperature);
    float totalMass =  mass0 + mass1;

    _temperature = (mass0 * _temperature + mass1 * temperature) / totalMass;
    _volume = totalMass / density(_temperature);
  }

  void add(WaterMix &wm)
  {
    LiquidMix::add(wm.volume(), wm.temperature());
  }

  void addExact(WaterMix &wm)
  {
    addExact(wm.volume(), wm.temperature());
  }

  float mass()
  {
    return _volume * density(_temperature);
  }

  float volume2mass(float volume, float temperature)
  {
    return volume * density(temperature);
  }

  float mass2volume(float mass, float temperature)
  {
    return mass / density(temperature);
  }


  //  density is in fact multiMap code
  float  density(float temperature)
  {
    //  strip table size?
    uint8_t size = 22;
    uint8_t _in[]  = { 0, 1, 4, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    float _out[] = {
      0.9998495,  0.9999017,  0.9999749,  0.9997000,  0.9991026,
      0.9982067,  0.9970470,  0.9956488,  0.9940326,  0.9922152,
      0.9902100,  0.9880400,  0.9856900,  0.9832000,  0.9805500,
      0.9777600,  0.9748400,  0.9717900,  0.9686100,  0.9653100,
      0.9618900,  0.9583500
    };

    //  take care the temperature is within range
    //  temperature = constrain(temperature, _in[0], _in[size-1]);
    if (temperature <= _in[0]) return _out[0];
    if (temperature >= _in[size-1]) return _out[size-1];

    //  search right interval
    uint8_t pos = 1;  //  _in[0] already tested
    while(temperature > _in[pos]) pos++;

    //  this will handle all exact "points" in the _in array
    if (temperature == _in[pos]) return _out[pos];

    //  interpolate in the right segment for the rest
    uint8_t pos1 = pos - 1;
    return (temperature - _in[pos1]) * (_out[pos] - _out[pos1]) / (_in[pos] - _in[pos1]) + _out[pos1];
  }
};


//  -- END OF FILE --
