#pragma once
//
//    FILE: Correlation.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Calculate Correlation from a small dataset.
// HISTORY: See Correlation.cpp
//


#include "Arduino.h"


#define CORRELATION_LIB_VERSION          (F("0.1.4"))


class Correlation
{
public:
  Correlation(uint8_t size = 20);   // WARNING calculate memory usage !!
  ~Correlation();

  // returns true if the value is added to internal array.
  // returns false when internal array is full.
  bool    add(float x, float y);

  uint8_t count() { return _count; };
  uint8_t size()  { return _size; };
  void    clear();

  // in running mode, adding new values will replace old ones
  // this constantly adapts the regression params A and B.
  void    setRunningCorrelation(bool rc) { _runningMode = rc; };
  bool    getRunningCorrelation()        { return _runningMode; };

  // worker, to calculate the correlation params. 
  // MUST be called before getting the params A, B, R, Rsquare, Esquare, 
  //                                          avgX and avgY
  // returns false if contains no elements ==> count() == 0
  bool    calculate();

  // Y = A + B * X
  float   getA()       { return _a; };
  float   getB()       { return _b; };

  // returns R == correlation coefficient
  float   getR()       { return sqrt(_rSquare); };
  float   getRsquare() { return _rSquare; };
  
  // returns sum of the errors squared
  float   getEsquare() { return _sumErrorSquare; };

  // get the average values of the datasets (as it is available)
  float   getAvgX()    { return _avgX; };
  float   getAvgY()    { return _avgY; };
  
  // based on the dataset get the estimated values for X and Y
  // library does not return confidence interval for these. 
  float   getEstimateY(float x);
  float   getEstimateX(float y);


  // STATISTICAL
  float   getMinX();    // idem
  float   getMaxX();    // idem
  float   getMinY();    // idem
  float   getMaxY();    // idem


  // DEBUGGING - access to internal arrays.
  bool    setXY(uint8_t idx, float x, float y);  // returns true if succeeded
  bool    setX(uint8_t idx, float x);            // returns true if succeeded
  bool    setY(uint8_t idx, float y);            // returns true if succeeded
  float   getX(uint8_t idx);    // idem
  float   getY(uint8_t idx);    // idem
  float   getSumXiYi() { return _sumXiYi; };
  float   getSumXi2()  { return _sumXi2;  };
  float   getSumYi2()  { return _sumYi2;  };


private:
  uint8_t _size  = 0;
  uint8_t _idx   = 0;
  uint8_t _count = 0;
  bool    _runningMode = false;
  bool    _needRecalculate = true;

  float *  _x;
  float *  _y;

  float   _avgX;
  float   _avgY;
  float   _a;
  float   _b;
  float   _rSquare;
  float   _sumErrorSquare;
  float   _sumXiYi;
  float   _sumXi2;
  float   _sumYi2;
};

// -- END OF FILE --
