#pragma once
//
//    FILE: temperature.h
// VERSION: 0.3.2
//    DATE: 2015-03-29
// PURPOSE: collection temperature functions
//
//  HISTORY:
//  0.1.0   2015-03-29  initial version
//  0.1.1   2017-07-26  double to float (issue #33)
//  0.2.0   2020-04-04  #pragma once, removed WProgram.h, readme.md, comments
//                      replaced obsolete links with new ones,
//                      tested and removed some code
//  0.2.1   2020-05-26  added wind-chill formulas
//  0.2.2   2020-06-19  fix library.json
//  0.2.3   2020-08-27  fix #5 order of functions, typo, fixed 1 example
//  0.2.4   2021-01-08  Arduino-CI + unit tests
//  0.2.5   2021-12-28  Arduino-CI, library.json, readme.md, license, minor edits
//
//  0.3.0   2022-01-05  fix #10 update HeatIndex function
//                      compared with https://www.calculator.net/heat-index-calculator.html
//  0.3.1   2022-01-07  fix adjustments
//  0.3.2   2022-01-08  Renamed Celcius to Celsius.
//                      added a TempConvertor class for more exotic scales.
//                      added baroToSeaLevel() - kudos to RobertDB59


#define TEMPERATURE_VERSION         (F("0.3.2"))


inline float Fahrenheit(float celsius)
{
  return 1.8 * celsius + 32;    // 5.0 / 9.0 = 1.8
}


inline float Celsius(float fahrenheit)
{
  return (fahrenheit - 32) * 0.55555555555;   // 5.0 / 9.0 = 0.555...
}


inline float Kelvin(float celsius)
{
  return celsius + 273.15;
}


// reference:
// [1] https://wahiduddin.net/calc/density_algorithms.htm
// [2] https://web.archive.org/web/20100528030817/https://www.colorado.edu/geography/weather_station/Geog_site/about.htm
// dewPoint function based on code of [2]
// calculation of the saturation vapour pressure part is based upon NOAA ESGG(temp)
float dewPoint(float celsius, float humidity)
{
  // Calculate saturation vapour pressure
  // ratio 100C and actual temp in Kelvin
  float A0 = 373.15 / (273.15 + celsius);
  // SVP = Saturation Vapor Pressure - based on ESGG() NOAA
  float SVP = -7.90298 * (A0 - 1.0);
  SVP +=  5.02808 * log10(A0);
  SVP += -1.3816e-7 * (pow(10, (11.344 * ( 1.0 - 1.0/A0))) - 1.0 );
  SVP +=  8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1.0 ))) - 1.0 ) ;
  SVP += log10(1013.246);

  // calculate actual vapour pressure VP;
  // note to convert to KPa the -3 is used
  float VP = pow(10, SVP - 3) * humidity;
  float T = log( VP / 0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}


// dewPointFast() is > 5x faster than dewPoint() - run dewpoint_test.ino
// delta mdewPointFastax with dewPoint() - run dewpoint_test.ino ==> ~0.347
// (earlier version mentions ~0.6544 but that test code is gone :(
// http://en.wikipedia.org/wiki/Dew_point
float dewPointFast(float celsius, float humidity)
{
  float a = 17.271;
  float b = 237.7;
  float temp = (a * celsius) / (b + celsius) + log(humidity/100);
  float Td = (b * temp) / (a - temp);
  return Td;
}


// https://en.wikipedia.org/wiki/Humidex
float humidex(float celsius, float dewPoint)
{
  float e = 19.833625 - 5417.753 /(273.16 + dewPoint);
  float h = celsius + 3.3941 * exp(e) - 5.555;
  return h;
}


// 0.3.0 => https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml 
//          previous  https://en.wikipedia.org/wiki/Heat_index
// TODO add valid range for TF & R
// TF = temp in Fahrenheit
// RH = relative humidity in %
float heatIndex(float TF, float RH)
{
  float HI = 0;

  if (TF >= 80)
  {
    const float c1 = -42.379;
    const float c2 =  2.04901523;
    const float c3 = 10.14333127;
    const float c4 = -0.22475541;
    const float c5 = -0.00683783;
    const float c6 = -0.05481717;
    const float c7 =  0.00122874;
    const float c8 =  0.00085282;
    const float c9 = -0.00000199;

    float A = (( c5 * TF) + c2) * TF + c1;
    float B = (((c7 * TF) + c4) * TF + c3) * RH;
    float C = (((c9 * TF) + c8) * TF + c6) * RH * RH;

    HI = A + B + C;
    if ((RH < 13) && (TF <= 112))
    {
      HI -= ((13 - RH) / 4) * sqrt((17 - abs(TF - 95.0)) / 17);
    }
    if ((RH > 87) && (TF < 87))
    {
      HI += ((RH - 85) / 10) * ((87 - TF) / 5);
    }
    return HI;
  }

  HI = 0.5 * (TF + 61.0 + ((TF - 68.0) * 1.2) + (RH * 0.094));

  return HI;
}


