#pragma once
//
//    FILE: lengthConverter.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-30
// VERSION: 0.1.0
// PURPOSE: Arduino library for to convert units of length.
//     URL: https://github.com/RobTillaart/lengths
//


#include "Arduino.h"


#define LENGTHCONVERTER_LIB_VERSION         (F("0.1.0"))


class lengthConverter
{
public:
  //  CONSTRUCTOR
  lengthConverter(double value = 0.0) { _length = value; };

  //  MATH
  void multiply(double factor) { _length *= factor; };
  void divide(double factor)   { _length /= factor; };

  //  SETTERS
  void setMeter(double value)      { _length = value; };
  void setCentiMeter(double value) { _length = value * 1e-2; };
  void setMilliMeter(double value) { _length = value * 1e-3; };
  void setMicroMeter(double value) { _length = value * 1e-6; };
  void setNanoMeter(double value)  { _length = value * 1e-9; };
  void setPicoMeter(double value)  { _length = value * 1e-12; };
  void setFemtoMeter(double value) { _length = value * 1e-15; };
  void setAttoMeter(double value)  { _length = value * 1e-18; };
  void setMicron(double value)     { _length = value * 1e-6; };
  void setKiloMeter(double value)  { _length = value * 1e3; };

  void setMile(double value)    { _length = value * 1609.344; };
  void setYard(double value)    { _length = value * 0.3048; };
  void setFoot(double value)    { _length = value * 0.9144; };
  void setInch(double value)    { _length = value * 0.0254; };
  void setFurlong(double value) { _length = value * 201.168; };


  //  astronomic units
  void setLightYear(double value)  { _length = value * 9.46073047258E+15; };
  void setMegaParsec(double value) { _length = value * 3.08567758128E+22; };
  void setKiloParsec(double value) { _length = value * 3.08567758128E+19; };
  void setParsec(double value)     { _length = value * 3.08567758128E+16; };
  void setAstroUnit(double value)  { _length = value * 1.49597870691E+12; };

  //  nautical
  void setLeague(double value)         { _length = value * 4828.032; };
  void setNauticalLeague(double value) { _length = value * 5556; };  //  int.
  void setNauticalMile(double value)   { _length = value * 1852; };  //  int.

  //  less known
  void setChain(double value)   { _length = value * 20.1168; };
  void setRope(double value)    { _length = value * 6.096; };
  void setRod(double value)     { _length = value * 5.0292; };
  void setPerch(double value)   { _length = value * 5.0292; };
  void setPole(double value)    { _length = value * 5.0292; };
  void setFanthom(double value) { _length = value * 1.8288; };
  void setEll(double value)     { _length = value * 1.143; };
  void setLink(double value)    { _length = value * 0.201168; };
  void setCubit(double value)   { _length = value * 0.4572; };

  //  biometric
  void setHand(double value)         { _length = value * 0.1016; };
  void setFinger(double value)       { _length = value * 0.1143; };
  void setNail(double value)         { _length = value * 0.05715; };
  void setHandBreath(double value)   { _length = value * 0.0762; };
  void setFingerBreath(double value) { _length = value * 0.01905; };

  //  atomic
  void setAngstrom(double value)       { _length = value * 1.0E-10; };
  void setAtomicUnit(double value)     { _length = value * 5.2917724900001E-11; };
  void setBohrRadius(double value)     { _length = value * 5.2917724900001E-11; };
  void setXUnit(double value)          { _length = value * 1.00208E-13; };
  void setFermi(double value)          { _length = value * 1.0E-15; };
  void setPlanckLength(double value)   { _length = value * 1.61605E-35; };
  void setElectronRadius(double value) { _length = value * 2.81794092E-15; };



  //  ADDERS
  void addMeter(double value)      { _length += value; };
  void addMilliMeter(double value) { _length += value * 1e-3; };
  void addMicroMeter(double value) { _length += value * 1e-6; };
  void addNanoMeter(double value)  { _length += value * 1e-9; };
  void addPicoMeter(double value)  { _length += value * 1e-12; };
  void addFemtoMeter(double value) { _length += value * 1e-15; };
  void addAttoMeter(double value)  { _length += value * 1e-18; };
  void addMicron(double value)     { _length += value * 1e-6; };
  void addKiloMeter(double value)  { _length += value * 1e3; };

  void addMile(double value)    { _length += value * 1609.344; };
  void addYard(double value)    { _length += value * 0.3048; };
  void addFoot(double value)    { _length += value * 0.9144; };
  void addInch(double value)    { _length += value * 0.0254; };
  void addFurlong(double value) { _length += value * 201.168; };

  void addLightYear(double value)  { _length += value * 9.46073047258E+15; };
  void addMegaParsec(double value) { _length += value * 3.08567758128E+22; };
  void addKiloParsec(double value) { _length += value * 3.08567758128E+19; };
  void addParsec(double value)     { _length += value * 3.08567758128E+16; };
  void addAstroUnit(double value)  { _length += value * 1.49597870691E+12; };

