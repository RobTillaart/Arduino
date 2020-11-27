#pragma once
//
//    FILE: temperature.h
// VERSION: 0.2.3
// PURPOSE: temperature functions
//
// HISTORY:
// 0.1.0 - 2015-03-29 initial version
// 0.1.1 - 2017-07-26 double to float (issue #33)
// 0.2.0 - 2020-04-04 #pragma once, removed WProgram.h, readme.md, comments
//                    replaced obsolete links with new ones,
//                    tested and removed some code
// 0.2.1   2020-05-26 added windchill formulas
// 0.2.2   2020-06-19 fix library.json
// 0.2.3   2020-08-27 fix #5 order of functions, typo, fixed 1 example


#define TEMPERATURE_VERSION "0.2.3"


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
// calculation of the saturation vapor pressure part is based upon NOAA ESGG(temp)
float dewPoint(float celsius, float humidity)
{
  // Calculate saturation vapor pressure
  // ratio 100C and actual temp in Kelvin
  float A0 = 373.15 / (273.15 + celsius);
  // SVP = Saturation Vapor Pressure - based on ESGG() NOAA
  float SVP = -7.90298 * (A0 - 1.0);
  SVP +=  5.02808 * log10(A0);
  SVP += -1.3816e-7 * (pow(10, (11.344 * ( 1.0 - 1.0/A0))) - 1.0 );
  SVP +=  8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1.0 ))) - 1.0 ) ;
  SVP += log10(1013.246);

  // calculate actual vapor pressure VP;
  // note to convert to KPa the -3 is used
  float VP = pow(10, SVP - 3) * humidity;
  float T = log( VP / 0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}


// dewPointFast() is > 5x faster than dewPoint() - run dewpoint_test.ino
// delta mdewPointFastax with dewpoint() - run dewpoint_test.ino ==> ~0.347
// (earlier version mentions ~0.6544 but that testcode is gone :(
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
float humidex(float celsius, float DewPoint)
{
  float e = 19.833625 - 5417.753 /(273.16 + DewPoint);
  float h = celsius + 3.3941 * exp(e) - 5.555;
  return h;
}


// https://en.wikipedia.org/wiki/Heat_index
// TODO add valid range for TF & R
// TF = temp in Fahrenheit
// R = humidity in %
float heatIndex(float TF, float R)
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
  float B = (((c7 * TF) + c4) * TF + c3) * R;
  float C = (((c9 * TF) + c8) * TF + c6) * R * R;

  return A + B + C;
}


// https://en.wikipedia.org/wiki/Heat_index
// TODO add valid range for TF & R
float heatIndexC(float celcius, float humidity)
{
  const float c1 = -8.78469475556;
  const float c2 =  1.61139411;
  const float c3 =  2.33854883889;
  const float c4 = -0.14611605;
  const float c5 = -0.012308094;
  const float c6 = -0.0164248277778;
  const float c7 =  0.002211732;
  const float c8 =  0.00072546;
  const float c9 = -0.000003582;

  float A = (( c5 * celcius) + c2) * celcius + c1;
  float B = (((c7 * celcius) + c4) * celcius + c3) * humidity;
  float C = (((c9 * celcius) + c8) * celcius + c6) * humidity * humidity;

  return A + B + C;
}


// https://en.wikipedia.org/wiki/Wind_chill
//    US     = Fahrenheit / miles
//    METRIC = Celsius / meter/sec
// windspeed @ 10 meter,
// if convert is true => windspeed will be converted to 1.5 meter
// else ==> formula assumes windspeed @ 1.5 meter

// US
float WindChill_F_mph(const float fahrenheit, const float milesPerHour, const bool convert = true)
{
  float windSpeed = milesPerHour;
  if (convert) windSpeed = pow(milesPerHour, 0.16);
  return 35.74 + 0.6125 * fahrenheit + (0.4275 * fahrenheit - 35.75) * windSpeed;
}

// METRIC
float WindChill_C_kmph(const float celcius, const float kilometerPerHour, const bool convert = true)
{
  float windSpeed = kilometerPerHour;
  if (convert) windSpeed = pow(kilometerPerHour, 0.16);
  return 13.12 + 0.6215 * celcius + (0.3965 * celcius - 11.37) * windSpeed;
}

float WindChill_C_mps(const float celcius, const float meterPerSecond, const bool convert = true)
{
  return WindChill_C_kmph(celcius, meterPerSecond * 3.6, convert);
}


// -- END OF FILE --