// 0.3.0 => https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml 
//          previous  https://en.wikipedia.org/wiki/Heat_index
// TODO add valid range for TF & RH
// TODO optimize?
float heatIndexC(float C, float humidity)
{
  float TF = Fahrenheit(C);
  return Celsius(heatIndex(TF, humidity));

/*
  const float c1 = -8.78469475556;
  const float c2 =  1.61139411;
  const float c3 =  2.33854883889;
  const float c4 = -0.14611605;
  const float c5 = -0.012308094;
  const float c6 = -0.0164248277778;
  const float c7 =  0.002211732;
  const float c8 =  0.00072546;
  const float c9 = -0.000003582;

  float A = (( c5 * Celsius) + c2) * Celsius + c1;
  float B = (((c7 * Celsius) + c4) * Celsius + c3) * humidity;
  float C = (((c9 * Celsius) + c8) * Celsius + c6) * humidity * humidity;

  return A + B + C;
*/
}


// https://en.wikipedia.org/wiki/Wind_chill
//    US     = Fahrenheit / miles
//    METRIC = Celsius / meter/sec
// wind speed @ 10 meter,
// if convert is true => wind speed will be converted to 1.5 meter
// else ==> formula assumes wind speed @ 1.5 meter


// US
float WindChill_F_mph(const float fahrenheit, const float milesPerHour, const bool convert = true)
{
  float windSpeed = milesPerHour;
  if (convert) windSpeed = pow(milesPerHour, 0.16);
  return 35.74 + 0.6125 * fahrenheit + (0.4275 * fahrenheit - 35.75) * windSpeed;
}


// METRIC
float WindChill_C_kmph(const float Celsius, const float kilometerPerHour, const bool convert = true)
{
  float windSpeed = kilometerPerHour;
  if (convert) windSpeed = pow(kilometerPerHour, 0.16);
  return 13.12 + 0.6215 * Celsius + (0.3965 * Celsius - 11.37) * windSpeed;
}


float WindChill_C_mps(const float Celsius, const float meterPerSecond, const bool convert = true)
{
  return WindChill_C_kmph(Celsius, meterPerSecond * 3.6, convert);
}


// https://www.engineeringtoolbox.com/air-altitude-pressure-d_462.html
//   Does not have the temperature correction ==> it has almost the -5.257 exponent
// https://www.omnicalculator.com/physics/air-pressure-at-altitude
//   similar to https://en.wikipedia.org/wiki/Barometric_formula
//
// Note: altitude in meters.
float baroToSeaLevelC( float pressure, float celsius, float altitude)
{
  float altitudeFactor = 0.0065 * altitude;
  float kelvin = celsius + 273.15;
  return pressure * pow( 1 - (altitudeFactor / (kelvin + altitudeFactor)), -5.257);
}


/////////////////////////////////////////////////////////////
//
//  TEMPERATURE CONVERTER CLASS
//
class temperatureConverter
{
  //  used Celsius as internal unit, to minimize math
  public:
    temperatureConverter()              { _temp = 0; };

    void setKelvin(float value = 0)     { _temp = value - 273.15; };
    void setCelsius(float value = 0)    { _temp = value; };
    void setFahrenheit(float value = 0) { _temp = (value - 32.0) / 1.8; };
    void setReamur(float value = 0)     { _temp = value * 1.25; };
    void setRankine(float value = 0)    { _temp = (value - 491.67) / 1.8; };
    void setDelisle(float value = 0)    { _temp = (value + 100) / 1.5; };
    void setNewton(float value = 0)     { _temp = value / 0.33; };
    void setRomer(float value = 0)      { _temp = (value - 7.5) / 0.525; };

    float getKelvin()      { return _temp + 273.15; };
    float getCelsius()     { return _temp; };
    float getFahrenheit()  { return _temp * 1.8 + 32; };
    float getReamur()      { return _temp * 0.8; };
    float getRankine()     { return _temp * 1.8 + 491.67; };
    float getDelisle()     { return _temp * 1.5 - 100.0; };
    float getNewton()      { return _temp * 0.33; };
    float getRomer()       { return _temp * 0.525 + 7.5; };

  private:
    float _temp = 0;
};


// -- END OF FILE --