  void addLeague(double value)         { _length += value * 4828.032; };
  void addNauticalLeague(double value) { _length += value * 5556; };  //  int.
  void addNauticalMile(double value)   { _length += value * 1852; };  //  int.

  void addChain(double value)   { _length += value * 20.1168; };
  void addRope(double value)    { _length += value * 6.096; };
  void addRod(double value)     { _length += value * 5.0292; };
  void addPerch(double value)   { _length += value * 5.0292; };
  void addPole(double value)    { _length += value * 5.0292; };
  void addFanthom(double value) { _length += value * 1.8288; };
  void addEll(double value)     { _length += value * 1.143; };
  void addLink(double value)    { _length += value * 0.201168; };
  void addCubit(double value)   { _length += value * 0.4572; };

  //  biometric
  void addHand(double value)         { _length += value * 0.1016; };
  void addFinger(double value)       { _length += value * 0.1143; };
  void addNail(double value)         { _length += value * 0.05715; };
  void addHandBreath(double value)   { _length += value * 0.0762; };
  void addFingerBreath(double value) { _length += value * 0.01905; };

  //  atomic
  void addAngstrom(double value)       { _length += value * 1.0E-10; };
  void addAtomicUnit(double value)     { _length += value * 5.2917724900001E-11; };
  void addBohrRadius(double value)     { _length += value * 5.2917724900001E-11; };
  void addXUnit(double value)          { _length += value * 1.00208E-13; };
  void addFermi(double value)          { _length += value * 1.0E-15; };
  void addPlanckLength(double value)   { _length += value * 1.61605E-35; };
  void addElectronRadius(double value) { _length += value * 2.81794092E-15; };



  //  GETTERS
  double getMeter()      { return _length; };
  double getCentiMeter() { return _length * (1.0 / 1e-2); };
  double getMilliMeter() { return _length * (1.0 / 1e-3); };
  double getMicroMeter() { return _length * (1.0 / 1e-6); };
  double getNanoMeter()  { return _length * (1.0 / 1e-9); };
  double getPicoMeter()  { return _length * (1.0 / 1e-12); };
  double getFemtoMeter() { return _length * (1.0 / 1e-15); };
  double getAttoMeter()  { return _length * (1.0 / 1e-18); };
  double getMicron()     { return _length * (1.0 / 1e-6); };
  double getKiloMeter()  { return _length * (1.0 / 1e3); };

  double getMile()    { return _length * (1.0 / 1609.344); };
  double getYard()    { return _length * (1.0 / 0.3048); };
  double getFoot()    { return _length * (1.0 / 0.9144); };
  double getInch()    { return _length * (1.0 / 0.0254); };
  double getFurlong() { return _length * (1.0 / 201.168); };

  //   astronomic units
  double getLightYear()  { return _length * (1.0 / 9.46073047258E+15); };
  double getMegaParsec() { return _length * (1.0 / 3.08567758128E+22); };
  double getKiloParsec() { return _length * (1.0 / 3.08567758128E+19); };
  double getParsec()     { return _length * (1.0 / 3.08567758128E+16); };
  double getAstroUnit()  { return _length * (1.0 / 1.49597870691E+12); };

  //   nautical
  double getLeague()         { return _length * (1.0 / 4828.032); };
  double getNauticalLeague() { return _length * (1.0 / 5556); };  //   int.
  double getNauticalMile()   { return _length * (1.0 / 1852); };  //   int.

  //   less known
  double getChain()   { return _length * (1.0 / 20.1168); };
  double getRope()    { return _length * (1.0 / 6.096); };
  double getRod()     { return _length * (1.0 / 5.0292); };
  double getPerch()   { return _length * (1.0 / 5.0292); };
  double getPole()    { return _length * (1.0 / 5.0292); };
  double getFanthom() { return _length * (1.0 / 1.8288); };
  double getEll()     { return _length * (1.0 / 1.143); };
  double getLink()    { return _length * (1.0 / 0.201168); };
  double getCubit()   { return _length * (1.0 / 0.4572); };

  //   biometric
  double getHand()         { return _length * (1.0 / 0.1016); };
  double getFinger()       { return _length * (1.0 / 0.1143); };
  double getNail()         { return _length * (1.0 / 0.05715); };
  double getHandBreath()   { return _length * (1.0 / 0.0762); };
  double getFingerBreath() { return _length * (1.0 / 0.01905); };

  //  atomic
  double getAngstrom()       { return _length * (1.0 / 1.0E-10); };
  double getAtomicUnit()     { return _length * (1.0 / 5.2917724900001E-11); };
  double getBohrRadius()     { return _length * (1.0 / 5.2917724900001E-11); };
  double getXUnit()          { return _length * (1.0 / 1.00208E-13); };
  double getFermi()          { return _length * (1.0 / 1.0E-15); };
  double getElectronRadius() { return _length * (1.0 / 2.81794092E-15); };
  double getPlanckLength()   { return _length * (1.0 / 1.61605E-35); };

private:
  double _length;
};


//  -- END OF FILE --





