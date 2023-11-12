//
//    FILE: temperature.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.7
//    DATE: 2015-03-29
// PURPOSE: collection temperature functions
//     URL: https://github.com/RobTillaart/Temperature


#include "temperature.h"


float Fahrenheit(float celsius)
{
  return 1.8 * celsius + 32;    //  5.0 / 9.0 = 1.8
}


float Celsius(float Fahrenheit)
{
  return (Fahrenheit - 32) * 0.55555555555;   //  5.0 / 9.0 = 0.555...
}


float Kelvin(float celsius)
{
  return celsius + 273.15;
}


//  reference:
//  [1] https://wahiduddin.net/calc/density_algorithms.htm
//  [2] https://web.archive.org/web/20100528030817/https://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//  dewPoint function based on code of [2]
//  calculation of the saturation vapour pressure part is based upon NOAA ESGG(temp)
float dewPoint(float celsius, float humidity)
{
  //  Calculate saturation vapour pressure
  //  ratio 100C and actual temp in Kelvin
  float AA0 = 373.15 / (273.15 + celsius);
  //  SVP = Saturation Vapor Pressure - based on ESGG() NOAA
  float SVP = -7.90298 * (AA0 - 1.0);
  SVP +=  5.02808 * log10(AA0);
  SVP += -1.3816e-7 * (pow(10, (11.344 * ( 1.0 - 1.0/AA0))) - 1.0 );
  SVP +=  8.1328e-3 * (pow(10, (-3.49149 * (AA0 - 1.0 ))) - 1.0 ) ;
  SVP += log10(1013.246);

  //  calculate actual vapour pressure VP;
  //  note to convert to KPa the -3 is used
  float VP = pow(10, SVP - 3) * humidity;
  float T = log( VP / 0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}


//  dewPointFast() is > 5x faster than dewPoint() - run dewpoint_test.ino
//  delta mdewPointFastax with dewPoint() - run dewpoint_test.ino ==> ~0.347
//  (earlier version mentions ~0.6544 but that test code is gone :(
//  http://en.wikipedia.org/wiki/Dew_point
float dewPointFast(float celsius, float humidity)
{
  float a = 17.271;
  float b = 237.7;
  float temp = (a * celsius) / (b + celsius) + log(humidity/100);
  float Td = (b * temp) / (a - temp);
  return Td;
}


//  https://en.wikipedia.org/wiki/Humidex
float humidex(float celsius, float dewPoint)
{
  float e = 19.833625 - 5417.753 /(273.16 + dewPoint);
  float h = celsius + 3.3941 * exp(e) - 5.555;
  return h;
}


//  0.3.0 => https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
//           previous  https://en.wikipedia.org/wiki/Heat_index
//  TF = temp in Fahrenheit
//  RH = relative humidity in %
float heatIndex(float TF, float RH)
{
  //  Steadman's formula
  //  float HI =  0.5 * (TF + 61.0 + ((TF - 68.0) * 1.2) + (RH * 0.094));
  //  optimized to:
  float HI =  TF * 1.1 - 10.3 + RH * 0.047;


  //  Rothfusz regression
  if (HI >= 80)
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
  }

  return HI;
}


//  0.3.0 => https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
//           previous  https://en.wikipedia.org/wiki/Heat_index
//  TC = temp in Celsius
//  RH = relative humidity in %
float heatIndexC(float TC, float RH)
{
  if ( (TC < 27) || (RH < 40)) return TC;
  float TF = Fahrenheit(TC);
  return Celsius(heatIndex(TF, RH));

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


//  https://carnotcycle.wordpress.com/2012/08/04/how-to-convert-relative-humidity-to-absolute-humidity/
//  Absolute Humidity (grams/m3) = 6.112 × e^[(17.67 × T)/(T+243.5)] × rh × 2.1674
//                                 -----------------------------------------------
//                                                 (273.15+T)
float absoluteHumidity(float Celsius, float relHumidity)
{
  float TC = Celsius;
  float AH = (2.1674 * 6.112) * relHumidity;
  AH *= exp((17.67 * TC)/(243.5 + TC));
  AH /=  (273.15 + TC);
  return AH;
}



//  https://en.wikipedia.org/wiki/Wind_chill
//     US     = Fahrenheit / miles / hour
//     METRIC = Celsius    / meter / hour (sec)
//  wind speed @ 10 meter,
//  if convert is true => wind speed will be converted to 1.5 meter
//  else ==> formula assumes wind speed @ 1.5 meter


//  US
float WindChill_F_mph(const float Fahrenheit, const float milesPerHour, const bool convert)
{
  if ((milesPerHour < 3.0) || (Fahrenheit > 50)) return Fahrenheit;
  float windSpeed = milesPerHour;
  if (convert) windSpeed = pow(milesPerHour, 0.16);
  return 35.74 + 0.6125 * Fahrenheit + (0.4275 * Fahrenheit - 35.75) * windSpeed;
}


//  METRIC - standard wind chill formula for Environment Canada
float WindChill_C_kmph(const float Celsius, const float kilometerPerHour, const bool convert)
{
  if ((kilometerPerHour < 4.8) || (Celsius > 10)) return Celsius;
  float windSpeed = kilometerPerHour;
  if (convert) windSpeed = pow(kilometerPerHour, 0.16);
  return 13.12 + 0.6215 * Celsius + (0.3965 * Celsius - 11.37) * windSpeed;
}


float WindChill_C_mps(const float Celsius, const float meterPerSecond, const bool convert)
{
  return WindChill_C_kmph(Celsius, meterPerSecond * 3.6, convert);
}


//  https://www.engineeringtoolbox.com/air-altitude-pressure-d_462.html
//    Does not have the temperature correction ==> it has almost the -5.257 exponent
//  https://www.omnicalculator.com/physics/air-pressure-at-altitude
//    similar to https://en.wikipedia.org/wiki/Barometric_formula
//
//  Note: altitude in meters.
float baroToSeaLevelC( float pressure, float celsius, float altitude)
{
  float altitudeFactor = 0.0065 * altitude;
  float kelvin = celsius + 273.15;
  return pressure * pow( 1 - (altitudeFactor / (kelvin + altitudeFactor)), -5.257);
}


//  https://www.omnicalculator.com/physics/air-pressure-at-altitude
//    temperature (Celsius) at altitude (meter)
float seaLevelToAltitude( float pressureSeaLevel, float celsius, float altitude)
{
  float kelvin = celsius + 273.15;
  //  P = P0 * exp( -g.M.h / (R.T));
  float factor = -9.80655 * 0.0289644 / 8.31432;
  factor /= kelvin;
  return pressureSeaLevel * exp(factor * abs(altitude));
}

float altitudeToSeaLevel( float pressure, float celsius, float altitude)
{
  float kelvin = celsius + 273.15;
  //  P = P0 * exp( -g.M.h / (R.T));
  float factor = 9.80655 * 0.0289644 / 8.31432;
  factor /= kelvin;
  return pressure / exp(factor * abs(altitude));
}


//  https://en.wikipedia.org/wiki/High-altitude_cooking
float boilingFahrenheit(float feet)
{
  if (feet >= 0) return 212.1309 - feet * 1.86176954e-3;
  return 212;
}


float boilingCelsius(float meter)
{
  if (meter > 0) return 100.08143 - meter * 3.39670635e-3;
  return 100;
}

//  Celsius = 80..100
float boilingMeter(float Celsius)
{
  if (Celsius >= 100) return 0;
  return 29458.542 - Celsius * 294.34149;
}


//  -- END OF FILE --

